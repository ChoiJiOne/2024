#include "Assertion.h"
#include "Atlas2D.h"
#include "EntityManager.h"
#include "RenderManager2D.h"
#include "ResourceManager.h"

#include "Cactus.h"
#include "Player.h"

Cactus::Cactus(const Rect2D& bound)
	: spriteBound_(bound)
{
	player_ = EntityManager::Get().GetByName<Player>("Player");
	atlas_ = ResourceManager::Get().GetByName<Atlas2D>("Atlas");

	collisionBound_ = spriteBound_;
	collisionBound_.size.x -= 10.0f;

	bIsInitialized_ = true;
}

Cactus::~Cactus()
{
	if (bIsInitialized_)
	{
		Release();
	}
}

void Cactus::Tick(float deltaSeconds)
{
	if (collisionBound_.Intersect(player_->GetCollisionBound()))
	{
		player_->SetStatus(Player::Status::HURT);
	}
}

void Cactus::Render()
{
	RenderManager2D::Get().DrawSprite(atlas_, "Cactus", spriteBound_.center, spriteBound_.size.x, spriteBound_.size.y);
}

void Cactus::Release()
{
	CHECK(bIsInitialized_);

	player_ = nullptr;
	atlas_ = nullptr;

	bIsInitialized_ = false;
}
