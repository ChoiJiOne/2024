#include <json/json.h>

#include "Game/GameManager.h"

GameManager GameManager::singleton_;

GameManager& GameManager::GetRef()
{
	return singleton_;
}

GameManager* GameManager::GetPtr()
{
	return &singleton_;
}

void GameManager::Startup()
{
}

void GameManager::Shutdown()
{
}
