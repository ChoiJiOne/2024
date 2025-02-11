#include "Assertion.h"
#include "Atlas2D.h"
#include "Camera2D.h"
#include "EntityManager.h"
#include "RenderManager2D.h"
#include "ResourceManager.h"
#include "IApp.h"

#include "Floor.h"
#include "Player.h"

Floor::Floor() 
	: player_(EntityManager::Get().GetByName<Player>("Player"))
	, camera_(EntityManager::Get().GetByName<Camera2D>("Camera"))
	, bCanMove_(false)
{
	atlas_ = ResourceManager::Get().GetByName<Atlas2D>("Atlas");
	floor_.size = Vec2f(camera_->GetWidth() + 2.0f, 100.0f);
	floor_.center = Vec2f(0.0f, (-camera_->GetHeight() + floor_.size.y) * 0.5f);

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
		bCanMove_ = GetMovable();
		return;
	}

	bCanMove_ = GetMovable();
	if (bCanMove_)
	{
		for (auto& block : blocks_)
		{
			block.center.x -= deltaSeconds * player_->GetSpeed();
		}

		if (!blocks_.front().Intersect(camera_->GetCollision()))
		{
			for (uint32_t index = 0; index < blocks_.size() - 1; ++index)
			{
				blocks_[index].center = blocks_[index + 1].center;
			}

			blocks_.back().center.x = blocks_[blocks_.size() - 2].center.x + blocks_.front().size.x;
		}
	}
}

void Floor::Render()
{
	RenderManager2D& renderMgr = RenderManager2D::Get();
	static RenderManager2D::SpriteRenderOptions option;

	renderMgr.DrawSprite(atlas_, "Floor", floor_.center, floor_.size.x, floor_.size.y, 0.0f, option);
	for (const auto& block : blocks_)
	{
		renderMgr.DrawSprite(atlas_, "Block", block.center, block.size.x, block.size.y, 0.0f, option);
	}
}

void Floor::Release()
{
	CHECK(bIsInitialized_);

	camera_ = nullptr;
	atlas_ = nullptr;
	player_ = nullptr;

	bIsInitialized_ = false;
}

void Floor::ResetBlocks()
{
	Vec2f center = Vec2f(-camera_->GetWidth() * 0.5f, -220.0f);
	Vec2f size = Vec2f(40.0f, 40.0f);
	
	for (auto& block : blocks_)
	{
		block.center = center;
		block.size = size;

		center.x += size.x;
	}
}

bool Floor::GetMovable()
{
	Player::EStatus status = player_->GetStatus();
	return status == Player::EStatus::JUMP || status == Player::EStatus::RUN;
}
