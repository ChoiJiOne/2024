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
#include "GameTitleScene2D.h"
#include "MainCamera2D.h"

GameTitleScene2D::GameTitleScene2D()
{
	mainCamera_ = entityMgr_->GetByName<MainCamera2D>("MainCamera");

	TTFont* font32 = resourceMgr_->GetByName<TTFont>("Font32");
	TTFont* font128 = resourceMgr_->GetByName<TTFont>("Font128");

	TextUI* title = uiMgr_->CreateTextUI("Tetris2D\\Res\\UI\\Title.ui", font128);
	ButtonUI* startBtn = uiMgr_->CreateButtonUI("Tetris2D\\Res\\UI\\Start.ui", Mouse::LEFT, font32, 
		[&]() 
		{
			Switch<GamePlayScene2D>("GamePlayScene");

			GamePlayScene2D* scene = IApp::Get()->GetSceneByName<GamePlayScene2D>("GamePlayScene");
			scene->Reset();
		}
	);
	ButtonUI* quitBtn = uiMgr_->CreateButtonUI("Tetris2D\\Res\\UI\\Quit_GameTitleScene2D.ui", Mouse::LEFT, font32, 
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

GameTitleScene2D::~GameTitleScene2D()
{
}