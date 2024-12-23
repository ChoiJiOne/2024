#include <array>

#include "Audio/AudioManager.h"
#include "Audio/Sound.h"
#include "Entity/Backdrop.h"
#include "Entity/EntityManager.h"
#include "Entity/UIButton.h"
#include "Entity/UICamera.h"
#include "Entity/UIPanel.h"
#include "Entity/UISlider.h"
#include "Entity/UIText.h"
#include "Game/GameManager.h"
#include "GL/GLManager.h"
#include "GL/RenderManager2D.h"
#include "GL/TTFont.h"
#include "Scene/GameOptionScene.h"
#include "Scene/GameTitleScene.h"
#include "Scene/SceneManager.h"
#include "Utils/Assertion.h"

GameOptionScene::GameOptionScene()
{
	sceneManager_->Register("GameOptionScene", this);

	gameManager_ = GameManager::GetPtr();

	Initailize();
}

GameOptionScene::~GameOptionScene()
{
	gameManager_ = nullptr;

	UnInitailize();
}

void GameOptionScene::Tick(float deltaSeconds)
{
	for (auto& uiEntity : updateUiEntities_)
	{
		uiEntity->Tick(deltaSeconds);
	}
}

void GameOptionScene::Render()
{
	glManager_->BeginFrame(0.0f, 0.0f, 0.0f, 1.0f);
	{
		renderManager_->Begin(uiCamera_);
		{
			for (auto& uiEntity : renderUiEntities_)
			{
				uiEntity->Render();
			}
		}
		renderManager_->End();
	}
	glManager_->EndFrame();
}

void GameOptionScene::Enter()
{
	bIsEnter_ = true;
	bIsSwitched_ = false;
}

void GameOptionScene::Exit()
{
	bIsSwitched_ = false;
	bIsEnter_ = false;
}

void GameOptionScene::Initailize()
{
	uiCamera_ = entityManager_->GetByName<UICamera>("UICamera");
	updateUiEntities_.push_back(uiCamera_);

	Backdrop* backdrop = entityManager_->GetByName<Backdrop>("Backdrop");
	updateUiEntities_.push_back(backdrop);
	renderUiEntities_.push_back(backdrop);

	UIPanel* optionPanel = entityManager_->Create<UIPanel>("Resource\\UI\\GameOptionScene\\Option.panel", glManager_->GetByName<TextureAtlas2D>("TextureAtlas"));
	updateUiEntities_.push_back(optionPanel);
	renderUiEntities_.push_back(optionPanel);

	TTFont* font48 = glManager_->GetByName<TTFont>("Font48");

	static std::array<std::string, 7> uiNames =
	{
		"Charge",
		"Click",
		"Coin",
		"Dash",
		"EndSound",
		"Explosion",
		"Theme"
	};

	for (const auto& uiName : uiNames)
	{
		float volume = gameManager_->GetConfigValue<float>(PrintF("Sound.%s", uiName.c_str()));
		Sound* sound = AudioManager::GetRef().GetByName<Sound>(uiName);
		sound->SetVolume(volume);

		std::string sliderUIPath = PrintF("Resource\\UI\\GameOptionScene\\%s.slider", uiName.c_str());
		UISlider* sliderUI = entityManager_->Create<UISlider>(sliderUIPath, uiCamera_, EMouse::LEFT,
			[&](float rate)
			{
				Sound* sound = AudioManager::GetRef().GetByName<Sound>(uiName);
				sound->SetVolume(rate);
				sound->Start();
			}
		);
		updateUiEntities_.push_back(sliderUI);
		renderUiEntities_.push_back(sliderUI);

		std::string textUIPath = PrintF("Resource\\UI\\GameOptionScene\\%s.text", uiName.c_str());

		UIText* textUI = entityManager_->Create<UIText>(textUIPath, font48);
		updateUiEntities_.push_back(textUI);
		renderUiEntities_.push_back(textUI);
	}
	
	UIButton* backBtn = entityManager_->Create<UIButton>("Resource\\UI\\GameOptionScene\\Back.button", uiCamera_, font48, EMouse::LEFT,
		[&]()
		{
			AudioManager::GetRef().GetByName<Sound>("Click")->Start();

			bIsSwitched_ = true;
			switchScene_ = backScene_;
		}
	);
	updateUiEntities_.push_back(backBtn);
	renderUiEntities_.push_back(backBtn);
}

void GameOptionScene::UnInitailize()
{	
	/** 외부에서 생성된 엔티티나 리소스는 초기화 해제하지 않습니다. */
	for (auto& updateUiEntity : updateUiEntities_)
	{
		if (updateUiEntity == uiCamera_)
		{
			// UI 카메라는 외부에서 생성했으므로, 정리 대상에서 제외.
			continue;
		}

		if (updateUiEntity && updateUiEntity->IsInitialized())
		{
			entityManager_->Destroy(updateUiEntity);
			updateUiEntity = nullptr;
		}
	}
}
