#include "Assertion.h"
#include "RenderManager2D.h"
#include "ResourceManager.h"

#include "GameApp.h"

GameApp::GameApp() : IApp("CoinDash2D", 100, 100, 480, 720, false, false)
{
}

GameApp::~GameApp()
{
}

void GameApp::Startup()
{
}

void GameApp::Shutdown()
{
}

void GameApp::Run()
{
	RunLoop(
		[&](float deltaSeconds)
		{
			BeginFrame(0.0f, 0.0f, 0.0f, 1.0f);
			EndFrame();
		}
	);
}
