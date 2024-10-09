#include "Assertion.h"
#include "Camera2D.h"
#include "EntityManager.h"
#include "RenderManager2D.h"

#include "Board.h"
#include "ParticleScheduler.h"

ParticleScheduler::ParticleScheduler()
{
	camera_ = EntityManager::Get().GetByName<Camera2D>("MainCamera");

	bIsInitialized_ = true;
}

ParticleScheduler::~ParticleScheduler()
{
	if (bIsInitialized_)
	{
		Release();
	}
}

void ParticleScheduler::Tick(float deltaSeconds)
{
}

void ParticleScheduler::Render()
{
}

void ParticleScheduler::Release()
{
	CHECK(bIsInitialized_);

	camera_ = nullptr;

	bIsInitialized_ = false;
}