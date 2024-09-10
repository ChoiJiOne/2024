#include "Assertion.h"
#include "Atlas2D.h"
#include "EntityManager.h"
#include "RenderManager2D.h"
#include "ResourceManager.h"

#include "Cactus.h"
#include "Player.h"

Cactus::Cactus(const Rect2D& bound)
	: bound_(bound)
{
	player_ = EntityManager::Get().GetByName<Player>("Player");
	atlas_ = ResourceManager::Get().GetByName<Atlas2D>("Atlas");

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
}

void Cactus::Render()
{
	RenderManager2D::Get().DrawSprite(atlas_, "Cactus", bound_.center, bound_.size.x, bound_.size.y);
}

void Cactus::Release()
{
	CHECK(bIsInitialized_);

	player_ = nullptr;
	atlas_ = nullptr;

	bIsInitialized_ = false;
}
