#include "Assertion.h"
#include "EntityManager.h"
#include "RenderManager2D.h"

#include "Particle.h"
#include "ParticleScheduler.h"

ParticleScheduler::ParticleScheduler()
{
	EntityManager& entityMgr = EntityManager::GetRef();
	for (uint32_t index = 0; index < MAX_PARTICLE_SIZE; ++index)
	{
		particles_[index] = entityMgr.Create<Particle>();
	}

	particleSpeed_ = 500.0f;
	particleScale_ = 0.3f;

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

	bool bIsDoneAllParticle = true;
	for (uint32_t index = 0; index < numActiveParticle_; ++index)
	{
		particles_[index]->Tick(deltaSeconds);

		if (particles_[index]->GetStatus() == Particle::Status::ACTIVE)
		{
			bIsDoneAllParticle = false;
		}
	}

	if (bIsDoneAllParticle)
	{
		bIsActive_ = false;
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

	EntityManager& entityMgr = EntityManager::GetRef();
	for (uint32_t index = 0; index < MAX_PARTICLE_SIZE; ++index)
	{
		entityMgr.Destroy(particles_[index]);
	}

	bIsInitialized_ = false;
}

void ParticleScheduler::Reset()
{
	for (uint32_t index = 0; index < numActiveParticle_; ++index)
	{
		particles_[index]->SetStatus(Particle::Status::WAIT);
	}
	
	bIsActive_ = false;
	particleSpeed_ = 500.0f;
	particleScale_ = 0.3f;
	numActiveParticle_ = 0;
}

void ParticleScheduler::Start(const Block* blocks, uint32_t count)
{
	static const uint32_t NUM_DIRECTIONS = 4;

	numActiveParticle_ = 0;
	for (uint32_t index = 0; index < count; ++index)
	{
		Rect2D bound = blocks[index].GetBound();
		Vec4f color = blocks[index].GetColor();

		bound.size = bound.size * particleScale_;

		for (uint32_t ii = 0; ii < NUM_DIRECTIONS; ++ii)
		{
			float radian = GameMath::GenerateRandomFloat(0.0f, TWO_PI);
			Vec2f direction(GameMath::Cos(radian), GameMath::Sin(radian));

			particles_[numActiveParticle_ + ii]->Reset(bound, direction, color, particleSpeed_);
			particles_[numActiveParticle_ + ii]->Start();
		}
		
		numActiveParticle_ += NUM_DIRECTIONS;
	}
	bIsActive_ = true;
}
