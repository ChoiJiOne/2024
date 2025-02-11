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

#include "Background.h"
#include "GameHistoryScene2D.h"
#include "GamePlayScene2D.h"
#include "GameTitleScene2D.h"
#include "MainCamera2D.h"

GameTitleScene2D::GameTitleScene2D()
{
	mainCamera_ = entityMgr_->GetByName<MainCamera2D>("MainCamera");

	Background* background = entityMgr_->GetByName<Background>("Background");

	TTFont* font32 = resourceMgr_->GetByName<TTFont>("Font32");
	TTFont* font128 = resourceMgr_->GetByName<TTFont>("Font128");

	TextUI* title = uiMgr_->CreateTextUI("Resource\\UI\\Title.ui", font128);
	ButtonUI* startBtn = uiMgr_->CreateButtonUI("Resource\\UI\\Start.ui", Mouse::LEFT, font32, 
		[&]() 
		{
			GamePlayScene2D* scene = Switch<GamePlayScene2D>("GamePlayScene");
			scene->Reset();
		}
	);
	ButtonUI* historyBtn = uiMgr_->CreateButtonUI("Resource\\UI\\History.ui", Mouse::LEFT, font32,
		[&] 
		{
			Switch<GameHistoryScene2D>("GameHistoryScene");
		}
	);
	ButtonUI* quitBtn = uiMgr_->CreateButtonUI("Resource\\UI\\Quit_GameTitleScene2D.ui", Mouse::LEFT, font32, 
		[&]() 
		{  
			InputManager::GetRef().RequestQuit();
		}
	);

	updateEntities_.push_back(mainCamera_);

	renderEntities_.push_back(background);
	
	uiEntities_.push_back(title);
	uiEntities_.push_back(startBtn);
	uiEntities_.push_back(historyBtn);
	uiEntities_.push_back(quitBtn);
}

GameTitleScene2D::~GameTitleScene2D()
{
}