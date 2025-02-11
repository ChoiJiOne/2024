#pragma once

#include "IEntity2D.h"
#include "GameMath.h"

#include "Block.h"

class Camera2D;

class Particle : public IEntity2D
{
public:
	enum class Status
	{
		WAIT   = 0x00,
		ACTIVE = 0x01,
		DONE   = 0x02,
	};

public:
	Particle();
	Particle(const Rect2D& bound, const Vec2f& direction, const Vec4f& color, float speed);
	virtual ~Particle();

	DISALLOW_COPY_AND_ASSIGN(Particle);

	virtual void Tick(float deltaSeconds) override;
	virtual void Render() override;
	virtual void Release() override;

	void Reset(const Rect2D& bound, const Vec2f& direction, const Vec4f& color, float speed);
	void Start();

	const Status& GetStatus() const { return status_; }
	void SetStatus(const Status& status) { status_ = status; }

private:
	Rect2D bound_;
	Vec2f direction_;
	Vec4f color_;
	float speed_ = 0.0f;
	float directionFactor_ = 0.0f;
	Status status_ = Status::WAIT;

	static Camera2D* camera_;
};