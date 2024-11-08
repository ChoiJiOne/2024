#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtc/constants.hpp>
#include <glm/gtc/epsilon.hpp>
#include <glm/gtx/norm.hpp>

#include "Physic/Circle2D.h"
#include "Physic/Line2D.h"
#include "Physic/OrientedRect2D.h"
#include "Physic/Rect2D.h"
#include "Utils/Assertion.h"

/** 선과 선 끼리의 충돌 */
bool IsCollision(const Line2D* lhs, const Line2D* line1)
{
	glm::vec2 p1 = lhs->start;
	glm::vec2 p2 = lhs->end;
	glm::vec2 p3 = line1->start;
	glm::vec2 p4 = line1->end;

	glm::vec2 p12 = p2 - p1;
	glm::vec2 p34 = p4 - p3;
	glm::vec2 p31 = p1 - p3;
	
	float cross = p12.x * p34.y - p12.y * p34.x;
	if (glm::epsilonEqual<float>(cross, 0.0f, glm::epsilon<float>())) /** 두 직선이 서로 평행한 경우. */
	{
		static auto checkBound = [](const glm::vec2& minPos, const glm::vec2& maxPos, const glm::vec2& pos)->bool
			{
				float minX = glm::min<float>(minPos.x, maxPos.x);
				float minY = glm::min<float>(minPos.y, maxPos.y);
				float maxX = glm::max<float>(minPos.x, maxPos.x);
				float maxY = glm::max<float>(minPos.y, maxPos.y);

				return (minX <= pos.x && pos.x <= maxX) && (minY <= pos.y && pos.y <= maxY);
			};

		return (checkBound(p1, p2, p3) || checkBound(p1, p2, p4) || checkBound(p3, p4, p1) || checkBound(p3, p4, p2));
	}
	else /** 그렇지 않은 모든 경우 */
	{
		float uA = (p34.x * p31.y - p34.y * p31.x) / cross;
		float uB = (p12.x * p31.y - p12.y * p31.x) / cross;
		return (uA >= 0.0f && uA <= 1.0f && uB >= 0.0f && uB <= 1.0f);
	}
}

/** 선과 원 사이의 충돌 처리 */
bool IsCollision(const Line2D* lhs, const Circle2D* rhs)
{
	static auto checkCircleBound = [](const Circle2D* circle, const glm::vec2& pos)->bool
		{
			float dist2 = glm::length2(pos - circle->center);
			float r2 = circle->radius * circle->radius;
			return dist2 <= r2;
		};

	if (checkCircleBound(rhs, lhs->start) || checkCircleBound(rhs, lhs->end))
	{
		return true;
	}

	glm::vec2 d = lhs->end - lhs->start;
	float t = glm::dot(rhs->center - lhs->start, d) / glm::dot(d, d);
	if (t < 0.0f || t > 1.0f)
	{
		return false;
	}

	glm::vec2 pos = lhs->start + d * t;
	pos = pos - rhs->center;
	float r2 = rhs->radius * rhs->radius;

	return glm::length2(pos) <= r2;
}

bool Line2D::Intersect(const ICollider2D* collider) const
{
	CHECK(collider != nullptr);

	EType type = collider->GetType();
	bool bIsIntersect = false;

	switch (type)
	{
	case ICollider2D::EType::LINE:
	{
		const Line2D* other = reinterpret_cast<const Line2D*>(collider);
		bIsIntersect = IsCollision(this, other);
	}
	break;

	case ICollider2D::EType::CIRCLE:
	{
		const Circle2D* other = reinterpret_cast<const Circle2D*>(collider);
		bIsIntersect = IsCollision(this, other);
	}
	break;

	case ICollider2D::EType::AABB:
	{
		const Rect2D* other = reinterpret_cast<const Rect2D*>(collider);
	}	
	break;

	case ICollider2D::EType::OBB:
	{
		const OrientedRect2D* other = reinterpret_cast<const OrientedRect2D*>(collider);
	}
	break;

	default: 
		break;// ICollider2D::EType::NONE:
	}

	return bIsIntersect;
}
