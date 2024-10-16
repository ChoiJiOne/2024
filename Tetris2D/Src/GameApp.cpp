#include "Assertion.h"
#include "ButtonUI.h"
#include "EntityManager.h"
#include "PanelUI.h"
#include "ResourceManager.h"
#include "RenderManager2D.h"
#include "TextUI.h"
#include "TTFont.h"
#include "UIManager.h"

#include "Board.h"
#include "GameApp.h"
#include "MainCamera2D.h"
#include "Messenger.h"
#include "Next.h"
#include "ParticleScheduler.h"
#include "Tetromino.h"
#include "TetrominoController.h"

GameApp::GameApp() : IApp("Tetris2D", 200, 200, 600, 800, false, false)
{
}

GameApp::~GameApp()
{
}

void GameApp::Startup()
{
	LoadResource();

	EntityManager& entityMgr = EntityManager::Get();

	mainCamera_ = entityMgr.Create<MainCamera2D>();
	entityMgr.Register("MainCamera", mainCamera_);
	
	LoadTitleStatusEntities();
	LoadGamePlayStatusEntities();
}

void GameApp::Shutdown()
{
	EntityManager::Get().Destroy(mainCamera_);
	mainCamera_ = nullptr;
}

void GameApp::Run()
{
	RunLoop(
		[&](float deltaSeconds)
		{
			StatusEntities& statusEntities = statusEntities_.at(status_);

			// 2D 엔티티 업데이트
			for (auto& entity : statusEntities.updateEntities_)
			{
				entity->Tick(deltaSeconds);
			}

			// UI 엔티티 업데이트
			IEntityUI** uiEntities = statusEntities.uiEntities_.data();
			uint32_t uiEntityCount = static_cast<uint32_t>(statusEntities.uiEntities_.size());
			UIManager::Get().BatchTickUIEntity(uiEntities, uiEntityCount, deltaSeconds);

			BeginFrame(0.0f, 0.0f, 0.0f, 1.0f);

			IEntity2D** renderEntities = statusEntities.renderEntities_.data();
			uint32_t renderEntityCount = static_cast<uint32_t>(statusEntities.renderEntities_.size());

			RenderManager2D::Get().BatchRenderEntities(mainCamera_, renderEntities, renderEntityCount);
			UIManager::Get().BatchRenderUIEntity(uiEntities, uiEntityCount);
			
			EndFrame();
		}
	);
}

void GameApp::LoadResource()
{
	ResourceManager& resourceMgr = ResourceManager::Get();
	std::string resourcePath = "Tetris2D\\Res\\";

	std::string fontPath = resourcePath + "Font\\SeoulNamsanEB.ttf";
	std::array<int32_t, 2> fontSizes = { 32, 128, };
	for (const auto& fontSize : fontSizes)
	{
		TTFont* font = resourceMgr.Create<TTFont>(fontPath, 0x00, 0x128, static_cast<float>(fontSize));
		resourceMgr.Register(GameUtils::PrintF("Font%d", fontSize), font);
	}
}

void GameApp::LoadTitleStatusEntities()
{
	EntityManager& entityMgr = EntityManager::Get();

	TTFont* font32 = ResourceManager::Get().GetByName<TTFont>("Font32");
	TTFont* font128 = ResourceManager::Get().GetByName<TTFont>("Font128");

	TextUI* title = UIManager::Get().Create(L"TETRIS2D", font128, Vec2f(0.0f, 200.0f), Vec4f(1.0f, 1.0f, 1.0f, 1.0f));
	ButtonUI* startBtn = UIManager::Get().Create("Tetris2D\\Res\\Button\\Start.button", Mouse::LEFT, font32, [&]() { status_ = Status::GAMEPLAY; });
	ButtonUI* quitBtn = UIManager::Get().Create("Tetris2D\\Res\\Button\\Quit.button", Mouse::LEFT, font32, [&]() { bIsQuit_ = true; });

	StatusEntities statusEntities;
	statusEntities.updateEntities_ = 
	{
		mainCamera_,
	};
	statusEntities.uiEntities_ =
	{ 
		title,
		startBtn,
		quitBtn,
	};

	statusEntities_.insert({ Status::TITLE, statusEntities });
}

void GameApp::LoadGamePlayStatusEntities()
{
	EntityManager& entityMgr = EntityManager::Get();
	
	ParticleScheduler* particleScheduler = entityMgr.Create<ParticleScheduler>();
	entityMgr.Register("ParticleScheduler", particleScheduler);

	Next* next = entityMgr.Create<Next>();
	entityMgr.Register("Next", next);
	
	Messenger* messenger = entityMgr.Create<Messenger>();
	entityMgr.Register("Messenger", messenger);

	Board* board = entityMgr.Create<Board>(Vec2f(-50.0f, 0.0f), 30.0f, 10, 20);
	entityMgr.Register("Board", board);

	TetrominoController* tetrominoController = entityMgr.Create<TetrominoController>();
	entityMgr.Register("TetrominoController", tetrominoController);

	TTFont* font32 = ResourceManager::Get().GetByName<TTFont>("Font32");
	TextUI* nextText = UIManager::Get().Create(L"NEXT", font32, Vec2f(195.0f, 140.0f), Vec4f(1.0f, 1.0f, 1.0f, 1.0f));
	TextUI* scoreText = UIManager::Get().Create(L"SCORE", font32, Vec2f(195.0f, 0.0f), Vec4f(1.0f, 1.0f, 1.0f, 1.0f));
	PanelUI* score = UIManager::Get().Create("Tetris2D\\Res\\Panel\\Score.panel", font32);
	entityMgr.Register("Score", score);

	StatusEntities statusEntities;
	statusEntities.updateEntities_ =
	{
		mainCamera_,
		tetrominoController,
		board,
		particleScheduler,
		messenger,
	};
	statusEntities.renderEntities_ =
	{ 
		board,
		next,
		tetrominoController,
		particleScheduler,
		messenger,
	};
	statusEntities.uiEntities_ =
	{
		nextText,
		scoreText,
		score,
	};

	statusEntities_.insert({ Status::GAMEPLAY, statusEntities });
}