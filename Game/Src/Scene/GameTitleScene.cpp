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

	Initailize();
}

GameTitleScene::~GameTitleScene()
{
	UnInitailize();
}

void GameTitleScene::Tick(float deltaSeconds)
{
	for (auto& uiEntity : updateUiEntities_)
	{
		uiEntity.second->Tick(deltaSeconds);
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
				uiEntity.second->Render();
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

void GameTitleScene::Initailize()
{
	uiCamera_ = entityManager_->GetByName<UICamera>("UICamera");
	updateUiEntities_.insert({ "UICamera", uiCamera_ });

	Backdrop* backdrop = entityManager_->Create<Backdrop>();
	updateUiEntities_.insert({ "Backdrop", backdrop });
	renderUiEntities_.insert({ "Backdrop", backdrop });

	Title* title = entityManager_->Create<Title>();
	updateUiEntities_.insert({ "Title", title });
	renderUiEntities_.insert({ "Title", title });

	UIButton* startBtn = entityManager_->Create<UIButton>("Resource\\UI\\Start.button", uiCamera_, glManager_->GetByName<TTFont>("Font48"), EMouse::LEFT, [&]() {});
	updateUiEntities_.insert({ "StartButton", startBtn });
	renderUiEntities_.insert({ "StartButton", startBtn });

	UIButton* galleryBtn = entityManager_->Create<UIButton>("Resource\\UI\\Gallery.button", uiCamera_, glManager_->GetByName<TTFont>("Font48"), EMouse::LEFT, [&]() {});
	updateUiEntities_.insert({ "GalleryButton", galleryBtn });
	renderUiEntities_.insert({ "GalleryButton", galleryBtn });

	UIButton* optionBtn = entityManager_->Create<UIButton>("Resource\\UI\\Option.button", uiCamera_, glManager_->GetByName<TTFont>("Font48"), EMouse::LEFT, [&]() {});
	updateUiEntities_.insert({ "OptionButton", optionBtn });
	renderUiEntities_.insert({ "OptionButton", optionBtn });

	UIButton* quitBtn = entityManager_->Create<UIButton>("Resource\\UI\\Quit.button", uiCamera_, glManager_->GetByName<TTFont>("Font48"), EMouse::LEFT, [&]() {});
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
}
