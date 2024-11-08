#include <array>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtc/constants.hpp>
#include <glm/gtc/epsilon.hpp>
#include <glm/gtx/norm.hpp>

#include "Physic/Circle2D.h"
#include "Physic/Line2D.h"
#include "Physic/OrientedRect2D.h"
#include "Physic/Rect2D.h"
#include "Utils/Assertion.h"

/** 축을 기준으로 AABB와 OBB가 오버랩(겹치는지) 확인 */
bool IsOverlapOnAxis(const Rect2D* rect, const OrientedRect2D* orientedRect, const glm::vec2& axis)
{
	float rectMin = 0.0f;
	float rectMax = 0.0f;
	rect->GetInterval(axis, rectMin, rectMax);

	float orientedRectMin = 0.0f;
	float orientedRectMax = 0.0f;
	orientedRect->GetInterval(axis, orientedRectMin, orientedRectMax);

	return ((orientedRectMin <= rectMax) && (rectMin <= orientedRectMax));
}

/** AABB와 AABB 끼리의 충돌 처리 */
bool IsCollision(const Rect2D* lhs, const Rect2D* rhs)
{
	glm::vec2 minPos0 = lhs->GetMin();
	glm::vec2 maxPos0 = lhs->GetMax();
	glm::vec2 minPos1 = rhs->GetMin();
	glm::vec2 maxPos1 = rhs->GetMax();

	bool bIsOverlapX = ((minPos1.x <= maxPos0.x) && (minPos0.x <= maxPos1.x));
	bool bIsOverlapY = ((minPos1.y <= maxPos0.y) && (minPos0.y <= maxPos1.y));

	return bIsOverlapX && bIsOverlapY;
}

/** AABB와 OBB 끼리의 충돌 처리 */
bool IsCollision(const Rect2D* rect, const OrientedRect2D* orientedRect)
{
	float rotate = orientedRect->rotate;
	glm::mat2 roateMat(glm::cos(rotate), -glm::sin(rotate), glm::sin(rotate), glm::cos(rotate));

	glm::vec2 axis0(orientedRect->size.x * 0.5f, 0.0f);
	glm::vec2 axis1(0.0f, orientedRect->size.y * 0.5f);

	std::array<glm::vec2, 4> separateAxis =
	{
		glm::vec2(1.0f, 0.0f),
		glm::vec2(0.0f, 1.0f),
		glm::normalize(axis0) * roateMat,
		glm::normalize(axis1) * roateMat,
	};

	for (const auto& axis : separateAxis)
	{
		if (!IsOverlapOnAxis(rect, orientedRect, axis))
		{
			return false;
		}
	}

	return true;
}

bool Rect2D::Intersect(const ICollider2D* collider) const
{
	CHECK(collider != nullptr);

	EType type = collider->GetType();
	bool bIsIntersect = false;

	switch (type)
	{
	case ICollider2D::EType::LINE:
	{
		const Line2D* other = reinterpret_cast<const Line2D*>(collider);
		bIsIntersect = other->Intersect(this);
	}
	break;

	case ICollider2D::EType::CIRCLE:
	{
		const Circle2D* other = reinterpret_cast<const Circle2D*>(collider);
		bIsIntersect = other->Intersect(this);
	}
	break;

	case ICollider2D::EType::AABB:
	{
		const Rect2D* other = reinterpret_cast<const Rect2D*>(collider);
		bIsIntersect = IsCollision(this, other);
	}
	break;

	case ICollider2D::EType::OBB:
	{
		const OrientedRect2D* other = reinterpret_cast<const OrientedRect2D*>(collider);
		bIsIntersect = IsCollision(this, other);
	}
	break;

	default: // ICollider2D::EType::NONE:
		break;
	}

	return bIsIntersect;
}

void Rect2D::GetInterval(const glm::vec2& axis, float& outMin, float& outMax) const
{
	glm::vec2 minPos = GetMin();
	glm::vec2 maxPos = GetMax();

	std::array<glm::vec2, 4> vertices =
	{
		glm::vec2(minPos.x, minPos.y),
		glm::vec2(minPos.x, maxPos.y),
		glm::vec2(maxPos.x, maxPos.y),
		glm::vec2(maxPos.x, minPos.y),
	};

	outMin = +FLT_MAX;
	outMax = -FLT_MAX;

	for (int32_t index = 0; index < vertices.size(); ++index)
	{
		float projection = glm::dot(axis, vertices[index]);

		if (projection < outMin)
		{
			outMin = projection;
		}

		if (projection > outMax)
		{
			outMax = projection;
		}
	}
}
