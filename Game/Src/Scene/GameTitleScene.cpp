#include "App/GameApp.h"
#include "App/IApp.h"
#include "Entity/Backdrop.h"
#include "Entity/EntityManager.h"
#include "Entity/FadeEffector.h"
#include "Entity/UIButton.h"
#include "Entity/UICamera.h"
#include "Entity/UIPanel.h"
#include "Entity/UIText.h"
#include "GL/FrameBuffer.h"
#include "GL/GLManager.h"
#include "GL/PostProcessor.h"
#include "GL/TTFont.h"
#include "Scene/GameOptionScene.h"
#include "Scene/GamePlayScene.h"
#include "Scene/GameRecordScene.h"
#include "Scene/GameTitleScene.h"
#include "Scene/SceneManager.h"
#include "Utils/Assertion.h"
#include "Utils/Utils.h"

GameTitleScene::GameTitleScene()
{
	sceneManager_->Register("GameTitleScene", this);

	Initailize();
}

GameTitleScene::~GameTitleScene()
{
	UnInitailize();
}

void GameTitleScene::Tick(float deltaSeconds)
{
	if (fadeEffector_->GetState() == FadeEffector::EState::PROGRESS)
	{
		fadeEffector_->Tick(deltaSeconds);

		// ���̵� �ƿ� ȿ���� �������� Ȯ��.
		if (fadeEffector_->GetState() == FadeEffector::EState::DONE)
		{
			bIsSwitched_ = true;
			switchScene_ = sceneManager_->GetByName<GamePlayScene>("GamePlayScene");
		}
		return;
	}

	for (auto& uiEntity : updateUiEntities_)
	{
		uiEntity->Tick(deltaSeconds);
	}
}

void GameTitleScene::Render()
{
	glManager_->BeginFrame(0.0f, 0.0f, 0.0f, 1.0f);
	{
		renderManager_->Begin(uiCamera_, frameBuffer_, renderTargetOption_);
		{
			for (auto& uiEntity : renderUiEntities_)
			{
				uiEntity->Render();
			}
		}
		renderManager_->End();

		PostProcessor::EType type = PostProcessor::EType::BLIT;
		if (fadeEffector_->GetState() != FadeEffector::EState::WAIT)
		{
			type = PostProcessor::EType::BLEND_COLOR;
			postProcessor_->SetBlendColor(fadeEffector_->GetBlendColor(), fadeEffector_->GetFactor());
		}

		postProcessor_->Blit(type, frameBuffer_);
	}
	glManager_->EndFrame();
}

void GameTitleScene::Enter()
{
	bIsEnter_ = true;
	bIsSwitched_ = false;
}

void GameTitleScene::Exit()
{
	fadeEffector_->Reset();

	bIsSwitched_ = false;
	bIsEnter_ = false;
}

void GameTitleScene::Initailize()
{
	postProcessor_ = renderManager_->GetPostProcessor();
	frameBuffer_ = reinterpret_cast<GameApp*>(IApp::GetPtr())->GetFrameBuffer();
	renderTargetOption_ = RenderTargetOption{ glm::vec4(0.0f, 0.0f, 0.0f, 1.0f), true };

	uiCamera_ = entityManager_->GetByName<UICamera>("UICamera");
	updateUiEntities_.push_back(uiCamera_);

	Backdrop* backdrop = entityManager_->Create<Backdrop>();
	entityManager_->Register("Backdrop", backdrop);
	updateUiEntities_.push_back(backdrop);
	renderUiEntities_.push_back(backdrop);

	UIPanel* titlePanel = entityManager_->Create<UIPanel>("Resource\\UI\\Title.panel", glManager_->GetByName<TextureAtlas2D>("TextureAtlas"));
	updateUiEntities_.push_back(titlePanel);
	renderUiEntities_.push_back(titlePanel);

	TTFont* font48 = glManager_->GetByName<TTFont>("Font48");

	UIText* menuText = entityManager_->Create<UIText>("Resource\\UI\\Menu.text", font48);
	updateUiEntities_.push_back(menuText);
	renderUiEntities_.push_back(menuText);

	UIButton* startBtn = entityManager_->Create<UIButton>("Resource\\UI\\Start.button", uiCamera_, font48, EMouse::LEFT, 
		[&]() { fadeEffector_->StartOut(fadeOutTime_); }
	);
	updateUiEntities_.push_back(startBtn);
	renderUiEntities_.push_back(startBtn);

	UIButton* recordBtn = entityManager_->Create<UIButton>("Resource\\UI\\Record.button", uiCamera_, font48, EMouse::LEFT, 
		[&]() 
		{
			bIsSwitched_ = true;
			switchScene_ = sceneManager_->GetByName<GameRecordScene>("GameRecordScene");
		}
	);
	updateUiEntities_.push_back(recordBtn);
	renderUiEntities_.push_back(recordBtn);

	UIButton* optionBtn = entityManager_->Create<UIButton>("Resource\\UI\\Option.button", uiCamera_, font48, EMouse::LEFT, 
		[&]() 
		{
			bIsSwitched_ = true;
			switchScene_ = sceneManager_->GetByName<GameOptionScene>("GameOptionScene");
		}
	);
	updateUiEntities_.push_back(optionBtn);
	renderUiEntities_.push_back(optionBtn);

	UIButton* quitBtn = entityManager_->Create<UIButton>("Resource\\UI\\Quit.button", uiCamera_, font48, EMouse::LEFT, 
		[&]()
		{ 
			IApp::GetPtr()->RequestDoneLoop(); 
		}
	);
	updateUiEntities_.push_back(quitBtn);
	renderUiEntities_.push_back(quitBtn);

	fadeEffector_ = entityManager_->GetByName<FadeEffector>("FadeEffector");
	updateUiEntities_.push_back(fadeEffector_);
}

void GameTitleScene::UnInitailize()
{
	updateUiEntities_.remove(uiCamera_);

	for (auto& updateUiEntity : updateUiEntities_)
	{
		if (updateUiEntity && updateUiEntity->IsInitialized())
		{
			entityManager_->Destroy(updateUiEntity);
			updateUiEntity = nullptr;
		}
	}
	
	frameBuffer_ = nullptr;
	postProcessor_ = nullptr;
}
