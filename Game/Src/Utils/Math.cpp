#include <chrono>
#include <random>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/vector_angle.hpp>

#include "Utils/Math.h"

float GetRadianVec2(const glm::vec2& v)
{
	float rotate = glm::angle(glm::vec2(1.0f, 0.0f), v);
	return v.y < 0.0f ? (2.0f * glm::pi<float>() - rotate) : rotate;
}

int32_t GenerateRandomInt(int32_t minValue, int32_t maxValue)
{
	std::random_device randomDevice;
	std::mt19937 generator(randomDevice());
	std::uniform_int_distribution<int32_t> distribution(glm::min<int32_t>(minValue, maxValue), glm::max<int32_t>(minValue, maxValue));

	return distribution(generator);
}

float GenerateRandomFloat(float minValue, float maxValue)
{
	std::random_device randomDevice;
	std::mt19937 generator(randomDevice());
	std::uniform_real_distribution<float> distribution(glm::min<float>(minValue, maxValue), glm::max<float>(minValue, maxValue));

	return distribution(generator);
}

glm::vec2 GenerateRandomDisk(float radius)
{
	float radian = GenerateRandomFloat(0.0f, 2.0f * glm::pi<float>());
	float r = GenerateRandomFloat(0.0f, radius);
	return glm::vec2(r * glm::cos(radian), r * glm::sin(radian));
}