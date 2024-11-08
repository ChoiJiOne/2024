#pragma once

#include "Physic/ICollider2D.h"

/** 2D ���� �浹 ó���� ���� ���Դϴ�. */
struct Line2D : public ICollider2D
{
	Line2D() = default;
	Line2D(const glm::vec2& s, const glm::vec2& e) : start(s), end(e) {}
	Line2D(Line2D&& instance) noexcept : start(instance.start), end(instance.end) {}
	Line2D(const Line2D& instance) noexcept : start(instance.start), end(instance.end) {}
	virtual ~Line2D() {}

	Line2D& operator=(Line2D&& instance) noexcept
	{
		if (this == &instance) return *this;

		start = instance.start;
		end = instance.end;

		return *this;
	}

	Line2D& operator=(const Line2D& instance) noexcept
	{
		if (this == &instance) return *this;

		start = instance.start;
		end = instance.end;

		return *this;
	}

	virtual EType GetType() const override { return EType::LINE; }
	virtual bool Intersect(const ICollider2D* collider) const override;

	glm::vec2 start;
	glm::vec2 end;
};