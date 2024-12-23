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

/** 반지름 위의 임의의 벡터를 생성합니다. */
glm::vec2 GenerateRandomRadius(float radius);

/** 반지름 내의 임의의 벡터를 생성합니다. */
glm::vec2 GenerateRandomDisk(float radius);

/** 
 * 특정 벡터를 기준으로 라디안 각도 범위 내에 벡터를 생성합니다. 
 * 단, 생성된 벡터는 정규화된 벡터입니다.
 */
glm::vec2 GenerateRandomVec2(const glm::vec2& v, float radian);