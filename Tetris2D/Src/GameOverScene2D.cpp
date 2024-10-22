#include "Assertion.h"
#include "ButtonUI.h"
#include "EntityManager.h"
#include "IApp.h"
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
#include "GameOverScene2D.h"
#include "GamePlayScene2D.h"
#include "GameTitleScene2D.h"
#include "HighScoreViewer.h"
#include "MainCamera2D.h"

GameOverScene2D::GameOverScene2D()
{
	mainCamera_ = entityMgr_->GetByName<MainCamera2D>("MainCamera");

	Background* background = entityMgr_->GetByName<Background>("Background");

	HighScoreViewer* highScoreViewer = entityMgr_->Create<HighScoreViewer>();
	entityMgr_->Register("HighScoreViewer", highScoreViewer);

	TTFont* font64 = resourceMgr_->GetByName<TTFont>("Font64");
	TextUI* gameOver = uiMgr_->CreateTextUI("Tetris2D\\Res\\UI\\GameOver.ui", font64);

	TTFont* font32 = resourceMgr_->GetByName<TTFont>("Font32");
	ButtonUI* resetBtn = uiMgr_->CreateButtonUI("Tetris2D\\Res\\UI\\Reset_GameOverScene2D.ui", Mouse::LEFT, font32,
		[&]()
		{
			GamePlayScene2D* scene = Switch<GamePlayScene2D>("GamePlayScene");
			scene->Reset();
		}
	);
	ButtonUI* quitBtn = uiMgr_->CreateButtonUI("Tetris2D\\Res\\UI\\Quit_GameOverScene2D.ui", Mouse::LEFT, font32, [&]() { Switch<GameTitleScene2D>("GameTitleScene"); });

	updateEntities_.push_back(highScoreViewer);

	renderEntities_.push_back(background);
	renderEntities_.push_back(highScoreViewer);

	uiEntities_.push_back(gameOver);
	uiEntities_.push_back(resetBtn);
	uiEntities_.push_back(quitBtn);
}

GameOverScene2D::~GameOverScene2D()
{
}

void GameOverScene2D::Enter()
{
	HighScoreViewer* highScoreViewer = entityMgr_->GetByName<HighScoreViewer>("HighScoreViewer");
	highScoreViewer->UpdateRecentState();

	IGameScene2D::Enter();
}