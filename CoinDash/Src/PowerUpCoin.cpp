#include "Assertion.h"
#include "Atlas2D.h"
#include "EntityManager.h"
#include "IApp.h"
#include "RenderManager2D.h"
#include "ResourceManager.h"
#include "SpriteAnim2D.h"

#include "Cactus.h"
#include "Player.h"
#include "PowerUpCoin.h"

static const float MIN_X_POS = -240.0f;
static const float MAX_X_POS = +240.0f;
static const float MIN_Y_POS = -360.0f;
static const float MAX_Y_POS = +360.0f;
static const float MIN_TIME = 10.0f;
static const float MAX_TIME = 15.0f;

PowerUpCoin::PowerUpCoin()
{
	player_ = EntityManager::Get().GetByName<Player>("Player");
	cactus_ =
	{
		EntityManager::Get().GetByName<Cactus>("Cactus0"),
		EntityManager::Get().GetByName<Cactus>("Cactus1"),
		EntityManager::Get().GetByName<Cactus>("Cactus2"),
		EntityManager::Get().GetByName<Cactus>("Cactus3"),
	};

	Atlas2D* atlas = ResourceManager::Get().GetByName<Atlas2D>("Atlas");

	std::vector<std::string> clips = { 
		"PowerCoin_1", 
		"PowerCoin_2", 
		"PowerCoin_3", 
		"PowerCoin_4", 
		"PowerCoin_5", 
		"PowerCoin_6", 
		"PowerCoin_7", 
		"PowerCoin_8", 
		"PowerCoin_9", 
		"PowerCoin_10",
	};
	anim_ = ResourceManager::Get().Create<SpriteAnim2D>(atlas, clips, true, 1.0f);

	bound_.radius = 20.0f;
	
	time_ = GameMath::GenerateRandomFloat(MIN_TIME, MAX_TIME);

	bIsInitialized_ = true;
}

PowerUpCoin::~PowerUpCoin()
{
	if (bIsInitialized_)
	{
		Release();
	}
}

void PowerUpCoin::Tick(float deltaSeconds)
{
	Player::Status status = player_->GetStatus();
	if (status == Player::Status::HURT)
	{
		bIsActive_ = false;
		return;
	}

	time_ -= deltaSeconds;
	if (time_ <= 0.0f)
	{
		if (bIsActive_)
		{
			time_ = GameMath::GenerateRandomFloat(MIN_TIME, MAX_TIME);
		}
		else
		{
			time_ = 5.0f;

			bool bCanActive = true;
			do
			{
				bCanActive = true;

				float x = GameMath::GenerateRandomFloat(MIN_X_POS, MAX_X_POS);
				float y = GameMath::GenerateRandomFloat(MIN_Y_POS, MAX_Y_POS);
				bound_.center = Vec2f(x, y);

				if (bound_.Intersect(player_->GetCollisionBound()))
				{
					bCanActive = false;
				}

				for (auto& cactus : cactus_)
				{
					if (bound_.Intersect(cactus->GetBound()))
					{
						bCanActive = false;
					}
				}
			} while (!bCanActive);
		}

		bIsActive_ = !bIsActive_;
		return;
	}

	if (bIsActive_)
	{
		if (bound_.Intersect(player_->GetCollisionBound()))
		{
			player_->PickupPowerUpCoin();

			time_ = GameMath::GenerateRandomFloat(MIN_TIME, MAX_TIME);
			bIsActive_ = false;
		}

		anim_->Update(deltaSeconds);
	}
}

void PowerUpCoin::Render()
{
	if (!bIsActive_)
	{
		return;
	}

	float size = 2.0f * bound_.radius;

	static RenderManager2D::SpriteRenderOptions option;
	RenderManager2D::Get().DrawSprite(anim_->GetAtlas(), anim_->GetCurrentClip(), bound_.center, size, size, 0.0f, option);
}

void PowerUpCoin::Release()
{
	CHECK(bIsInitialized_);

	ResourceManager::Get().Destroy(anim_);
	anim_ = nullptr;

	player_ = nullptr;

	bIsInitialized_ = false;
}

void PowerUpCoin::Reset()
{
	time_ = GameMath::GenerateRandomFloat(MIN_TIME, MAX_TIME);
	bIsActive_ = false;
	anim_->Reset();
}