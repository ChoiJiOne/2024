#include "Assertion.h"
#include "EntityManager.h"
#include "RenderManager2D.h"

#include "Particle.h"
#include "ParticleScheduler.h"

ParticleScheduler::ParticleScheduler()
{
	EntityManager& entityMgr = EntityManager::Get();
	for (uint32_t index = 0; index < MAX_PARTICLE_SIZE; ++index)
	{
		particles_[index] = entityMgr.Create<Particle>();
	}

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
	if (!bIsActive_)
	{
		return;
	}

	for (uint32_t index = 0; index < numActiveParticle_; ++index)
	{
		particles_[index]->Tick(deltaSeconds);
	}
}

void ParticleScheduler::Render()
{
	if (!bIsActive_)
	{
		return;
	}

	for (uint32_t index = 0; index < numActiveParticle_; ++index)
	{
		particles_[index]->Render();
	}
}

void ParticleScheduler::Release()
{
	CHECK(bIsInitialized_);

	EntityManager& entityMgr = EntityManager::Get();
	for (uint32_t index = 0; index < MAX_PARTICLE_SIZE; ++index)
	{
		entityMgr.Destroy(particles_[index]);
	}

	bIsInitialized_ = false;
}