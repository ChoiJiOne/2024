#pragma once

#include <array>

#include "IEntity2D.h"
#include "GameMath.h"

#include "Block.h"

class Camera2D;

class ParticleScheduler : public IEntity2D
{
public:
	ParticleScheduler();
	virtual ~ParticleScheduler();

	DISALLOW_COPY_AND_ASSIGN(ParticleScheduler);

	virtual void Tick(float deltaSeconds) override;
	virtual void Render() override;
	virtual void Release() override;

private:
	Camera2D* camera_ = nullptr;
};