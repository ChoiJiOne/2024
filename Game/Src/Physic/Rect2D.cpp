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

bool Rect2D::Intersect(const ICollider2D* collider) const
{
	return false;
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
