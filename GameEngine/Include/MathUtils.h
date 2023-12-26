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
	/**
	 * @brief ���� ���� ���ʺй� ������ ��ȯ�մϴ�.
	 *
	 * @param radian ��ȯ�� ���� ���Դϴ�.
	 *
	 * @return ��ȯ�� ���ʺй� ���Դϴ�.
	 */
	static inline float ToDegree(float radian)
	{
		return (radian * 180.0f) / Pi;
	}


	/**
	 * @brief ���ʺй� ���� ���� ������ ��ȯ�մϴ�.
	 *
	 * @param degree ��ȯ�� ���ʺй� ���Դϴ�.
	 *
	 * @return ��ȯ�� ���� ���Դϴ�.
	 */
	static inline float ToRadian(float degree)
	{
		return (degree * Pi) / 180.0f;
	}


	/**
	 * @brief �ε� �Ҽ��� ���� 0�� ������� Ȯ���մϴ�.
	 *
	 * @param value 0�� ������� Ȯ���� ���Դϴ�.
	 * @param epsilon �� Ȯ���� ���� ���Ƿ� ���Դϴ�.
	 *
	 * @return �ε� �Ҽ��� ���� 0�� �����ٸ� true, �׷��� �ʴٸ� false�� ��ȯ�մϴ�.
	 */
	static inline bool NearZero(float value, float epsilon = Epsilon)
	{
		return (std::fabs(value) <= epsilon);
	}


	/**
	 * @brief �� ���� ū ���� ��ȯ�մϴ�.
	 *
	 * @param lhs ũ�⸦ ���� �� �� ���� ���Դϴ�.
	 * @param rhs ũ�⸦ ���� �� �� ������ ���Դϴ�.
	 *
	 * @return �� �� �� ū ���� ��ȯ�մϴ�.
	 */
	template <typename T>
	static inline T Max(const T& lhs, const T& rhs)
	{
		return (lhs < rhs ? rhs : lhs);
	}


	/**
	 * @brief �� ���� ���� ���� ��ȯ�մϴ�.
	 *
	 * @param lhs ũ�⸦ ���� �� �� ���� ���Դϴ�.
	 * @param rhs ũ�⸦ ���� �� �� ������ ���Դϴ�.
	 *
	 * @return �� �� �� ���� ���� ��ȯ�մϴ�.
	 */
	template <typename T>
	static inline T Min(const T& lhs, const T& rhs)
	{
		return (lhs < rhs ? lhs : rhs);
	}


	/**
	 * @brief ���� ������ �����ϴ� ���� ���� ����ϴ�.
	 * 
	 * @param radian ���� ���� ���� ���� �����Դϴ�.
	 * 
	 * @return ���� ������ �����ϴ� ���ΰ��� ��ȯ�մϴ�.
	 * 
	 * @note
	 * - DirectXMath�� XMScalarSin ����
	 * - �˰����� 11���� �̴ϸƽ�(Minimax) �ٻ�ġ(1th-degree Minimax approximation) ���
	 * - https://gist.github.com/publik-void/067f7f2fef32dbe5c27d6e215f824c91
	 */
	static inline float Sin(float radian)
	{
		float quotient = OneDivTwoPi * radian;
		if (radian >= 0.0f)
		{
			quotient = static_cast<float>(static_cast<int>(quotient + 0.5f));
		}
		else
		{
			quotient = static_cast<float>(static_cast<int>(quotient - 0.5f));
		}

		float y = radian - TwoPi * quotient;

		if (y > PiDiv2)
		{
			y = Pi - y;
		}
		else if (y < -PiDiv2)
		{
			y = -Pi - y;
		}

		float y2 = y * y;
		return (((((-2.3889859e-08f * y2 + 2.7525562e-06f) * y2 - 0.00019840874f) * y2 + 0.0083333310f) * y2 - 0.16666667f) * y2 + 1.0f) * y;
	}


	/**
	 * @brief ���� ������ �����ϴ� �ڻ��� ���� ��ȯ�մϴ�.
	 *
	 * @param radian �ڻ��� ���� ���� ���� �����Դϴ�.
	 *
	 * @return ���� ������ �����ϴ� �ڻ��ΰ��� ��ȯ�մϴ�.
	 *
	 * @note
	 * - DirectXMath�� XMScalarCos ����
	 * - �˰����� 10���� �̴ϸƽ�(Minimax) �ٻ�ġ(1th-degree Minimax approximation) ���
	 * - https://gist.github.com/publik-void/067f7f2fef32dbe5c27d6e215f824c91
	 */
	static inline float Cos(float radian)
	{
		float quotient = OneDivTwoPi * radian;
		if (radian >= 0.0f)
		{
			quotient = static_cast<float>(static_cast<int>(quotient + 0.5f));
		}
		else
		{
			quotient = static_cast<float>(static_cast<int>(quotient - 0.5f));
		}

		float y = radian - TwoPi * quotient;
		float sign = 1.0f;

		if (y > PiDiv2)
		{
			y = Pi - y;
			sign = -1.0f;
		}
		else if (y < -PiDiv2)
		{
			y = -Pi - y;
			sign = -1.0f;
		}

		float y2 = y * y;
		float p = ((((-2.6051615e-07f * y2 + 2.4760495e-05f) * y2 - 0.0013888378f) * y2 + 0.041666638f) * y2 - 0.5f) * y2 + 1.0f;

		return sign * p;
	}


	/**
	 * @brief ���� [lower, upper] ������ �ڸ��ϴ�.
	 *
	 * @param value ������ �ڸ� ���Դϴ�.
	 * @param lower ������ �ּҰ��Դϴ�.
	 * @param upper ������ �ִ밪�Դϴ�.
	 *
	 * @return ������ �߷� ���� ���� ��ȯ�մϴ�.
	 */
	template <typename T>
	static inline T Clamp(const T& value, const T& lower, const T& upper)
	{
		return Min(upper, Max(lower, value));
	}
};