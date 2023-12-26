#pragma once

#include <algorithm>
#include <cmath>
#include <chrono>
#include <random>

#include "Matrix2x2.h"
#include "Matrix3x3.h"
#include "Matrix4x4.h"
#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"


/**
 * @brief ����(��) ���Դϴ�.
 */
const float Pi = 3.141592654f;


/**
 * @brief 2����(2��) ���Դϴ�.
 */
const float TwoPi = 6.283185307f;


/**
 * @brief ����(��) �� ���� ���Դϴ�.
 */
const float OneDivPi = 0.318309886f;


/**
 * @brief 2����(2��) �� ���� ���Դϴ�.
 */
const float OneDivTwoPi = 0.159154943f;


/**
 * @brief ����(��) �� �ݰ�(��/2)�Դϴ�.
 */
const float PiDiv2 = 1.570796327f;


/**
 * @brief ����(��) �� ���� �� ��(��/4)�Դϴ�.
 */
const float PiDiv4 = 0.785398163f;


/**
 * @brief ���� ���Ѵ� ���Դϴ�.
 */
const float Infinity = std::numeric_limits<float>::infinity();


/**
 * @brief ���� ���Ѵ� ���Դϴ�.
 */
const float NInfinity = -std::numeric_limits<float>::infinity();


/**
 * @brief ���Ƿ�(��) ���Դϴ�.
 */
const float Epsilon = std::numeric_limits<float>::epsilon();


/**
 * @brief ���� ���� Ȯ�� ����� �����մϴ�.
 */
class MathUtils
{
public:
};