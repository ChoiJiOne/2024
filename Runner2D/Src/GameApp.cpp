#include "Assertion.h"
#include "Atlas2D.h"
#include "Camera2D.h"
#include "EntityManager.h"
#include "RenderManager2D.h"
#include "ResourceManager.h"
#include "Texture2D.h"
#include "TTFont.h"

#include "Background.h"
#include "Box.h"
#include "Camera.h"
#include "Floor.h"
#include "GameApp.h"
#include "Player.h"
#include "Spawner.h"

GameApp::GameApp() : IApp("Runner2D", 100, 100, 800, 600, false, false)
{
}

GameApp::~GameApp()
{
}

void GameApp::Startup()
{
	LoadResource();

	Camera* camera = EntityManager::Get().Create<Camera>();
	EntityManager::Get().Register("Camera", camera);

	Player* player = EntityManager::Get().Create<Player>();
	EntityManager::Get().Register("Player", player);

	Background* background = EntityManager::Get().Create<Background>();
	EntityManager::Get().Register("Background", background);

	Floor* floor = EntityManager::Get().Create<Floor>();
	EntityManager::Get().Register("Floor", floor);

	Spawner* spawner = EntityManager::Get().Create<Spawner>();
	EntityManager::Get().Register("Spawner", spawner);

	camera_ = camera;

	updateEntities_ =
	{
		camera,
		player,
		background,
		floor,
		spawner,
	};

	renderEntities_ =
	{
		background,
		floor,
		spawner,
		player,
	};
}

void GameApp::Shutdown()
{
	EntityManager::Get().Destroy(camera_);
	camera_ = nullptr;
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
			{
				for (auto& entity : renderEntities_)
				{
					entity->Render();
				}
			}
			RenderManager2D::Get().End();
			EndFrame();
		}
	);
}

void GameApp::LoadResource()
{
	resourceRootPath_ = "Runner2D\\Res\\";
	
	Atlas2D* atlas = ResourceManager::Get().Create<Atlas2D>(resourceRootPath_ + "Atlas\\Atlas.png", resourceRootPath_ + "Atlas\\Atlas.json", Texture2D::Filter::NEAREST);
	ResourceManager::Get().Register("Atlas", atlas);

	std::string fontPath = resourceRootPath_ + "Font\\Yolk.ttf";
	std::array<int32_t, 4> fontSizes = { 16, 24, 32, 64 };
	for (const auto& fontSize : fontSizes)
	{
		TTFont* font = ResourceManager::Get().Create<TTFont>(fontPath, 0, 9660, static_cast<float>(fontSize));
		ResourceManager::Get().Register(GameUtils::PrintF("Font%d", fontSize), font);
	}
}