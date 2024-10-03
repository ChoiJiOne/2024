#include "Assertion.h"
#include "Camera2D.h"
#include "EntityManager.h"
#include "ResourceManager.h"
#include "RenderManager2D.h"

#include "Board.h"
#include "GameApp.h"
#include "Tetromino.h"

GameApp::GameApp() : IApp("Tetris2D", 200, 200, 600, 800, false, false)
{
}

GameApp::~GameApp()
{
}

void GameApp::Startup()
{
	EntityManager& entityMgr = EntityManager::Get();

	mainCamera_ = Camera2D::CreateScreenCamera();
	entityMgr.Register("MainCamera", mainCamera_);

	Board* board = entityMgr.Create<Board>(Vec2f(-50.0f, 0.0f), 30.0f, 10, 20);
	entityMgr.Register("Board", board);

	Tetromino* tetromino = entityMgr.Create<Tetromino>(Vec2f(0.0f, 0.0f), 27.0f, 30.0f, Tetromino::Type::Z, Vec4f(1.0f, 1.0f, 0.5f, 1.0f));

	updateEntities_ =
	{
		mainCamera_,
		tetromino,
		//board,
	};

	renderEntities_ =
	{
		//board,
		tetromino,
	};
}

void GameApp::Shutdown()
{
	EntityManager::Get().Destroy(mainCamera_);
	mainCamera_ = nullptr;
}

void GameApp::Run()
{
	float minX = -300.0f;
	float maxX = +300.0f;
	float strideX = 10.0f;
	float minY = -400.0f;
	float maxY = +400.0f;
	float strideY = 10.0f;

	RunLoop(
		[&](float deltaSeconds)
		{
			for (auto& entity : updateEntities_)
			{
				entity->Tick(deltaSeconds);
			}

			BeginFrame(0.0f, 0.0f, 0.0f, 1.0f);

			RenderManager2D::Get().Begin(mainCamera_);
			{
				for (float x = minX; x <= maxX; x += strideX)
				{
					Vec4f color = (x == 0.0f) ? Vec4f(0.0f, 0.0f, 1.0f, 1.0f) : Vec4f(0.5f, 0.5f, 0.5f, 0.5f);
					RenderManager2D::Get().DrawLine(Vec2f(x, minY), Vec2f(x, maxY), color);
				}

				for (float y = minY; y <= maxY; y += strideY)
				{
					Vec4f color = (y == 0.0f) ? Vec4f(1.0f, 0.0f, 0.0f, 1.0f) : Vec4f(0.5f, 0.5f, 0.5f, 0.5f);
					RenderManager2D::Get().DrawLine(Vec2f(minX, y), Vec2f(maxX, y), color);
				}
			}
			RenderManager2D::Get().End();

			RenderManager2D::Get().BatchRenderEntities(mainCamera_, renderEntities_.data(), renderEntities_.size());

			EndFrame();
		}
	);
}