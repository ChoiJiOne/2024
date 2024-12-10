#include "Assertion.h"
#include "RenderStateManager.h"

#include "MainCamera2D.h"

MainCamera2D::MainCamera2D()
{
	RenderStateManager::GetRef().GetScreenSize<float>(size_.x, size_.y);
	
	ortho_ = CalculateOrtho(center_, size_);
	collision_ = Rect2D(center_, size_);
	originCollision_ = collision_;

	maxShakeTime_ = 0.05f;
	shakeMoveLength_ = 80.0f;

	bIsInitialized_ = true;
}

MainCamera2D::~MainCamera2D()
{
	if (bIsInitialized_)
	{
		Release();
	}
}

void MainCamera2D::Tick(float deltaSeconds)
{
	if (!bStartShake_)
	{
		return;
	}

	shakeTime_ += deltaSeconds;
	if (shakeTime_ >= maxShakeTime_)
	{
		bStartShake_ = false;
		collision_ = originCollision_;
		ortho_ = CalculateOrtho(collision_.center, collision_.size);
		return;
	}

	collision_.center.y = originCollision_.center.y + shakeMoveLength_ * GameMath::Sin(shakeTime_);
	ortho_ = CalculateOrtho(collision_.center, collision_.size);
}

void MainCamera2D::Release()
{
	CHECK(bIsInitialized_);

	bIsInitialized_ = false;
}

void MainCamera2D::Reset()
{
	bStartShake_ = false;
	collision_ = originCollision_;
	ortho_ = CalculateOrtho(collision_.center, collision_.size);
}

void MainCamera2D::Shake()
{
	shakeTime_ = 0.0f;
	bStartShake_ = true;
}