#pragma once

#include <glm/glm.hpp>

/**
 * 2차원 벡터의 라디안 각도 값을 얻습니다.
 * 이때, 각도의 범위는 [0, 2pi] 입니다.
 */
float GetRadianVec2(const glm::vec2& v);

/** [minValue, maxValue] 범위의 임의의 난수를 생성합니다. */
int32_t GenerateRandomInt(int32_t minValue, int32_t maxValue);

/** [minValue, maxValue] 범위의 임의의 부동 소수점 난수를 생성합니다. */
float GenerateRandomFloat(float minValue, float maxValue);