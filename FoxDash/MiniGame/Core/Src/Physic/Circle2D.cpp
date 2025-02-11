#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtc/constants.hpp>
#include <glm/gtc/epsilon.hpp>
#include <glm/gtx/norm.hpp>

#include "Physic/Circle2D.h"
#include "Physic/Line2D.h"
#include "Physic/OrientedRect2D.h"
#include "Physic/Rect2D.h"
#include "Utils/Assertion.h"

/** 원과 원 끼리의 충돌 처리 */
bool IsCollision(const Circle2D* lhs, const Circle2D* rhs)
{
	float dist = glm::length2(rhs->center - lhs->center);
	float radiusSum = lhs->radius + rhs->radius;

	return dist <= radiusSum * radiusSum;
}

/** 원과 AABB 끼리의 충돌 처리 */
bool IsCollision(const Circle2D* lhs, const Rect2D* rhs)
{
	glm::vec2 minPos = rhs->GetMin();
	glm::vec2 maxPos = rhs->GetMax();
	glm::vec2 closest(glm::clamp<float>(lhs->center.x, minPos.x, maxPos.x), glm::clamp<float>(lhs->center.y, minPos.y, maxPos.y));

	float dist = glm::length2(closest - lhs->center);
	float r2 = lhs->radius * lhs->radius;

	return dist <= r2;
}

/** 원과 OBB 끼리의 충돌 처리 */
bool IsCollision(const Circle2D* lhs, const OrientedRect2D* rhs)
{
	float rotate = -rhs->rotate;
	glm::mat2 roateMat(glm::cos(rotate), -glm::sin(rotate), glm::sin(rotate), glm::cos(rotate));
	glm::vec2 center = (lhs->center - rhs->center) * roateMat;

	Circle2D circle(center, lhs->radius);
	Rect2D rect(glm::vec2(0.0f, 0.0f), rhs->size);
	
	return IsCollision(&circle, &rect);
}

bool Circle2D::Intersect(const ICollider2D* collider) const
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
		bIsIntersect = IsCollision(this, other);
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
