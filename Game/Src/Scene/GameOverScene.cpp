#include "App/GameApp.h"
#include "App/IApp.h"
#include "Entity/Backdrop.h"
#include "Entity/EntityManager.h"
#include "Entity/FadeEffector.h"
#include "Entity/GameOver.h"
#include "Entity/ResultViewer.h"
#include "Entity/UIButton.h"
#include "Entity/UICamera.h"
#include "Game/GameManager.h"
#include "GL/FrameBuffer.h"
#include "GL/GLManager.h"
#include "GL/PostProcessor.h"
#include "GL/TTFont.h"
#include "Scene/GameOverScene.h"
#include "Scene/GameTitleScene.h"
#include "Scene/SceneManager.h"
#include "Utils/Assertion.h"
#include "Utils/Utils.h"

GameOverScene::GameOverScene()
{
	sceneManager_->Register("GameOverScene", this);

	Initailize();
}

GameOverScene::~GameOverScene()
{
	UnInitailize();
}

void GameOverScene::Tick(float deltaSeconds)
{
	for (auto& uiEntity : updateUiEntities_)
	{
		uiEntity.second->Tick(deltaSeconds);
	}
}

void GameOverScene::Render()
{
	glManager_->BeginFrame(0.0f, 0.0f, 0.0f, 1.0f);
	{
		renderManager_->Begin(uiCamera_, frameBuffer_, renderTargetOption_);
		{
			for (auto& uiEntity : renderUiEntities_)
			{
				uiEntity.second->Render();
			}
		}
		renderManager_->End();

		PostProcessor::EType type = PostProcessor::EType::BLIT;
		if (fadeEffector_->GetState() == FadeEffector::EState::PROGRESS)
		{
			type = PostProcessor::EType::BLEND_COLOR;
			postProcessor_->SetBlendColor(fadeEffector_->GetBlendColor(), fadeEffector_->GetFactor());
		}

		postProcessor_->Blit(type, frameBuffer_);
	}
	glManager_->EndFrame();
}

void GameOverScene::Enter()
{
	bIsEnter_ = true;
	bIsSwitched_ = false;

	playTimeResultViewer_->Start(static_cast<int32_t>(gameManager_->GetRecentGamePlayRecord()->playTime));
	getCoinResultViewer_->Start(gameManager_->GetRecentGamePlayRecord()->getCoin);

	fadeEffector_->StartIn(fadeInTime_);
}

void GameOverScene::Exit()
{
	fadeEffector_->Reset();

	bIsSwitched_ = false;
	bIsEnter_ = false;
}

void GameOverScene::Initailize()
{
	postProcessor_ = renderManager_->GetPostProcessor();
	frameBuffer_ = reinterpret_cast<GameApp*>(IApp::GetPtr())->GetFrameBuffer();
	renderTargetOption_ = RenderTargetOption{ glm::vec4(0.0f, 0.0f, 0.0f, 1.0f), true };

	uiCamera_ = entityManager_->GetByName<UICamera>("UICamera");
	updateUiEntities_.insert({ "UICamera", uiCamera_ });
	
	Backdrop* backdrop = entityManager_->GetByName<Backdrop>("Backdrop");
	updateUiEntities_.insert({ "Backdrop", backdrop });
	renderUiEntities_.insert({ "Backdrop", backdrop });

	GameOver* gameOver = entityManager_->Create<GameOver>();
	updateUiEntities_.insert({ "GameOver", gameOver });
	renderUiEntities_.insert({ "GameOver", gameOver });

	TTFont* font48 = glManager_->GetByName<TTFont>("Font48");
	resultViewTime_ = 5.0f;

	playTimeResultViewer_ = entityManager_->Create<ResultViewer>(font48, glm::vec2(0.0f, 0.0f), L"TIME", glm::vec4(0.0f, 0.0f, 0.0f, 1.0f), resultViewTime_);
	updateUiEntities_.insert({ "PlayTimeResultViewer", playTimeResultViewer_ });
	renderUiEntities_.insert({ "PlayTimeResultViewer", playTimeResultViewer_ });

	getCoinResultViewer_ = entityManager_->Create<ResultViewer>(font48, glm::vec2(0.0f, -50.0f), L"COIN", glm::vec4(0.0f, 0.0f, 0.0f, 1.0f), resultViewTime_);
	updateUiEntities_.insert({ "GetCoinResultViewer", getCoinResultViewer_ });
	renderUiEntities_.insert({ "GetCoinResultViewer", getCoinResultViewer_ });

	UIButton* doneBtn = entityManager_->Create<UIButton>("Resource\\UI\\Done.button", uiCamera_, font48, EMouse::LEFT, 
		[&]() 
		{
			bIsSwitched_ = true;
			switchScene_ = sceneManager_->GetByName<GameTitleScene>("GameTitleScene");
		}
	);
	updateUiEntities_.insert({ "DoneButton", doneBtn });
	renderUiEntities_.insert({ "DoneButton", doneBtn });

	fadeEffector_ = entityManager_->GetByName<FadeEffector>("FadeEffector");
	updateUiEntities_.insert({ "FadeEffector", fadeEffector_ });
}

void GameOverScene::UnInitailize()
{	
	/** 외부에서 생성된 엔티티나 리소스는 초기화 해제하지 않습니다. */
	for (auto& updateUiEntity : updateUiEntities_)
	{
		if (updateUiEntity.second == uiCamera_)
		{
			// UI 카메라는 외부에서 생성했으므로, 정리 대상에서 제외.
			continue;
		}

		if (updateUiEntity.second && updateUiEntity.second->IsInitialized())
		{
			entityManager_->Destroy(updateUiEntity.second);
			updateUiEntity.second = nullptr;
		}
	}

	for (auto& renderUIEntity : renderUiEntities_)
	{
		if (renderUIEntity.second && renderUIEntity.second->IsInitialized())
		{
			entityManager_->Destroy(renderUIEntity.second);
			renderUIEntity.second = nullptr;
		}
	}

	frameBuffer_ = nullptr;
	postProcessor_ = nullptr;
}
