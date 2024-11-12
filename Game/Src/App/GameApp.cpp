#include "App/GameApp.h"
#include "Scene/GameDevScene.h"
#include "Scene/SceneManager.h"

GameApp::GameApp() 
	: IApp(windowWidth_, windowHeight_, "HyperCoinDash2D", bIsWindowCentered_)
{
}

GameApp::~GameApp()
{
}

void GameApp::Startup()
{
	GameDevScene* devScene = SceneManager::GetRef().Create<GameDevScene>();

	SetAppScene(devScene);
}

void GameApp::Shutdown()
{
}
