#pragma once

#include <array>

#include "IEntity2D.h"
#include "GameMath.h"

#include "Block.h"

class Camera2D;

class Particle : public IEntity2D
{
public:
	enum class Status
	{
		WAIT      = 0x00,
		EXPLOSION = 0x01,
		DONE      = 0x02,
	};

public:
	Particle();
	virtual ~Particle();

	DISALLOW_COPY_AND_ASSIGN(Particle);

	virtual void Tick(float deltaSeconds) override;
	virtual void Render() override;
	virtual void Release() override;

private:
	Camera2D* camera_ = nullptr;

	static const uint32_t MAX_PARTICLE_COUNT = 200;

	uint32_t numParticleBlock_ = 0;
	std::array<Block, MAX_PARTICLE_COUNT> particles_;
};