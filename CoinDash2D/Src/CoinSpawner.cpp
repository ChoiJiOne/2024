#include "Assertion.h"
#include "EntityManager.h"

#include "Cactus.h"
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
	cactus_ =
	{
		EntityManager::Get().GetByName<Cactus>("Cactus0"),
		EntityManager::Get().GetByName<Cactus>("Cactus1"),
		EntityManager::Get().GetByName<Cactus>("Cactus2"),
		EntityManager::Get().GetByName<Cactus>("Cactus3"),
	};

	maxNumCoin_ = 5;
	coinRemoveEvent_ = [&](Coin* coin)->bool { return coin == nullptr; };

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

			bool bCanCreateCoin = true;
			do
			{
				bCanCreateCoin = true;

				float x = GameMath::GenerateRandomFloat(MIN_X_POS, MAX_X_POS);
				float y = GameMath::GenerateRandomFloat(MIN_Y_POS, MAX_Y_POS);
				bound.center = GameMath::Vec2f(x, y);

				if (bound.Intersect(player_->GetCollisionBound()))
				{
					bCanCreateCoin = false;
				}

				for (auto& cactus : cactus_)
				{
					if (bound.Intersect(cactus->GetBound()))
					{
						bCanCreateCoin = false;
					}
				}
			} while (!bCanCreateCoin);

			Coin* coin = EntityManager::Get().Create<Coin>(bound);
			coins_.push_back(coin);
		}
	}

	for (auto& coin : coins_)
	{
		coin->Tick(deltaSeconds);
	}

	Cleanup();
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

void CoinSpawner::Cleanup()
{
	for (auto& coin : coins_)
	{
		if (coin && coin->IsPickup())
		{
			EntityManager::Get().Destroy(coin);
			coin = nullptr;
		}
	}

	coins_.remove_if(coinRemoveEvent_);
}
