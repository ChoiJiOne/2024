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

	UIButton* startBtn = entityManager_->Create<UIButton>("Resource\\UI\\Start.button", uiCamera_, glManager_->GetByName<TTFont>("Font48"), EMouse::LEFT, [&]() {});
	updateUiEntities_.push_back(startBtn);
	renderUiEntities_.push_back(startBtn);

	UIButton* galleryBtn = entityManager_->Create<UIButton>("Resource\\UI\\Gallery.button", uiCamera_, glManager_->GetByName<TTFont>("Font48"), EMouse::LEFT, [&]() {});
	updateUiEntities_.push_back(galleryBtn);
	renderUiEntities_.push_back(galleryBtn);

	UIButton* optionBtn = entityManager_->Create<UIButton>("Resource\\UI\\Option.button", uiCamera_, glManager_->GetByName<TTFont>("Font48"), EMouse::LEFT, [&]() {});
	updateUiEntities_.push_back(optionBtn);
	renderUiEntities_.push_back(optionBtn);

	UIButton* quitBtn = entityManager_->Create<UIButton>("Resource\\UI\\Quit.button", uiCamera_, glManager_->GetByName<TTFont>("Font48"), EMouse::LEFT, [&]() {});
	updateUiEntities_.push_back(quitBtn);
	renderUiEntities_.push_back(quitBtn);
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
