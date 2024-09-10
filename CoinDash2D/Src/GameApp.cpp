#include "Assertion.h"
#include "Atlas2D.h"
#include "EntityManager.h"
#include "RenderManager2D.h"
#include "ResourceManager.h"
#include "Texture2D.h"

#include "Background.h"
#include "Cactus.h"
#include "Camera.h"
#include "CoinSpawner.h"
#include "Entity2D.h"
#include "GameApp.h"
#include "Player.h"

GameApp::GameApp() : IApp("CoinDash2D", 100, 100, 480, 720, false, false)
{
}

GameApp::~GameApp()
{
}

void GameApp::Startup()
{
	Atlas2D* atlas = ResourceManager::Get().Create<Atlas2D>("CoinDash2D\\Res\\Atlas\\Atlas.png", "CoinDash2D\\Res\\Atlas\\Atlas.json", Texture2D::Filter::NEAREST);
	ResourceManager::Get().Register("Atlas", atlas);

	camera_ = EntityManager::Get().Create<Camera>();
	EntityManager::Get().Register("Camera", camera_);

	Background* background = EntityManager::Get().Create<Background>();
	EntityManager::Get().Register("Background", background);

	Player* player = EntityManager::Get().Create<Player>();
	EntityManager::Get().Register("Player", player);

	CoinSpawner* coinSpawner = EntityManager::Get().Create<CoinSpawner>();
	EntityManager::Get().Register("CoinSpawner", coinSpawner);

	Cactus* cactus0 = EntityManager::Get().Create<Cactus>(Rect2D(GameMath::Vec2f(-120.0f, +150.0f), GameMath::Vec2f(50.0f, 60.0f)));
	EntityManager::Get().Register("Cactus0", cactus0);

	Cactus* cactus1 = EntityManager::Get().Create<Cactus>(Rect2D(GameMath::Vec2f(+120.0f, +150.0f), GameMath::Vec2f(50.0f, 60.0f)));
	EntityManager::Get().Register("Cactus1", cactus1);

	Cactus* cactus2 = EntityManager::Get().Create<Cactus>(Rect2D(GameMath::Vec2f(-120.0f, -150.0f), GameMath::Vec2f(50.0f, 60.0f)));
	EntityManager::Get().Register("Cactus2", cactus2);

	Cactus* cactus3 = EntityManager::Get().Create<Cactus>(Rect2D(GameMath::Vec2f(+120.0f, -150.0f), GameMath::Vec2f(50.0f, 60.0f)));
	EntityManager::Get().Register("Cactus3", cactus3);

	updateEntities_ = 
	{
		camera_,
		player,
		coinSpawner,
		cactus0,
		cactus1,
		cactus2,
		cactus3,
		background,
	};

	renderEntities_ = 
	{
		background,
		player,
		coinSpawner,
		cactus0,
		cactus1,
		cactus2,
		cactus3,
	};
}

void GameApp::Shutdown()
{
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

			RenderManager2D::Get().Begin(camera_);
			for (auto& entity : renderEntities_)
			{
				entity->Render();
			}
			RenderManager2D::Get().End();

			EndFrame();
		}
	);
}
