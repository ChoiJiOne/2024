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
#include "Block.h"
#include "Board.h"
#include "EmptyPanel.h"
#include "GamePauseScene2D.h"
#include "GamePlayScene2D.h"
#include "GameTitleScene2D.h"
#include "MainCamera2D.h"
#include "Messenger.h"
#include "Next.h"
#include "Particle.h"
#include "ParticleScheduler.h"
#include "Tetromino.h"
#include "TetrominoController.h"

GamePauseScene2D::GamePauseScene2D()
{
	mainCamera_ = entityMgr_->GetByName<MainCamera2D>("MainCamera");

	Background* background = entityMgr_->GetByName<Background>("Background");
	EmptyPanel* emptyPanel = entityMgr_->GetByName<EmptyPanel>("EmptyPanel");
	ParticleScheduler* particleScheduler = entityMgr_->GetByName<ParticleScheduler>("ParticleScheduler");
	Next* next = entityMgr_->GetByName<Next>("Next");
	Board* board = entityMgr_->GetByName<Board>("Board");
	TetrominoController* tetrominoController = entityMgr_->GetByName<TetrominoController>("TetrominoController");

	TextUI* nextText = entityMgr_->GetByName<TextUI>("NextText");
	TextUI* scoreText = entityMgr_->GetByName<TextUI>("ScoreText");
	PanelUI* score = entityMgr_->GetByName<PanelUI>("Score");
	TextUI* levelText = entityMgr_->GetByName<TextUI>("LevelText");
	PanelUI* level = entityMgr_->GetByName<PanelUI>("Level");
	
	TTFont* font32 = resourceMgr_->GetByName<TTFont>("Font32");
	ButtonUI* continueBtn = uiMgr_->CreateButtonUI("Tetris2D\\Res\\UI\\Continue.ui", Mouse::LEFT, font32, [&]() { Switch<GamePlayScene2D>("GamePlayScene"); });
	ButtonUI* resetBtn = uiMgr_->CreateButtonUI("Tetris2D\\Res\\UI\\Reset_GamePauseScene2D.ui", Mouse::LEFT, font32, 
		[&]() 
		{
			GamePlayScene2D* scene = Switch<GamePlayScene2D>("GamePlayScene");
			scene->Reset();
		}
	);
	ButtonUI* quitBtn = uiMgr_->CreateButtonUI("Tetris2D\\Res\\UI\\Quit_GamePauseScene2D.ui", Mouse::LEFT, font32, [&]() { Switch<GameTitleScene2D>("GameTitleScene"); });

	renderEntities_.push_back(background);
	renderEntities_.push_back(emptyPanel);
	renderEntities_.push_back(board);
	renderEntities_.push_back(next);
	renderEntities_.push_back(tetrominoController);
	renderEntities_.push_back(particleScheduler);

	uiEntities_.push_back(nextText);
	uiEntities_.push_back(scoreText);
	uiEntities_.push_back(score);
	uiEntities_.push_back(levelText);
	uiEntities_.push_back(level);
	uiEntities_.push_back(continueBtn);
	uiEntities_.push_back(resetBtn);
	uiEntities_.push_back(quitBtn);
}

GamePauseScene2D::~GamePauseScene2D()
{
}