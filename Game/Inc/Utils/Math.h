#pragma once

#include <glm/glm.hpp>

/**
 * 2���� ������ ���� ���� ���� ����ϴ�.
 * �̶�, ������ ������ [0, 2pi] �Դϴ�.
 */
float GetRadianVec2(const glm::vec2& v);

/** [minValue, maxValue] ������ ������ ������ �����մϴ�. */
int32_t GenerateRandomInt(int32_t minValue, int32_t maxValue);

/** [minValue, maxValue] ������ ������ �ε� �Ҽ��� ������ �����մϴ�. */
float GenerateRandomFloat(float minValue, float maxValue);