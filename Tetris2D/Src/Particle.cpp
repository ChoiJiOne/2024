#include "Assertion.h"
#include "EntityManager.h"
#include "RenderManager2D.h"

#include "Particle.h"

Particle::Particle()
{
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
