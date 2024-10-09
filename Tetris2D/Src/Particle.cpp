#include "Assertion.h"
#include "Camera2D.h"
#include "RenderManager2D.h"

#include "Board.h"
#include "Particle.h"
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

	camera_ = nullptr;

	bIsInitialized_ = false;
}