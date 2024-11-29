#include "Entity/Backdrop.h"
#include "Entity/EntityManager.h"
#include "Entity/PlayRecordViewer.h"
#include "Entity/UIButton.h"
#include "Entity/UICamera.h"
#include "Entity/UIPanel.h"
#include "GL/GLManager.h"
#include "GL/RenderManager2D.h"
#include "GL/TTFont.h"
#include "Scene/GameRecordScene.h"
#include "Scene/GameTitleScene.h"
#include "Scene/SceneManager.h"
#include "Utils/Assertion.h"

GameRecordScene::GameRecordScene()
{
	sceneManager_->Register("GameRecordScene", this);

	Initailize();
}

GameRecordScene::~GameRecordScene()
{
	UnInitailize();
}

void GameRecordScene::Tick(float deltaSeconds)
{
	for (auto& uiEntity : updateUiEntities_)
	{
		uiEntity->Tick(deltaSeconds);
	}
}

void GameRecordScene::Render()
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

void GameRecordScene::Enter()
{
	bIsEnter_ = true;
	bIsSwitched_ = false;

	playRecordViewer_->Update();
}

void GameRecordScene::Exit()
{
	bIsSwitched_ = false;
	bIsEnter_ = false;
}

void GameRecordScene::Initailize()
{
	uiCamera_ = entityManager_->GetByName<UICamera>("UICamera");
	updateUiEntities_.push_back(uiCamera_);

	Backdrop* backdrop = entityManager_->GetByName<Backdrop>("Backdrop");
	updateUiEntities_.push_back(backdrop);
	renderUiEntities_.push_back(backdrop);

	TTFont* font48 = glManager_->GetByName<TTFont>("Font48");

	UIPanel* recordPanel = entityManager_->Create<UIPanel>("Resource\\UI\\Record.panel", glManager_->GetByName<TextureAtlas2D>("TextureAtlas"));
	updateUiEntities_.push_back(recordPanel);
	renderUiEntities_.push_back(recordPanel);

	playRecordViewer_ = entityManager_->Create<PlayRecordViewer>();
	updateUiEntities_.push_back(playRecordViewer_);
	renderUiEntities_.push_back(playRecordViewer_);

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

void GameRecordScene::UnInitailize()
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
