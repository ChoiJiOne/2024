#include "Assertion.h"
#include "Camera2D.h"
#include "EntityManager.h"
#include "RenderManager2D.h"

#include "Particle.h"

Camera2D* Particle::camera_ = nullptr;

Particle::Particle(const Rect2D& bound, const Vec2f& direction, const Vec4f& color, float speed)
	: bound_(bound)
	, direction_(direction)
	, color_(color)
	, speed_(speed)
{
	if (!camera_)
	{
		camera_ = EntityManager::Get().GetByName<Camera2D>("MainCamera");
	}

	bIsInitialized_ = true;
}

Particle::~Particle()
{
	if (bIsInitialized_)
	{
		Release();
	}
}

void Particle::Tick(float deltaSeconds)
{
	if (status_ != Status::ACTIVE)
	{
		return;
	}

	direction_.y -= 9.8f; /** 중력 작용 테스트. */
	bound_.center.x += speed_ * direction_.x;
	bound_.center.y += speed_ * direction_.y;

	if (!bound_.Intersect(camera_->GetCollision()))
	{
		status_ = Status::DONE;
	}
}

void Particle::Render()
{
	if (status_ != Status::ACTIVE)
	{
		return;
	}

	RenderManager2D::Get().DrawRect(bound_.center, bound_.size.x, bound_.size.y, color_, 0.0f);
}

void Particle::Release()
{
	CHECK(bIsInitialized_);

	bIsInitialized_ = false;
}

void Particle::Reset(const Rect2D& bound, const Vec2f& direction, const Vec4f& color, float speed)
{
	bound_ = bound;
	direction_ = direction;
	color_ = color;
	speed_ = speed;
	status_ = Status::WAIT;
}

void Particle::Start()
{
	CHECK(status_ == Status::WAIT);

	status_ = Status::ACTIVE;
}