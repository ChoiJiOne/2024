#include "Assertion.h"
#include "Atlas2D.h"
#include "EntityManager.h"
#include "RenderManager2D.h"
#include "ResourceManager.h"
#include "Texture2D.h"

#include "Camera.h"
#include "GameApp.h"

GameApp::GameApp() : IApp("CoinDash2D", 100, 100, 480, 720, false, false)
{
}

GameApp::~GameApp()
{
}

void GameApp::Startup()
{
	camera_ = EntityManager::Get().Create<Camera>();
}

void GameApp::Shutdown()
{
}

void GameApp::Run()
{
	RunLoop(
		[&](float deltaSeconds)
		{
			camera_->Tick(deltaSeconds);

			BeginFrame(0.0f, 0.0f, 0.0f, 1.0f);
			EndFrame();
		}
	);
}
