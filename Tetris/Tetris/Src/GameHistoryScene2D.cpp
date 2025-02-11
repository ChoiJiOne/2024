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
#include "GameTitleScene2D.h"
#include "HistoryViewer.h"
#include "MainCamera2D.h"

GameHistoryScene2D::GameHistoryScene2D()
{
	mainCamera_ = entityMgr_->GetByName<MainCamera2D>("MainCamera");

	Background* background = entityMgr_->GetByName<Background>("Background");

	TTFont* font32 = resourceMgr_->GetByName<TTFont>("Font32");
	TTFont* font64 = resourceMgr_->GetByName<TTFont>("Font64");

	ButtonUI* backBtn = uiMgr_->CreateButtonUI("Resource\\UI\\Back.ui", Mouse::LEFT, font32, [&]() { Switch<GameTitleScene2D>("GameTitleScene"); });
	TextUI* historyText = uiMgr_->CreateTextUI("Resource\\UI\\HistoryText.ui", font32);
	TextUI* bestText = uiMgr_->CreateTextUI("Resource\\UI\\BestText.ui", font32);

	HistoryViewer* historyViewer = entityMgr_->Create<HistoryViewer>();
	entityMgr_->Register("HistoryViewer", historyViewer);

	updateEntities_.push_back(mainCamera_);
	updateEntities_.push_back(historyViewer);

	renderEntities_.push_back(background);
	renderEntities_.push_back(historyViewer);

	uiEntities_.push_back(historyText);
	uiEntities_.push_back(bestText);
	uiEntities_.push_back(backBtn);

	historyViewer_ = historyViewer;
}

GameHistoryScene2D::~GameHistoryScene2D()
{
}

void GameHistoryScene2D::Enter()
{
	historyViewer_->UpdateRecentHistory();

	IGameScene2D::Enter();
}