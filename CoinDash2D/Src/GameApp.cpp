#include "Assertion.h"
#include "Atlas2D.h"
#include "EntityManager.h"
#include "RenderManager2D.h"
#include "ResourceManager.h"
#include "Texture2D.h"

#include "Background.h"
#include "Camera.h"
#include "Entity2D.h"
#include "GameApp.h"

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

	updateEntities_ = 
	{
		camera_,
		background,
	};

	renderEntities_ = 
	{
		background,
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
