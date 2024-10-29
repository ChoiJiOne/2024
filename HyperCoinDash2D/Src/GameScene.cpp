#include "Assertion.h"
#include "EntityManager.h"

#include "GameScene.h"

GameScene::GameScene()
{
	mainCamera_ = EntityManager::GetRef().GetByName<Camera2D>("MainCamera");
}

GameScene::~GameScene()
{
}