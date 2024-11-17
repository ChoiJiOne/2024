#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/vector_angle.hpp>

#include "Utils/Math.h"

float GetRadianVec2(const glm::vec2& v)
{
	float rotate = glm::angle(glm::vec2(1.0f, 0.0f), v);
	return v.y < 0.0f ? (2.0f * glm::pi<float>() - rotate) : rotate;
}