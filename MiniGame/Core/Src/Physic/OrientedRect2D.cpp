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

/** 축을 기준으로 OBB와 OBB가 오버랩(겹치는지) 확인 */
bool IsOverlapOnAxis(const OrientedRect2D* lhs, const OrientedRect2D* rhs, const glm::vec2& axis)
{
	float min0 = 0.0f;
	float max0 = 0.0f;
	lhs->GetInterval(axis, min0, max0);

	float min1 = 0.0f;
	float max1 = 0.0f;
	rhs->GetInterval(axis, min1, max1);

	return ((min1 <= max0) && (min0 <= max1));
}

/** OBB와 OBB 끼리의 충돌 처리 */
bool IsCollision(const OrientedRect2D* lhs, const OrientedRect2D* rhs)
{
	float rotate0 = lhs->rotate;
	glm::mat2 roateMat0(glm::cos(rotate0), -glm::sin(rotate0), glm::sin(rotate0), glm::cos(rotate0));

	float rotate1 = rhs->rotate;
	glm::mat2 roateMat1(glm::cos(rotate1), -glm::sin(rotate1), glm::sin(rotate1), glm::cos(rotate1));

	std::array<glm::vec2, 6> separateAxis =
	{
		glm::vec2(1.0f, 0.0f),
		glm::vec2(0.0f, 1.0f),
		glm::normalize(glm::vec2(lhs->size.x * 0.5f,               0.0f)) * roateMat0,
		glm::normalize(glm::vec2(              0.0f, lhs->size.y * 0.5f)) * roateMat0,
		glm::normalize(glm::vec2(rhs->size.x * 0.5f,               0.0f)) * roateMat1,
		glm::normalize(glm::vec2(              0.0f, rhs->size.y * 0.5f)) * roateMat1,
	};

	for (const auto& axis : separateAxis)
	{
		if (!IsOverlapOnAxis(lhs, rhs, axis))
		{
			return false;
		}
	}

	return true;
}

bool OrientedRect2D::Intersect(const ICollider2D* collider) const
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
		bIsIntersect = other->Intersect(this);
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

void OrientedRect2D::GetInterval(const glm::vec2& axis, float& outMin, float& outMax) const
{
	Rect2D rect(center, size);
	glm::vec2 minPos = rect.GetMin();
	glm::vec2 maxPos = rect.GetMax();

	std::array<glm::vec2, 4> vertices =
	{
		glm::vec2(minPos.x, minPos.y),
		glm::vec2(minPos.x, maxPos.y),
		glm::vec2(maxPos.x, maxPos.y),
		glm::vec2(maxPos.x, minPos.y),
	};

	glm::mat2 roateMat(glm::cos(rotate), -glm::sin(rotate), glm::sin(rotate), glm::cos(rotate));
	for (int32_t index = 0; index < vertices.size(); ++index)
	{
		glm::vec2 colliderPos = (vertices[index] - center) * roateMat;
		vertices[index] = colliderPos + center;
	}

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
