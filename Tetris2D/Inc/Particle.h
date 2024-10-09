#pragma once

#include "IEntity2D.h"
#include "GameMath.h"

#include "Block.h"

class Camera2D;

class Particle : public IEntity2D
{
public:
	Particle(const Rect2D& bound, const Vec2f& direction, float speed);
	virtual ~Particle();

	DISALLOW_COPY_AND_ASSIGN(Particle);

	virtual void Tick(float deltaSeconds) override;
	virtual void Render() override;
	virtual void Release() override;
	
private:
	Rect2D bound_;
	Vec2f direction_;
	float speed_ = 0.0f;

	static Camera2D* camera_;
};