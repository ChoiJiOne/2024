#include "Assertion.h"
#include "Atlas2D.h"
#include "EntityManager.h"
#include "IApp.h"
#include "RenderManager2D.h"
#include "ResourceManager.h"
#include "SpriteAnim2D.h"

#include "Coin.h"
#include "Player.h"

Coin::Coin(const Circle2D& bound)
	: bound_(bound)
{
	player_ = EntityManager::Get().GetByName<Player>("Player");

	Atlas2D* atlas = ResourceManager::Get().GetByName<Atlas2D>("Atlas");

	std::vector<std::string> clips = { "Coin_1", "Coin_2", "Coin_3", "Coin_4", "Coin_5", "Coin_6", "Coin_7", "Coin_8", "Coin_9", "Coin_10", "Coin_11", };
	anim_ = ResourceManager::Get().Create<SpriteAnim2D>(atlas, clips, true, 1.0f);

	bIsInitialized_ = true;
}

Coin::~Coin()
{
	if (bIsInitialized_)
	{
		Release();
	}
}

void Coin::Tick(float deltaSeconds)
{
	anim_->Update(deltaSeconds);
}

void Coin::Render()
{
	RenderManager2D::Get().DrawSprite(anim_->GetAtlas(), anim_->GetCurrentClip(), bound_.center, 2.0f * bound_.radius, 2.0f * bound_.radius);
}

void Coin::Release()
{
	CHECK(bIsInitialized_);

	ResourceManager::Get().Destroy(anim_);
	anim_ = nullptr;

	player_ = nullptr;

	bIsInitialized_ = false;
}
