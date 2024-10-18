#include "Assertion.h"
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
#include "GamePauseScene2D.h"
#include "GameOverScene2D.h"
#include "GamePlayScene2D.h"
#include "MainCamera2D.h"
#include "Messenger.h"
#include "Next.h"
#include "Particle.h"
#include "ParticleScheduler.h"
#include "Tetromino.h"
#include "TetrominoController.h"

GamePlayScene2D::GamePlayScene2D()
{
	auto gamePauseEvent = [&]() 
		{
			bIsSwitched_ = true;

			GamePauseScene2D* scene = IApp::Get()->GetSceneByName<GamePauseScene2D>("GamePauseScene");
			switchScene_ = scene;
		};

	windowEventIDs_ = 
	{
		InputManager::GetRef().AddWindowEventAction(WindowEvent::FOCUS_LOST, gamePauseEvent, false),
		InputManager::GetRef().AddWindowEventAction(WindowEvent::MOVED, gamePauseEvent, false),
		InputManager::GetRef().AddWindowEventAction(WindowEvent::MINIMIZED, gamePauseEvent, false),
	};

	mainCamera_ = entityMgr_->GetByName<MainCamera2D>("MainCamera");

	ParticleScheduler* particleScheduler = entityMgr_->Create<ParticleScheduler>();
	entityMgr_->Register("ParticleScheduler", particleScheduler);

	Next* next = entityMgr_->Create<Next>();
	entityMgr_->Register("Next", next);

	Messenger* messenger = entityMgr_->Create<Messenger>();
	entityMgr_->Register("Messenger", messenger);

	Board* board = entityMgr_->Create<Board>(Vec2f(-50.0f, 0.0f), 30.0f, 10, 20);
	entityMgr_->Register("Board", board);

	TetrominoController* tetrominoController = entityMgr_->Create<TetrominoController>();
	entityMgr_->Register("TetrominoController", tetrominoController);

	TTFont* font32 = resourceMgr_->GetByName<TTFont>("Font32");

	TextUI* nextText = uiMgr_->CreateTextUI("Tetris2D\\Res\\UI\\Next.ui", font32);
	entityMgr_->Register("NextText", nextText);

	TextUI* scoreText = uiMgr_->CreateTextUI("Tetris2D\\Res\\UI\\ScoreText.ui", font32);
	entityMgr_->Register("ScoreText", scoreText);

	PanelUI* score = uiMgr_->CreatePanelUI("Tetris2D\\Res\\UI\\ScorePanel.ui", font32);
	entityMgr_->Register("Score", score);

	updateEntities_.push_back(mainCamera_);
	updateEntities_.push_back(tetrominoController);
	updateEntities_.push_back(board);
	updateEntities_.push_back(particleScheduler);
	updateEntities_.push_back(messenger);

	renderEntities_.push_back(board);
	renderEntities_.push_back(next);
	renderEntities_.push_back(tetrominoController);
	renderEntities_.push_back(particleScheduler);
	renderEntities_.push_back(messenger);

	uiEntities_.push_back(nextText);
	uiEntities_.push_back(scoreText);
	uiEntities_.push_back(score);

	tetrominoController_ = tetrominoController;
}

GamePlayScene2D::~GamePlayScene2D()
{
}

void GamePlayScene2D::Tick(float deltaSeconds)
{
	IGameScene2D::Tick(deltaSeconds);

	if (tetrominoController_->GetStatus() == TetrominoController::Status::DONE)
	{
		bIsSwitched_ = true;

		GameOverScene2D* scene = IApp::Get()->GetSceneByName<GameOverScene2D>("GameOverScene");
		switchScene_ = scene;
	}
}

void GamePlayScene2D::Enter()
{
	for (const auto& windowEventID : windowEventIDs_)
	{
		InputManager::GetRef().SetActiveWindowEventAction(windowEventID, true);
	}

	IGameScene2D::Enter();
}

void GamePlayScene2D::Exit()
{
	for (const auto& windowEventID : windowEventIDs_)
	{
		InputManager::GetRef().SetActiveWindowEventAction(windowEventID, false);
	}

	IGameScene2D::Exit();
}

void GamePlayScene2D::Reset()
{
	ParticleScheduler* particleScheduler = entityMgr_->GetByName<ParticleScheduler>("ParticleScheduler");
	particleScheduler->Reset();

	Messenger* messenger = entityMgr_->GetByName<Messenger>("Messenger");
	messenger->Reset();

	Board* board = entityMgr_->GetByName<Board>("Board");
	board->Reset();

	TetrominoController* tetrominoController = entityMgr_->GetByName<TetrominoController>("TetrominoController");
	tetrominoController->Reset();
}
