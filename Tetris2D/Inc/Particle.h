#pragma once

#include <array>

#include "IEntity2D.h"
#include "GameMath.h"

#include "Block.h"

class Camera2D;

class Particle : public IEntity2D
{
public:
	Particle();
	virtual ~Particle();

	DISALLOW_COPY_AND_ASSIGN(Particle);

	virtual void Tick(float deltaSeconds) override;
	virtual void Render() override;
	virtual void Release() override;

private:
	Camera2D* camera_ = nullptr;
};