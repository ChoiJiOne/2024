#include "Audio/AudioManager.h"
#include "Audio/Sound.h"
#include "Entity/Camera2D.h"
#include "Entity/EntityManager.h"
#include "Entity/UIButton.h"
#include "Entity/UICamera.h"
#include "GL/FrameBuffer.h"
#include "GL/GLManager.h"
#include "GL/PostProcessor.h"
#include "Scene/GameOptionScene.h"
#include "Scene/GamePauseScene.h"
#include "Scene/GamePlayScene.h"
#include "Scene/GameTitleScene.h"
#include "Scene/SceneManager.h"
#include "Utils/Assertion.h"

GamePauseScene::GamePauseScene()
{
	sceneManager_->Register("GamePauseScene", this);

	Initailize();
}

GamePauseScene::~GamePauseScene()
{
	UnInitailize();
}

void GamePauseScene::Tick(float deltaSeconds)
{
	for (auto& uiEntity : updateUiEntities_)
	{
		uiEntity->Tick(deltaSeconds);
	}
}

void GamePauseScene::Render()
{
	glManager_->BeginFrame(0.0f, 0.0f, 0.0f, 1.0f);
	{
		RenderGamePlayScene();

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

void GamePauseScene::Enter()
{
	bIsEnter_ = true;
	bIsSwitched_ = false;
}

void GamePauseScene::Exit()
{
	GameTitleScene* gameTitleScene = sceneManager_->GetByName<GameTitleScene>("GameTitleScene");
	if (switchScene_ == gameTitleScene)
	{
		gamePlayScene_->bIsPause_ = false;
		gamePlayScene_->Exit();
	}

	bIsSwitched_ = false;
	bIsEnter_ = false;
}

void GamePauseScene::Initailize()
{
	uiCamera_ = entityManager_->GetByName<UICamera>("UICamera");
	updateUiEntities_.push_back(uiCamera_);

	TTFont* font48 = glManager_->GetByName<TTFont>("Font48");

	UIButton* continueBtn = entityManager_->Create<UIButton>("Resource\\UI\\GamePauseScene\\Continue.button", uiCamera_, font48, EMouse::LEFT,
		[&]()
		{
			AudioManager::GetRef().GetByName<Sound>("Click")->Start();

			bIsSwitched_ = true;
			switchScene_ = sceneManager_->GetByName<GamePlayScene>("GamePlayScene");
		}
	);
	updateUiEntities_.push_back(continueBtn);
	renderUiEntities_.push_back(continueBtn);

	UIButton* optionBtn = entityManager_->Create<UIButton>("Resource\\UI\\GamePauseScene\\Option.button", uiCamera_, font48, EMouse::LEFT,
		[&]()
		{
			AudioManager::GetRef().GetByName<Sound>("Click")->Start();

			GameOptionScene* gameOptionScene = sceneManager_->GetByName<GameOptionScene>("GameOptionScene");
			gameOptionScene->SetBackwardsScene(this);

			bIsSwitched_ = true;
			switchScene_ = gameOptionScene;
		}
	);
	updateUiEntities_.push_back(optionBtn);
	renderUiEntities_.push_back(optionBtn);

	UIButton* doneBtn = entityManager_->Create<UIButton>("Resource\\UI\\GamePauseScene\\Done.button", uiCamera_, font48, EMouse::LEFT,
		[&]()
		{
			AudioManager::GetRef().GetByName<Sound>("Click")->Start();

			bIsSwitched_ = true;
			switchScene_ = sceneManager_->GetByName<GameTitleScene>("GameTitleScene");
		}
	);
	updateUiEntities_.push_back(doneBtn);
	renderUiEntities_.push_back(doneBtn);

	gamePlayScene_ = sceneManager_->GetByName<GamePlayScene>("GamePlayScene");
}

void GamePauseScene::UnInitailize()
{
	gamePlayScene_ = nullptr;

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

void GamePauseScene::RenderGamePlayScene()
{
	gamePlayScene_->renderTargetOption_.bIsClearBuffer = true;
	renderManager_->Begin(gamePlayScene_->mainCamera_, gamePlayScene_->frameBuffer_, gamePlayScene_->renderTargetOption_);
	{
		for (auto& renderEntity : gamePlayScene_->renderEntities_)
		{
			if (gamePlayScene_->gameEntityRange_.first <= renderEntity.first && renderEntity.first <= gamePlayScene_->gameEntityRange_.second)
			{
				renderEntity.second->Render();
			}
		}
	}
	renderManager_->End();

	gamePlayScene_->renderTargetOption_.bIsClearBuffer = false;
	renderManager_->Begin(gamePlayScene_->uiCamera_, gamePlayScene_->frameBuffer_, gamePlayScene_->renderTargetOption_);
	{
		for (auto& renderEntity : gamePlayScene_->renderEntities_)
		{
			if (gamePlayScene_->uiEntityRange_.first <= renderEntity.first && renderEntity.first <= gamePlayScene_->uiEntityRange_.second)
			{
				renderEntity.second->Render();
			}
		}
	}
	renderManager_->End();

	gamePlayScene_->postProcessor_->Blit(PostProcessor::EType::GAUSSIAN_BLUR, gamePlayScene_->frameBuffer_);
}
