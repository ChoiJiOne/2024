#include "Assertion.h"
#include "Atlas2D.h"
#include "RenderManager2D.h"
#include "ResourceManager.h"
#include "IApp.h"

#include "Camera.h"
#include "Floor.h"

Floor::Floor(Camera* camera) 
	: camera_(camera)
	, bCanMove_(false)
{
	atlas_ = ResourceManager::Get().GetByName<Atlas2D>("Floor");
	floor_.size = GameMath::Vec2f(camera_->GetWidth(), 100.0f);
	floor_.center = GameMath::Vec2f(0.0f, (- camera_->GetHeight() + floor_.size.y) * 0.5f);

	ResetBlocks();

	bIsInitialized_ = true;
}

Floor::~Floor()
{
	if (bIsInitialized_)
	{
		Release();
	}
}

void Floor::Tick(float deltaSeconds)
{
	if (!bCanMove_)
	{
		return;
	}

	for (auto& block : blocks_)
	{
		block.center.x -= deltaSeconds * scrollSpeed_;
	}
}

void Floor::Render()
{
	RenderManager2D::Get().DrawSprite(atlas_, "floor", floor_.center, floor_.size.x, floor_.size.y);

	for (const auto& block : blocks_)
	{
		RenderManager2D::Get().DrawSprite(atlas_, "block", block.center, block.size.x, block.size.y);
	}
}

void Floor::Release()
{
	CHECK(bIsInitialized_);

	camera_ = nullptr;
	atlas_ = nullptr;

	bIsInitialized_ = false;
}

void Floor::ResetBlocks()
{
	GameMath::Vec2f center = GameMath::Vec2f(-camera_->GetWidth() * 0.5f, -220.0f);
	GameMath::Vec2f size = GameMath::Vec2f(40.0f, 40.0f);
	
	for (auto& block : blocks_)
	{
		block.center = center;
		block.size = size;

		center.x += size.x;
	}
}
