#include "Entity/Backdrop.h"
#include "Entity/EntityManager.h"
#include "Entity/Title.h"
#include "Entity/UIButton.h"
#include "Entity/UICamera.h"
#include "GL/GLManager.h"
#include "GL/RenderManager2D.h"
#include "GL/TTFont.h"
#include "Scene/GamePlayScene.h"
#include "Scene/GameTitleScene.h"
#include "Scene/SceneManager.h"
#include "Utils/Assertion.h"
#include "Utils/Utils.h"

GameTitleScene::GameTitleScene()
{
	sceneManager_->Register("GameTitleScene", this);

	uiCamera_ = entityManager_->GetByName<UICamera>("UICamera");
	updateUiEntities_.push_back(uiCamera_);

	Backdrop* backdrop = entityManager_->Create<Backdrop>();
	updateUiEntities_.push_back(backdrop);
	renderUiEntities_.push_back(backdrop);

	Title* title = entityManager_->Create<Title>();
	updateUiEntities_.push_back(title);
	renderUiEntities_.push_back(title);

	UIButton* button = entityManager_->Create<UIButton>(uiCamera_, glManager_->GetByName<TTFont>("Font24"), EMouse::LEFT, [&]() {});
	updateUiEntities_.push_back(button);
	renderUiEntities_.push_back(button);
}

GameTitleScene::~GameTitleScene()
{
}

void GameTitleScene::Tick(float deltaSeconds)
{
	for (auto& uiEntity : updateUiEntities_)
	{
		uiEntity->Tick(deltaSeconds);
	}
}

void GameTitleScene::Render()
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

void GameTitleScene::Enter()
{
}

void GameTitleScene::Exit()
{
}
