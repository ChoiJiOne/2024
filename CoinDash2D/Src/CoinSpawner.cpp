#include "Assertion.h"
#include "Camera2D.h"
#include "EntityManager.h"
#include "ResourceManager.h"
#include "Sound.h"

#include "Cactus.h"
#include "Coin.h"
#include "CoinSpawner.h"
#include "CountDowner.h"
#include "Player.h"

static const float MIN_X_POS = -240.0f;
static const float MAX_X_POS = +240.0f;
static const float MIN_Y_POS = -360.0f;
static const float MAX_Y_POS = +360.0f;

CoinSpawner::CoinSpawner()
{
	camera_ = EntityManager::Get().GetByName<Camera2D>("Camera");
	player_ = EntityManager::Get().GetByName<Player>("Player");
	level_ = ResourceManager::Get().GetByName<Sound>("Level");
	cactus_ =
	{
		EntityManager::Get().GetByName<Cactus>("Cactus0"),
		EntityManager::Get().GetByName<Cactus>("Cactus1"),
		EntityManager::Get().GetByName<Cactus>("Cactus2"),
		EntityManager::Get().GetByName<Cactus>("Cactus3"),
	};

	maxNumCoin_ = 4;
	coinRemoveEvent_ = [&](Coin* coin)->bool { return coin == nullptr; };

	GenerateCoins();

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
	Player::Status status = player_->GetStatus();
	if (status == Player::Status::HURT)
	{
		for (auto& coin : coins_)
		{
			coin->Tick(deltaSeconds);
		}
		return;
	}

	if (coins_.empty())
	{
		level_->Reset();
		level_->Play();

		GenerateCoins();

		CountDowner* countDowner = EntityManager::Get().GetByName<CountDowner>("CountDowner");
		float time = countDowner->GetTime();
		countDowner->SetTime(time + 5.0f);
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

	level_ = nullptr;
	player_ = nullptr;
	camera_ = nullptr;

	bIsInitialized_ = false;
}

void CoinSpawner::Reset()
{
	for (auto& coin : coins_)
	{
		if (coin)
		{
			EntityManager::Get().Destroy(coin);
			coin = nullptr;
		}
	}

	coins_.clear();
	maxNumCoin_ = 4;
	GenerateCoins();
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

void CoinSpawner::GenerateCoins()
{
	maxNumCoin_++;

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
			bound.center = Vec2f(x, y);

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
