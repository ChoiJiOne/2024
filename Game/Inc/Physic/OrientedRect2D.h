#pragma once

#include "Physic/ICollider2D.h"

/** 충돌 처리를 위한 OBB 사각형입니다. */
struct OrientedRect2D : public ICollider2D
{
	OrientedRect2D() = default;
	OrientedRect2D(const glm::vec2& c, const glm::vec2& s, float r) : center(c), size(s), rotate(r) {}
	OrientedRect2D(OrientedRect2D&& instance) noexcept : center(instance.center), size(instance.size), rotate(instance.rotate) {}
	OrientedRect2D(const OrientedRect2D& instance) noexcept : center(instance.center), size(instance.size), rotate(instance.rotate) {}
	virtual ~OrientedRect2D() {}

	OrientedRect2D& operator=(OrientedRect2D&& instance) noexcept
	{
		if (this == &instance) return *this;

		center = instance.center;
		size = instance.size;
		rotate = instance.rotate;

		return *this;
	}

	OrientedRect2D& operator=(const OrientedRect2D& instance) noexcept
	{
		if (this == &instance) return *this;

		center = instance.center;
		size = instance.size;
		rotate = instance.rotate;

		return *this;
	}

	virtual EType GetType() const override { return EType::OBB; }
	virtual bool Intersect(const ICollider2D* collider) const override;

	void GetInterval(const glm::vec2& axis, float& outMin, float& outMax) const;

	glm::vec2 center = glm::vec2(0.0f, 0.0f);
	glm::vec2 size = glm::vec2(0.0f, 0.0f);
	float rotate; /** 라디안 각도 기준 */
};