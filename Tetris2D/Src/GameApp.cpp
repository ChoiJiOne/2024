#include "Assertion.h"
#include "EntityManager.h"
#include "ResourceManager.h"
#include "RenderManager2D.h"
#include "TTFont.h"

#include "Board.h"
#include "GameApp.h"
#include "MainCamera2D.h"
#include "Next.h"
#include "Score.h"
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

	Board* board = entityMgr.Create<Board>(Vec2f(-50.0f, 0.0f), 30.0f, 10, 20);
	entityMgr.Register("Board", board);

	TetrominoController* controller = entityMgr.Create<TetrominoController>();
	entityMgr.Register("Controller", controller);

	Next* next = entityMgr.Create<Next>();
	entityMgr.Register("Next", next);

	Score* score = entityMgr.Create<Score>();
	entityMgr.Register("Score", score);

	updateEntities_ =
	{
		mainCamera_,
		controller,
		board,
		score,
	};

	renderEntities_ =
	{
		board,
		next,
		controller,
		score,
	};
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
			for (auto& entity : updateEntities_)
			{
				entity->Tick(deltaSeconds);
			}

			BeginFrame(0.0f, 0.0f, 0.0f, 1.0f);
			
			RenderManager2D::Get().BatchRenderEntities(mainCamera_, renderEntities_.data(), renderEntities_.size());

			EndFrame();
		}
	);
}

void GameApp::LoadResource()
{
	ResourceManager& resourceMgr = ResourceManager::Get();
	std::string resourcePath = "Tetris2D\\Res\\";

	std::string fontPath = resourcePath + "Font\\SeoulNamsanEB.ttf";
	std::array<int32_t, 1> fontSizes = { 32, };
	for (const auto& fontSize : fontSizes)
	{
		TTFont* font = resourceMgr.Create<TTFont>(fontPath, 0x00, 0x128, static_cast<float>(fontSize));
		resourceMgr.Register(GameUtils::PrintF("Font%d", fontSize), font);
	}
}
