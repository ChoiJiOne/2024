#include "Assertion.h"
#include "Atlas2D.h"
#include "EntityManager.h"
#include "IApp.h"
#include "RenderManager2D.h"
#include "ResourceManager.h"
#include "SpriteAnim2D.h"

#include "Player.h"
#include "PowerUpCoin.h"

PowerUpCoin::PowerUpCoin()
{
	player_ = EntityManager::Get().GetByName<Player>("Player");

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

	bound_ = Circle2D(GameMath::Vec2f(0.0f, -100.0f), 20.0f);

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
	anim_->Update(deltaSeconds);
}

void PowerUpCoin::Render()
{
	float size = 2.0f * bound_.radius;
	RenderManager2D::Get().DrawSprite(anim_->GetAtlas(), anim_->GetCurrentClip(), bound_.center, size, size);
}

void PowerUpCoin::Release()
{
	CHECK(bIsInitialized_);

	ResourceManager::Get().Destroy(anim_);
	anim_ = nullptr;

	player_ = nullptr;

	bIsInitialized_ = false;
}