#pragma once

#include "Physic/ICollider2D.h"

/** 2D 충돌 처리를 위한 AABB 사각형입니다. */
struct Rect2D : public ICollider2D
{
	Rect2D() = default;
	Rect2D(const glm::vec2& c, const glm::vec2& s) : center(c), size(s) {}
	Rect2D(Rect2D&& instance) noexcept : center(instance.center), size(instance.size) {}
	Rect2D(const Rect2D& instance) noexcept : center(instance.center), size(instance.size) {}
	virtual ~Rect2D() {}

	Rect2D& operator=(Rect2D&& instance) noexcept
	{
		if (this == &instance) return *this;

		center = instance.center;
		size = instance.size;

		return *this;
	}

	Rect2D& operator=(const Rect2D& instance) noexcept
	{
		if (this == &instance) return *this;

		center = instance.center;
		size = instance.size;

		return *this;
	}

	glm::vec2 GetMin() const { return center - size * 0.5f; }
	glm::vec2 GetMax() const { return center + size * 0.5f; }

	virtual EType GetType() const override { return EType::AABB; }
	virtual bool Intersect(const ICollider2D* collider) const override;

	void GetInterval(const glm::vec2& axis, float& outMin, float& outMax) const;

	glm::vec2 center;
	glm::vec2 size;
};