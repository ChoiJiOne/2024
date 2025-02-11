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

#include "Background.h"
#include "Block.h"
#include "Board.h"
#include "EmptyPanel.h"
#include "GameHistoryTracker.h"
#include "GamePauseScene2D.h"
#include "GameOverScene2D.h"
#include "GamePlayScene2D.h"
#include "MainCamera2D.h"
#include "Messenger.h"
#include "Next.h"
#include "Particle.h"
#include "ParticleScheduler.h"
#include "UserState.h"
#include "Tetromino.h"
#include "TetrominoController.h"

GamePlayScene2D::GamePlayScene2D()
{
	auto gamePauseEvent = [&]() 
		{ 
			Switch<GamePauseScene2D>("GamePauseScene");
		};

	windowEventIDs_ = 
	{
		InputManager::GetRef().AddWindowEventAction(WindowEvent::FOCUS_LOST, gamePauseEvent, false),
		InputManager::GetRef().AddWindowEventAction(WindowEvent::MOVED, gamePauseEvent, false),
		InputManager::GetRef().AddWindowEventAction(WindowEvent::MINIMIZED, gamePauseEvent, false),
	};

	mainCamera_ = entityMgr_->GetByName<MainCamera2D>("MainCamera");

	Background* background = entityMgr_->GetByName<Background>("Background");

	EmptyPanel* emptyPanel = entityMgr_->Create<EmptyPanel>();
	entityMgr_->Register("EmptyPanel", emptyPanel);

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

	UserState* userState = entityMgr_->Create<UserState>();
	entityMgr_->Register("UserState", userState);

	TTFont* font32 = resourceMgr_->GetByName<TTFont>("Font32");

	TextUI* nextText = uiMgr_->CreateTextUI("Resource\\UI\\Next.ui", font32);
	entityMgr_->Register("NextText", nextText);

	TextUI* scoreText = uiMgr_->CreateTextUI("Resource\\UI\\ScoreText.ui", font32);
	entityMgr_->Register("ScoreText", scoreText);

	PanelUI* score = uiMgr_->CreatePanelUI("Resource\\UI\\ScorePanel.ui", font32);
	entityMgr_->Register("Score", score);

	TextUI* levelText = uiMgr_->CreateTextUI("Resource\\UI\\LevelText.ui", font32);
	entityMgr_->Register("LevelText", levelText);

	PanelUI* level = uiMgr_->CreatePanelUI("Resource\\UI\\LevelPanel.ui", font32);
	entityMgr_->Register("Level", level);

	updateEntities_.push_back(mainCamera_);
	updateEntities_.push_back(tetrominoController);
	updateEntities_.push_back(board);
	updateEntities_.push_back(particleScheduler);
	updateEntities_.push_back(userState);
	updateEntities_.push_back(messenger);

	renderEntities_.push_back(background);
	renderEntities_.push_back(emptyPanel);
	renderEntities_.push_back(board);
	renderEntities_.push_back(next);
	renderEntities_.push_back(tetrominoController);
	renderEntities_.push_back(particleScheduler);
	renderEntities_.push_back(messenger);

	uiEntities_.push_back(nextText);
	uiEntities_.push_back(scoreText);
	uiEntities_.push_back(score);
	uiEntities_.push_back(levelText);
	uiEntities_.push_back(level);

	tetrominoController_ = tetrominoController;
	userState_ = userState;
	gameHistoryTracker_ = entityMgr_->GetByName<GameHistoryTracker>("GameHistoryTracker");
}

GamePlayScene2D::~GamePlayScene2D()
{
}

void GamePlayScene2D::Tick(float deltaSeconds)
{
	IGameScene2D::Tick(deltaSeconds);

	if (tetrominoController_->GetStatus() == TetrominoController::Status::DONE)
	{
		gameHistoryTracker_->AddScore(userState_->GetScore());
		Switch<GameOverScene2D>("GameOverScene");
	}

	if (IsPauseGame())
	{
		Switch<GamePauseScene2D>("GamePauseScene");
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

	MainCamera2D* mainCamera = entityMgr_->GetByName<MainCamera2D>("MainCamera");
	mainCamera->Reset();

	IGameScene2D::Exit();
}

void GamePlayScene2D::Reset()
{
	MainCamera2D* mainCamera = entityMgr_->GetByName<MainCamera2D>("MainCamera");
	mainCamera->Reset();

	ParticleScheduler* particleScheduler = entityMgr_->GetByName<ParticleScheduler>("ParticleScheduler");
	particleScheduler->Reset();

	Messenger* messenger = entityMgr_->GetByName<Messenger>("Messenger");
	messenger->Reset();

	Board* board = entityMgr_->GetByName<Board>("Board");
	board->Reset();

	UserState* userState = entityMgr_->GetByName<UserState>("UserState");
	userState->Reset();

	TetrominoController* tetrominoController = entityMgr_->GetByName<TetrominoController>("TetrominoController");
	tetrominoController->Reset();
}

bool GamePlayScene2D::IsPauseGame()
{
	return InputManager::GetRef().GetKeyPress(Key::KEY_ESCAPE) == Press::PRESSED;
}