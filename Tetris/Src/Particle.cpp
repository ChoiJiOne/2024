#include "Assertion.h"
#include "Camera2D.h"
#include "EntityManager.h"
#include "RenderManager2D.h"

#include "Particle.h"

Camera2D* Particle::camera_ = nullptr;

Particle::Particle()
{
	if (!camera_)
	{
		camera_ = EntityManager::GetRef().GetByName<Camera2D>("MainCamera");
	}

	directionFactor_ = 2.0f;
	bIsInitialized_ = true;
}

Particle::Particle(const Rect2D& bound, const Vec2f& direction, const Vec4f& color, float speed)
	: bound_(bound)
	, direction_(direction)
	, color_(color)
	, speed_(speed)
{
	if (!camera_)
	{
		camera_ = EntityManager::GetRef().GetByName<Camera2D>("MainCamera");
	}

	directionFactor_ = 2.0f;
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

	direction_.y -= deltaSeconds * directionFactor_;
	bound_.center.x += deltaSeconds * speed_ * direction_.x;
	bound_.center.y += deltaSeconds * speed_ * direction_.y;

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

	RenderManager2D::GetRef().DrawRect(bound_.center, bound_.size.x, bound_.size.y, color_, 0.0f);
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
	directionFactor_ = 2.0f;
	status_ = Status::WAIT;
}

void Particle::Start()
{
	CHECK(status_ == Status::WAIT);

	status_ = Status::ACTIVE;
}