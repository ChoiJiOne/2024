#include "Assertion.h"
#include "Camera2D.h"
#include "EntityManager.h"
#include "RenderManager2D.h"

#include "Particle.h"

Camera2D* Particle::camera_ = nullptr;

Particle::Particle(const Rect2D& bound, const Vec2f& direction, float speed)
	: bound_(bound)
	, direction_(direction)
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
}

void Particle::Render()
{
}

void Particle::Release()
{
	CHECK(bIsInitialized_);

	bIsInitialized_ = false;
}
