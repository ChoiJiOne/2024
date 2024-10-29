#include "Assertion.h"
#include "RenderStateManager.h"

#include "GameScene.h"

GameScene::GameScene()
{
}

GameScene::~GameScene()
{
}

void GameScene::Tick(float deltaSeconds)
{
}

void GameScene::Render()
{
	RenderStateManager::GetRef().BeginFrame(1.0f, 0.0f, 0.0f, 1.0f);
	{

	}
	RenderStateManager::GetRef().EndFrame();
}

void GameScene::Enter()
{
	bIsEnter_ = true;
}

void GameScene::Exit()
{
	bIsSwitched_ = false;
	bIsEnter_ = false;
}
