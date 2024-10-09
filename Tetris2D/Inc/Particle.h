#pragma once

#include "Collision2D.h"

class Particle
{
public:
	Particle() = default;
	Particle(Particle&& instance) noexcept
		: bound_(instance.bound_)
		, direction_(instance.direction_)
		, speed_(instance.speed_)
		, originPos_(instance.originPos_) {}
	Particle(const Particle& instance) noexcept
		: bound_(instance.bound_)
		, direction_(instance.direction_)
		, speed_(instance.speed_)
		, originPos_(instance.originPos_) {}

	virtual ~Particle() {}

	Particle& operator=(Particle&& instance) noexcept
	{
		if (this == &instance) return *this;

		bound_ = instance.bound_;
		direction_ = instance.direction_;
		speed_ = instance.direction_;
		originPos_ = instance.originPos_;

		return *this;
	}

	Particle& operator=(const Particle& instance) noexcept
	{
		if (this == &instance) return *this;

		bound_ = instance.bound_;
		direction_ = instance.direction_;
		speed_ = instance.direction_;
		originPos_ = instance.originPos_;

		return *this;
	}

private:
	Rect2D bound_;
	Vec2f direction_;
	Vec2f speed_ = 0.0f;
	Vec2f originPos_;
};