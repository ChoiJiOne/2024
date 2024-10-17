#include "Assertion.h"
#include "ButtonUI.h"
#include "EntityManager.h"
#include "GameUtils.h"
#include "PanelUI.h"
#include "ResourceManager.h"
#include "RenderManager2D.h"
#include "TextUI.h"
#include "TTFont.h"
#include "UIManager.h"

#include "GameApp.h"
#include "MainCamera2D.h"
#include "TitleScene2D.h"

GameApp::GameApp() : IApp("Tetris2D", 200, 200, 600, 800, false, false)
{
	entityMgr_ = EntityManager::GetPtr();
	resourceMgr_ = ResourceManager::GetPtr();
}

GameApp::~GameApp()
{
	resourceMgr_ = nullptr;
	entityMgr_ = nullptr;
}

void GameApp::Startup()
{
	LoadResource();

	MainCamera2D* mainCamera = entityMgr_->Create<MainCamera2D>();
	entityMgr_->Register("MainCamera", mainCamera);

	titleScene_ = std::make_unique<TitleScene2D>();

	SetCurrentScene(titleScene_.get());
}

void GameApp::Shutdown()
{
	titleScene_.reset();
}

void GameApp::LoadResource()
{
	std::string resourcePath = "Tetris2D\\Res\\";
	std::string fontPath = resourcePath + "Font\\SeoulNamsanEB.ttf";
	std::array<int32_t, 2> fontSizes = { 32, 128, };
	for (const auto& fontSize : fontSizes)
	{
		TTFont* font = resourceMgr_->Create<TTFont>(fontPath, 0x00, 0x128, static_cast<float>(fontSize));
		resourceMgr_->Register(GameUtils::PrintF("Font%d", fontSize), font);
	}
}

//void GameApp::LoadTitleStatusEntities()
//{
//	TTFont* font32 = resourceMgr_->GetByName<TTFont>("Font32");
//	TTFont* font128 = resourceMgr_->GetByName<TTFont>("Font128");
//
//	TextUI* title = uiMgr_->CreateTextUI("Tetris2D\\Res\\UI\\Title.ui", font128);
//	ButtonUI* startBtn = uiMgr_->CreateButtonUI("Tetris2D\\Res\\UI\\Start.ui", Mouse::LEFT, font32, [&]() { status_ = Status::GAMEPLAY; });
//	ButtonUI* quitBtn = uiMgr_->CreateButtonUI("Tetris2D\\Res\\UI\\Quit.ui", Mouse::LEFT, font32, [&]() { bIsQuit_ = true; });
//
//	StatusEntities statusEntities;
//	statusEntities.updateEntities_ = 
//	{
//		mainCamera_,
//	};
//	statusEntities.uiEntities_ =
//	{ 
//		title,
//		startBtn,
//		quitBtn,
//	};
//
//	statusEntities_.insert({ Status::TITLE, statusEntities });
//}

//void GameApp::LoadGamePlayStatusEntities()
//{
//	ParticleScheduler* particleScheduler = entityMgr_->Create<ParticleScheduler>();
//	entityMgr_->Register("ParticleScheduler", particleScheduler);
//
//	Next* next = entityMgr_->Create<Next>();
//	entityMgr_->Register("Next", next);
//	
//	Messenger* messenger = entityMgr_->Create<Messenger>();
//	entityMgr_->Register("Messenger", messenger);
//
//	Board* board = entityMgr_->Create<Board>(Vec2f(-50.0f, 0.0f), 30.0f, 10, 20);
//	entityMgr_->Register("Board", board);
//
//	TetrominoController* tetrominoController = entityMgr_->Create<TetrominoController>();
//	entityMgr_->Register("TetrominoController", tetrominoController);
//
//	TTFont* font32 = resourceMgr_->GetByName<TTFont>("Font32");
//	TextUI* nextText = uiMgr_->CreateTextUI("Tetris2D\\Res\\UI\\Next.ui", font32);
//	TextUI* scoreText = uiMgr_->CreateTextUI("Tetris2D\\Res\\UI\\ScoreText.ui", font32);
//	PanelUI* score = uiMgr_->CreatePanelUI("Tetris2D\\Res\\UI\\ScorePanel.ui", font32);
//	entityMgr_->Register("Score", score);
//
//	StatusEntities statusEntities;
//	statusEntities.updateEntities_ =
//	{
//		mainCamera_,
//		tetrominoController,
//		board,
//		particleScheduler,
//		messenger,
//	};
//	statusEntities.renderEntities_ =
//	{ 
//		board,
//		next,
//		tetrominoController,
//		particleScheduler,
//		messenger,
//	};
//	statusEntities.uiEntities_ =
//	{
//		nextText,
//		scoreText,
//		score,
//	};
//
//	statusEntities_.insert({ Status::GAMEPLAY, statusEntities });
//}