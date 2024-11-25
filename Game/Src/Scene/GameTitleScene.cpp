#include "App/GameApp.h"
#include "App/IApp.h"
#include "Entity/Backdrop.h"
#include "Entity/EntityManager.h"
#include "Entity/FadeEffector.h"
#include "Entity/Title.h"
#include "Entity/UIButton.h"
#include "Entity/UICamera.h"
#include "GL/FrameBuffer.h"
#include "GL/GLManager.h"
#include "GL/PostProcessor.h"
#include "GL/TTFont.h"
#include "Scene/GamePlayScene.h"
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
		uiEntity.second->Tick(deltaSeconds);
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
				uiEntity.second->Render();
			}
		}
		renderManager_->End();

		PostProcessor::EType type = PostProcessor::EType::BLIT;
		const FadeEffector::EState& state = fadeEffector_->GetState();
		if (state != FadeEffector::EState::WAIT)
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
	updateUiEntities_.insert({ "UICamera", uiCamera_ });

	fadeEffector_ = entityManager_->GetByName<FadeEffector>("FadeEffector");
	updateUiEntities_.insert({ "FadeEffector", fadeEffector_ });

	Backdrop* backdrop = entityManager_->Create<Backdrop>();
	entityManager_->Register("Backdrop", backdrop);
	updateUiEntities_.insert({ "Backdrop", backdrop });
	renderUiEntities_.insert({ "Backdrop", backdrop });

	Title* title = entityManager_->Create<Title>();
	updateUiEntities_.insert({ "Title", title });
	renderUiEntities_.insert({ "Title", title });

	TTFont* font48 = glManager_->GetByName<TTFont>("Font48");

	UIButton* startBtn = entityManager_->Create<UIButton>("Resource\\UI\\Start.button", uiCamera_, font48, EMouse::LEFT, 
		[&]() 
		{ 
			fadeEffector_->StartOut(fadeOutTime_); 
		}
	);
	updateUiEntities_.insert({ "StartButton", startBtn });
	renderUiEntities_.insert({ "StartButton", startBtn });

	UIButton* galleryBtn = entityManager_->Create<UIButton>("Resource\\UI\\Gallery.button", uiCamera_, font48, EMouse::LEFT, [&]() {});
	updateUiEntities_.insert({ "GalleryButton", galleryBtn });
	renderUiEntities_.insert({ "GalleryButton", galleryBtn });

	UIButton* optionBtn = entityManager_->Create<UIButton>("Resource\\UI\\Option.button", uiCamera_, font48, EMouse::LEFT, [&]() {});
	updateUiEntities_.insert({ "OptionButton", optionBtn });
	renderUiEntities_.insert({ "OptionButton", optionBtn });

	auto loopDoneEvent = [&]() { IApp::GetPtr()->RequestDoneLoop(); };
	UIButton* quitBtn = entityManager_->Create<UIButton>("Resource\\UI\\Quit.button", uiCamera_, font48, EMouse::LEFT, loopDoneEvent);
	updateUiEntities_.insert({ "QuitButton", quitBtn });
	renderUiEntities_.insert({ "QuitButton", quitBtn });
}

void GameTitleScene::UnInitailize()
{
	/** �ܺο��� ������ ��ƼƼ�� ���ҽ��� �ʱ�ȭ �������� �ʽ��ϴ�. */
	for (auto& updateUiEntity : updateUiEntities_)
	{
		if (updateUiEntity.second == uiCamera_)
		{
			// UI ī�޶�� �ܺο��� ���������Ƿ�, ���� ��󿡼� ����.
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
