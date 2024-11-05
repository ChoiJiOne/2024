#include "GL/GLManager.h"
#include "Scene/GameDevScene.h"
#include "Utils/Assertion.h"

GameDevScene::GameDevScene()
{
}

GameDevScene::~GameDevScene()
{
}

void GameDevScene::Tick(float deltaSeconds)
{
}

void GameDevScene::Render()
{
	GLManager::GetRef().BeginFrame(0.0f, 0.0f, 0.0f, 1.0f);
	{

	}
	GLManager::GetRef().EndFrame();
}

void GameDevScene::Enter()
{
}

void GameDevScene::Exit()
{
}
