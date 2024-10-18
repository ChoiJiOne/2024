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

#include "Block.h"
#include "Board.h"
#include "GameOverScene2D.h"
#include "GamePlayScene2D.h"
#include "GameTitleScene2D.h"
#include "MainCamera2D.h"
#include "Messenger.h"
#include "Next.h"
#include "Particle.h"
#include "ParticleScheduler.h"
#include "Tetromino.h"
#include "TetrominoController.h"

GameOverScene2D::GameOverScene2D()
{
	mainCamera_ = entityMgr_->GetByName<MainCamera2D>("MainCamera");

	ParticleScheduler* particleScheduler = entityMgr_->GetByName<ParticleScheduler>("ParticleScheduler");
	Next* next = entityMgr_->GetByName<Next>("Next");
	Board* board = entityMgr_->GetByName<Board>("Board");
	TetrominoController* tetrominoController = entityMgr_->GetByName<TetrominoController>("TetrominoController");

	TTFont* font64 = resourceMgr_->GetByName<TTFont>("Font64");
	TextUI* gameOver = uiMgr_->CreateTextUI("Tetris2D\\Res\\UI\\GameOver.ui", font64);

	TTFont* font32 = resourceMgr_->GetByName<TTFont>("Font32");
	ButtonUI* resetBtn = uiMgr_->CreateButtonUI("Tetris2D\\Res\\UI\\Reset_GameOverScene2D.ui", Mouse::LEFT, font32,
		[&]()
		{
			bIsSwitched_ = true;

			GamePlayScene2D* scene = IApp::Get()->GetSceneByName<GamePlayScene2D>("GamePlayScene");
			scene->Reset();

			switchScene_ = scene;
		}
	);
	ButtonUI* quitBtn = uiMgr_->CreateButtonUI("Tetris2D\\Res\\UI\\Quit_GameOverScene2D.ui", Mouse::LEFT, font32,
		[&]()
		{
			bIsSwitched_ = true;

			GameTitleScene2D* scene = IApp::Get()->GetSceneByName<GameTitleScene2D>("GameTitleScene");
			switchScene_ = scene;
		}
	);

	renderEntities_.push_back(board);
	renderEntities_.push_back(next);
	renderEntities_.push_back(tetrominoController);
	renderEntities_.push_back(particleScheduler);

	uiEntities_.push_back(gameOver);
	uiEntities_.push_back(resetBtn);
	uiEntities_.push_back(quitBtn);
}

GameOverScene2D::~GameOverScene2D()
{
}