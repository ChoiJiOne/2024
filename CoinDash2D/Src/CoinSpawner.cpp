#include "Assertion.h"
#include "EntityManager.h"

#include "Camera.h"
#include "Coin.h"
#include "Player.h"
#include "CoinSpawner.h"

static const float MIN_X_POS = -240.0f;
static const float MAX_X_POS = +240.0f;
static const float MIN_Y_POS = -360.0f;
static const float MAX_Y_POS = +360.0f;

CoinSpawner::CoinSpawner()
{
	camera_ = EntityManager::Get().GetByName<Camera>("Camera");
	player_ = EntityManager::Get().GetByName<Player>("Player");

	maxNumCoin_ = 5;

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
	if (coins_.empty())
	{
		for (int32_t count = 0; count < maxNumCoin_; ++count)
		{
			Circle2D bound;
			bound.radius = 15.0f;

			do
			{
				float x = GameMath::GenerateRandomFloat(MIN_X_POS, MAX_X_POS);
				float y = GameMath::GenerateRandomFloat(MIN_Y_POS, MAX_Y_POS);
				bound.center = GameMath::Vec2f(x, y);
			} while (bound.Intersect(player_->GetCollisionBound()));

			Coin* coin = EntityManager::Get().Create<Coin>(bound);
			coins_.push_back(coin);
		}
	}

	for (auto& coin : coins_)
	{
		coin->Tick(deltaSeconds);
	}
}

void CoinSpawner::Render()
{
	for (auto& coin : coins_)
	{
		coin->Render();
	}
}

void CoinSpawner::Release()
{
	CHECK(bIsInitialized_);

	player_ = nullptr;
	camera_ = nullptr;

	bIsInitialized_ = false;
}
