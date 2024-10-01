#include "Assertion.h"
#include "ResourceManager.h"
#include "RenderManager2D.h"

#include "GameApp.h"

GameApp::GameApp() : IApp("Tetris2D", 200, 200, 800, 600, false, false)
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