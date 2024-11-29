#include "Entity/Backdrop.h"
#include "Entity/EntityManager.h"
#include "Entity/UIButton.h"
#include "Entity/UICamera.h"
#include "Entity/UIPanel.h"
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

	Initailize();
}

GameOptionScene::~GameOptionScene()
{
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

	UIPanel* optionPanel = entityManager_->Create<UIPanel>("Resource\\UI\\Option.panel", glManager_->GetByName<TextureAtlas2D>("TextureAtlas"));
	updateUiEntities_.push_back(optionPanel);
	renderUiEntities_.push_back(optionPanel);

	TTFont* font48 = glManager_->GetByName<TTFont>("Font48");

	UIButton* backBtn = entityManager_->Create<UIButton>("Resource\\UI\\Back.button", uiCamera_, font48, EMouse::LEFT,
		[&]()
		{
			bIsSwitched_ = true;
			switchScene_ = sceneManager_->GetByName<GameTitleScene>("GameTitleScene");
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
