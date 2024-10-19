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

#include "GameHistoryScene2D.h"
#include "GameTitleScene2D.h"
#include "MainCamera2D.h"

GameHistoryScene2D::GameHistoryScene2D()
{
	mainCamera_ = entityMgr_->GetByName<MainCamera2D>("MainCamera");

	TTFont* font32 = resourceMgr_->GetByName<TTFont>("Font32");
	ButtonUI* backBtn = uiMgr_->CreateButtonUI("Tetris2D\\Res\\UI\\Back.ui", Mouse::LEFT, font32, [&]() { Switch<GameTitleScene2D>("GameTitleScene"); });

	updateEntities_.push_back(mainCamera_);

	uiEntities_.push_back(backBtn);
}

GameHistoryScene2D::~GameHistoryScene2D()
{
}

void GameHistoryScene2D::Enter()
{
	IGameScene2D::Enter();
}