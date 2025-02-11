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

/** ������ ���� ������ ���͸� �����մϴ�. */
glm::vec2 GenerateRandomRadius(float radius);

/** ������ ���� ������ ���͸� �����մϴ�. */
glm::vec2 GenerateRandomDisk(float radius);

/** 
 * Ư�� ���͸� �������� ���� ���� ���� ���� ���͸� �����մϴ�. 
 * ��, ������ ���ʹ� ����ȭ�� �����Դϴ�.
 */
glm::vec2 GenerateRandomVec2(const glm::vec2& v, float radian);