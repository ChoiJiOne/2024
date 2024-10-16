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
	entityMgr_ = EntityManager::GetPtr();
	render2dMgr_ = RenderManager2D::GetPtr();
	resourceMgr_ = ResourceManager::GetPtr();
	uiMgr_ = UIManager::GetPtr();
}

GameApp::~GameApp()
{
	uiMgr_ = nullptr;
	resourceMgr_ = nullptr;
	render2dMgr_ = nullptr;
	entityMgr_ = nullptr;
}

void GameApp::Startup()
{
	LoadResource();

	mainCamera_ = entityMgr_->Create<MainCamera2D>();
	entityMgr_->Register("MainCamera", mainCamera_);
	
	LoadTitleStatusEntities();
	LoadGamePlayStatusEntities();
}

void GameApp::Shutdown()
{
	entityMgr_->Destroy(mainCamera_);
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
			uiMgr_->BatchTickUIEntity(uiEntities, uiEntityCount, deltaSeconds);

			BeginFrame(0.0f, 0.0f, 0.0f, 1.0f);

			IEntity2D** renderEntities = statusEntities.renderEntities_.data();
			uint32_t renderEntityCount = static_cast<uint32_t>(statusEntities.renderEntities_.size());

			render2dMgr_->BatchRenderEntities(mainCamera_, renderEntities, renderEntityCount);
			uiMgr_->BatchRenderUIEntity(uiEntities, uiEntityCount);
			
			EndFrame();
		}
	);
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

void GameApp::LoadTitleStatusEntities()
{
	TTFont* font32 = resourceMgr_->GetByName<TTFont>("Font32");
	TTFont* font128 = resourceMgr_->GetByName<TTFont>("Font128");

	TextUI* title = uiMgr_->CreateTextUI("Tetris2D\\Res\\UI\\Title.ui", font128);
	ButtonUI* startBtn = uiMgr_->CreateButtonUI("Tetris2D\\Res\\UI\\Start.ui", Mouse::LEFT, font32, [&]() { status_ = Status::GAMEPLAY; });
	ButtonUI* quitBtn = uiMgr_->CreateButtonUI("Tetris2D\\Res\\UI\\Quit.ui", Mouse::LEFT, font32, [&]() { bIsQuit_ = true; });

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
	TextUI* scoreText = uiMgr_->CreateTextUI("Tetris2D\\Res\\UI\\ScoreText.ui", font32);
	PanelUI* score = uiMgr_->CreatePanelUI("Tetris2D\\Res\\UI\\ScorePanel.ui", font32);
	entityMgr_->Register("Score", score);

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