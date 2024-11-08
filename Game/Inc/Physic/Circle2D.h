#pragma once

#include "Physic/ICollider2D.h"

/** 2D �浹 ó���� ���� ���Դϴ�. */
struct Circle2D : public ICollider2D
{
	Circle2D() = default;
	Circle2D(const glm::vec2& c, float r) : center(c), radius(r) {}
	Circle2D(Circle2D&& instance) noexcept : center(instance.center), radius(instance.radius) {}
	Circle2D(const Circle2D& instance) noexcept : center(instance.center), radius(instance.radius) {}
	virtual ~Circle2D() {}

	Circle2D& operator=(Circle2D&& instance) noexcept
	{
		if (this == &instance) return *this;

		center = instance.center;
		radius = instance.radius;

		return *this;
	}

	Circle2D& operator=(const Circle2D& instance) noexcept
	{
		if (this == &instance) return *this;

		center = instance.center;
		radius = instance.radius;

		return *this;
	}

	virtual EType GetType() const override { return EType::CIRCLE; }
	virtual bool Intersect(const ICollider2D* collider) const override;

	glm::vec2 center;
	float radius;
};