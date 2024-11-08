#pragma once

#include "Physic/ICollider2D.h"

/** 2D 물리 충돌 처리를 위한 점입니다. */
struct Point2D : public ICollider2D
{
	Point2D() = default;
	Point2D(const glm::vec2& c) : center(c) {}
	Point2D(Point2D&& instance) noexcept : center(instance.center) {}
	Point2D(const Point2D& instance) noexcept : center(instance.center) {}
	virtual ~Point2D() {}

	Point2D& operator=(Point2D&& instance) noexcept
	{
		if (this == &instance) return *this;

		center = instance.center;

		return *this;
	}

	Point2D& operator=(const Point2D& instance) noexcept
	{
		if (this == &instance) return *this;

		center = instance.center;

		return *this;
	}

	virtual EType GetType() const override { return EType::POINT; }
	virtual bool Intersect(const ICollider2D* collider) const override;

	glm::vec2 center;
};