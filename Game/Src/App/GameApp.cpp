#include "App/GameApp.h"
#include "Scene/GamePlayScene.h"
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
	GamePlayScene* gamePlayScene = sceneManager_->Create<GamePlayScene>();
	sceneManager_->Register("GamePlayScene", gamePlayScene);

	SetAppScene(gamePlayScene);
}

void GameApp::Shutdown()
{
}
