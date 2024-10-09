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

	EntityManager& entityMgr = EntityManager::Get();
	for (uint32_t index = 0; index < MAX_PARTICLE_SIZE; ++index)
	{
		entityMgr.Destroy(particles_[index]);
	}

	bIsInitialized_ = false;
}

void ParticleScheduler::Start(const Block* blocks, uint32_t count)
{
	static std::array<Vec2f, 4> directions =
	{
		Vec2f(GameMath::Cos(GameMath::ToRadian(150.0f)), GameMath::Sin(GameMath::ToRadian(150.0f))),
		Vec2f(GameMath::Cos(GameMath::ToRadian(120.0f)), GameMath::Sin(GameMath::ToRadian(120.0f))),
		Vec2f(GameMath::Cos(GameMath::ToRadian(60.0f)), GameMath::Sin(GameMath::ToRadian(60.0f))),
		Vec2f(GameMath::Cos(GameMath::ToRadian(30.0f)), GameMath::Sin(GameMath::ToRadian(30.0f))),
	};

	numActiveParticle_ = 0;
	for (uint32_t index = 0; index < count; ++index)
	{
		Rect2D bound = blocks[index].GetBound();
		Vec4f color = blocks[index].GetColor();

		bound.size = bound.size * 0.5f;

		for (uint32_t ii = 0; ii < directions.size(); ++ii)
		{
			particles_[numActiveParticle_ + ii]->Reset(bound, directions[ii], color, 100.0f);
			particles_[numActiveParticle_ + ii]->Start();
		}

		numActiveParticle_ += directions.size();
	}
	bIsActive_ = true;
}
