#include "Assertion.h"
#include "ButtonUI.h"
#include "EntityManager.h"
#include "IApp.h"
#include "InputManager.h"
#include "IEntity.h"
#include "IEntity2D.h"
#include "IEntityUI.h"
#include "PanelUI.h"
#include "ResourceManager.h"
#include "RenderManager2D.h"
#include "TextUI.h"
#include "TTFont.h"
#include "UIManager.h"

#include "GamePlayScene2D.h"
#include "MainCamera2D.h"
#include "TitleScene2D.h"

TitleScene2D::TitleScene2D()
{
	mainCamera_ = entityMgr_->GetByName<MainCamera2D>("MainCamera");

	TTFont* font32 = resourceMgr_->GetByName<TTFont>("Font32");
	TTFont* font128 = resourceMgr_->GetByName<TTFont>("Font128");

	TextUI* title = uiMgr_->CreateTextUI("Tetris2D\\Res\\UI\\Title.ui", font128);
	ButtonUI* startBtn = uiMgr_->CreateButtonUI("Tetris2D\\Res\\UI\\Start.ui", Mouse::LEFT, font32, 
		[&]() 
		{ 
			bIsSwitched_ = true;
			if (!switchScene_)
			{
				GamePlayScene2D* scene = IApp::Get()->GetSceneByName<GamePlayScene2D>("GamePlayScene");
				switchScene_ = scene;
			}
		}
	);
	ButtonUI* quitBtn = uiMgr_->CreateButtonUI("Tetris2D\\Res\\UI\\Quit.ui", Mouse::LEFT, font32, 
		[&]() 
		{  
			InputManager::GetRef().RequestQuit();
		}
	);

	updateEntities_.push_back(mainCamera_);
	uiEntities_.push_back(title);
	uiEntities_.push_back(startBtn);
	uiEntities_.push_back(quitBtn);
}

TitleScene2D::~TitleScene2D()
{
}

void TitleScene2D::Tick(float deltaSeconds)
{
	for (auto& entity : updateEntities_)
	{
		entity->Tick(deltaSeconds);
	}

	for (auto& uiEntity : uiEntities_)
	{
		uiEntity->Tick(deltaSeconds);
	}
}

void TitleScene2D::Render()
{
	renderStateMgr_->BeginFrame(0.0f, 0.0f, 0.0f, 1.0f);
	{// 2D ¿£Æ¼Æ¼ ·»´õ¸µ
		render2dMgr_->Begin(mainCamera_);
		{
			for (auto& entity : renderEntities_)
			{
				entity->Render();
			}
		}
		render2dMgr_->End();
	}
	{// UI ·»´õ¸µ
		IEntityUI** uiEntities = uiEntities_.data();
		uint32_t uiEntityCount = static_cast<uint32_t>(uiEntities_.size());
		uiMgr_->BatchRenderUIEntity(uiEntities, uiEntityCount);
	}
	renderStateMgr_->EndFrame();
}

void TitleScene2D::Enter()
{
	bIsEnter_ = true;
	bIsSwitched_ = false;
}

void TitleScene2D::Exit()
{
	bIsEnter_ = false;
	bIsSwitched_ = false;
}