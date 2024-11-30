#include "App/GameApp.h"
#include "Entity/EntityManager.h"
#include "GL/FrameBuffer.h"
#include "GL/GLManager.h"
#include "GL/PostProcessor.h"
#include "Scene/GamePauseScene.h"
#include "Scene/GamePlayScene.h"
#include "Scene/GameTitleScene.h"
#include "Scene/SceneManager.h"
#include "Utils/Assertion.h"

GamePauseScene::GamePauseScene()
{
	sceneManager_->Register("GamePauseScene", this);

	Initailize();
}

GamePauseScene::~GamePauseScene()
{
	UnInitailize();
}

void GamePauseScene::Tick(float deltaSeconds)
{
}

void GamePauseScene::Render()
{
}

void GamePauseScene::Enter()
{
	bIsEnter_ = true;
	bIsSwitched_ = false;
}

void GamePauseScene::Exit()
{
	bIsSwitched_ = false;
	bIsEnter_ = false;
}

void GamePauseScene::Initailize()
{
	postProcessor_ = renderManager_->GetPostProcessor();
	frameBuffer_ = reinterpret_cast<GameApp*>(IApp::GetPtr())->GetFrameBuffer();
	renderTargetOption_ = RenderTargetOption{ glm::vec4(0.0f, 0.0f, 0.0f, 1.0f), true };

	gamePlayScene_ = sceneManager_->GetByName<GamePlayScene>("GamePlayScene");
}

void GamePauseScene::UnInitailize()
{
	gamePlayScene_ = nullptr;
	frameBuffer_ = nullptr;
	postProcessor_ = nullptr;
}
