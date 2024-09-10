#include "Assertion.h"
#include "EntityManager.h"

#include "Camera.h"
#include "Coin.h"
#include "Player.h"
#include "CoinSpawner.h"

CoinSpawner::CoinSpawner()
{
	camera_ = EntityManager::Get().GetByName<Camera>("Camera");
	player_ = EntityManager::Get().GetByName<Player>("Player");

	bIsInitialized_ = true;
}

CoinSpawner::~CoinSpawner()
{
	if (bIsInitialized_)
	{
		Release();
	}
}

void CoinSpawner::Tick(float deltaSeconds)
{
}

void CoinSpawner::Render()
{
}

void CoinSpawner::Release()
{
	CHECK(bIsInitialized_);

	player_ = nullptr;
	camera_ = nullptr;

	bIsInitialized_ = false;
}
