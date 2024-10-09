#pragma once

#include <array>

#include "IEntity2D.h"
#include "GameMath.h"

#include "Block.h"

class Camera2D;

class ParticleController : public IEntity2D
{
public:
	ParticleController();
	virtual ~ParticleController();

	DISALLOW_COPY_AND_ASSIGN(ParticleController);

	virtual void Tick(float deltaSeconds) override;
	virtual void Render() override;
	virtual void Release() override;

private:
	Camera2D* camera_ = nullptr;
};