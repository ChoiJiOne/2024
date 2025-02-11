#pragma once

#include <array>

#include "IEntity2D.h"
#include "GameMath.h"

#include "Block.h"

class Particle;

class ParticleScheduler : public IEntity2D
{
public:
	ParticleScheduler();
	virtual ~ParticleScheduler();

	DISALLOW_COPY_AND_ASSIGN(ParticleScheduler);

	virtual void Tick(float deltaSeconds) override;
	virtual void Render() override;
	virtual void Release() override;

	bool IsActive() const { return bIsActive_; }
	
	void Reset();
	void Start(const Block* blocks, uint32_t count); /** 파티클 스케줄러 시작. */

private:
	bool bIsActive_ = false;

	/** 게임 내에서 삭제할 수 있는 최대 블럭의 수(40) X 4 = 160. */
	static const uint32_t MAX_PARTICLE_SIZE = 160;
	std::array<Particle*, MAX_PARTICLE_SIZE> particles_;

	float particleSpeed_ = 0.0f;
	float particleScale_ = 0.0f;
	int32_t numActiveParticle_ = 0;
};