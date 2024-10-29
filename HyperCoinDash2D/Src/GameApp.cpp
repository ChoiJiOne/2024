#include "Assertion.h"
#include "Camera2D.h"
#include "EntityManager.h"

#include "GameApp.h"
#include "GameScene.h"

GameApp::GameApp() : IApp("HyperCoinDash2D", 200, 200, 1000, 800, false, false)
{
}

GameApp::~GameApp()
{
}

void GameApp::Startup()
{
	Camera2D* mainCamera = Camera2D::CreateScreenCamera();
	EntityManager::GetRef().Register("MainCamera", mainCamera);

	gameScene_ = std::make_unique<GameScene>();
	AddSceneByName("GameScene", gameScene_.get());

	SetCurrentScene(gameScene_.get());
}

void GameApp::Shutdown()
{
	gameScene_.reset();
}
