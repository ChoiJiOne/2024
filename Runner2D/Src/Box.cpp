#include "Assertion.h"
#include "Atlas2D.h"
#include "EntityManager.h"
#include "RenderManager2D.h"
#include "ResourceManager.h"

#include "Box.h"
#include "Camera.h"
#include "Player.h"

Box::Box(const Rect2D& bound)
	: player_(EntityManager::Get().GetByName<Player>("Player"))
	, camera_(EntityManager::Get().GetByName<Camera>("Camera"))
	, bound_(bound)
	, bCanMove_(true)
{
	atlas_ = ResourceManager::Get().GetByName<Atlas2D>("Atlas");

	bIsInitialized_ = true;
}

Box::~Box()
{
	if (bIsInitialized_)
	{
		Release();
	}
}

void Box::Tick(float deltaSeconds)
{
	if (status_ == EStatus::DONE)
	{
		return;
	}
	
	bCanMove_ = GetMovable();
	if (bCanMove_)
	{
		bound_.center.x -= deltaSeconds * player_->GetSpeed();
	}

	if (!bound_.Intersect(camera_->GetCollision()) && bound_.center.x < 0.0f)
	{
		status_ = EStatus::DONE;
		bCanMove_ = false;
	}

	if (bound_.Intersect(player_->GetCollision()))
	{
		bCanMove_ = false;
		player_->SetStatus(Player::EStatus::HURT);
	}
}

void Box::Render()
{
	RenderManager2D::Get().DrawSprite(atlas_, "Box", bound_.center, bound_.size.x, bound_.size.y);
}

void Box::Release()
{
	CHECK(bIsInitialized_);

	atlas_ = nullptr;
	camera_ = nullptr;
	player_ = nullptr;

	bIsInitialized_ = false;
}

bool Box::GetMovable()
{
	Player::EStatus status = player_->GetStatus();
	return status == Player::EStatus::RUN || status == Player::EStatus::JUMP;
}
