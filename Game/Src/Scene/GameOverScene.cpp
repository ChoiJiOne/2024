#include "App/GameApp.h"
#include "App/IApp.h"
#include "Entity/Backdrop.h"
#include "Entity/EntityManager.h"
#include "Entity/FadeEffector.h"
#include "Entity/UIButton.h"
#include "Entity/UICamera.h"
#include "GL/FrameBuffer.h"
#include "GL/GLManager.h"
#include "GL/PostProcessor.h"
#include "GL/TTFont.h"
#include "Scene/GameOverScene.h"
#include "Scene/GamePlayScene.h"
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
		postProcessor_->Blit(type, frameBuffer_);
	}
	glManager_->EndFrame();
}

void GameOverScene::Enter()
{
	bIsEnter_ = true;
	bIsSwitched_ = false;
}

void GameOverScene::Exit()
{
	bIsSwitched_ = false;
	bIsEnter_ = false;
}

void GameOverScene::Initailize()
{
}

void GameOverScene::UnInitailize()
{
}
