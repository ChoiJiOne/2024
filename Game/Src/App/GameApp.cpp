#include "App/GameApp.h"
#include "Scene/GameDevScene.h"
#include "Scene/SceneManager.h"

GameApp::GameApp() 
	: IApp(windowWidth_, windowHeight_, windowTitle_, bIsWindowCentered_)
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
