#pragma once

#include <glm/glm.hpp>

/**
 * 2차원 벡터의 라디안 각도 값을 얻습니다.
 * 이때, 각도의 범위는 [0, 2pi] 입니다.
 */
float GetRadianVec2(const glm::vec2& v);