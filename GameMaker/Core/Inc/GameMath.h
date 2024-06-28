#pragma once

#include <chrono>
#include <cstdint>
#include <limits>
#include <random>


namespace GameMaker
{
	/**
	 * @brief ����(��) ���Դϴ�.
	 */
	const float PI = 3.141592654f;


	/**
	 * @brief 2����(2��) ���Դϴ�.
	 */
	const float TWO_PI = 6.283185307f;


	/**
	 * @brief ����(��) �� ���� ���Դϴ�.
	 */
	const float ONE_DIV_PI = 0.318309886f;


	/**
	 * @brief 2����(2��) �� ���� ���Դϴ�.
	 */
	const float ONE_DIV_2PI = 0.159154943f;


	/**
	 * @brief ����(��) �� �ݰ�(��/2)�Դϴ�.
	 */
	const float PI_DIV_2 = 1.570796327f;


	/**
	 * @brief ����(��) �� ���� �� ��(��/4)�Դϴ�.
	 */
	const float PI_DIV_4 = 0.785398163f;


	/**
	 * @brief ���Ƿ�(��) ���Դϴ�.
	 */
	const float EPSILON = 1.192092896e-07F;


	/**
	 * @brief ���� ���� ���ʺй� ������ ��ȯ�մϴ�.
	 *
	 * @param radian ��ȯ�� ���� ���Դϴ�.
	 *
	 * @return ��ȯ�� ���ʺй� ���Դϴ�.
	 */
	__forceinline float ToDegree(float radian)
	{
		return (radian * 180.0f) / PI;
	}


	/**
	 * @brief ���ʺй� ���� ���� ������ ��ȯ�մϴ�.
	 *
	 * @param degree ��ȯ�� ���ʺй� ���Դϴ�.
	 *
	 * @return ��ȯ�� ���� ���Դϴ�.
	 */
	__forceinline float ToRadian(float degree)
	{
		return (degree * PI) / 180.0f;
	}


	/**
	 * @brief �ε� �Ҽ��� ���� 0�� ������� Ȯ���մϴ�.
	 *
	 * @param value 0�� ������� Ȯ���� ���Դϴ�.
	 * @param epsilon �� Ȯ���� ���� ���Ƿ� ���Դϴ�.
	 *
	 * @return �ε� �Ҽ��� ���� 0�� �����ٸ� true, �׷��� �ʴٸ� false�� ��ȯ�մϴ�.
	 */
	__forceinline bool NearZero(float value, float epsilon = EPSILON)
	{
		return (std::fabsf(value) <= epsilon);
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
	__forceinline T Max(const T& lhs, const T& rhs)
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
	__forceinline T Min(const T& lhs, const T& rhs)
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
	__forceinline float Sin(float radian)
	{
		float quotient = ONE_DIV_2PI * radian;
		if (radian >= 0.0f)
		{
			quotient = static_cast<float>(static_cast<int>(quotient + 0.5f));
		}
		else
		{
			quotient = static_cast<float>(static_cast<int>(quotient - 0.5f));
		}

		float y = radian - TWO_PI * quotient;

		if (y > PI_DIV_2)
		{
			y = PI - y;
		}
		else if (y < -PI_DIV_2)
		{
			y = -PI - y;
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
	__forceinline float Cos(float radian)
	{
		float quotient = ONE_DIV_2PI * radian;
		if (radian >= 0.0f)
		{
			quotient = static_cast<float>(static_cast<int>(quotient + 0.5f));
		}
		else
		{
			quotient = static_cast<float>(static_cast<int>(quotient - 0.5f));
		}

		float y = radian - TWO_PI * quotient;
		float sign = 1.0f;

		if (y > PI_DIV_2)
		{
			y = PI - y;
			sign = -1.0f;
		}
		else if (y < -PI_DIV_2)
		{
			y = -PI - y;
			sign = -1.0f;
		}

		float y2 = y * y;
		float p = ((((-2.6051615e-07f * y2 + 2.4760495e-05f) * y2 - 0.0013888378f) * y2 + 0.041666638f) * y2 - 0.5f) * y2 + 1.0f;

		return sign * p;
	}


	/**
	 * @brief �ε� �Ҽ��� ������ ��ũ ������ ����մϴ�.
	 *
	 * @param value -1.0 ���� 1.0 ������ ���Դϴ�.
	 *
	 * @return �Է��� ���� ��ũ ����(�� ����) ���� ��ȯ�մϴ�.
	 *
	 * @note
	 * - DirectXMath�� XMScalarASin ����
	 * - �˰����� 7���� �̴ϸƽ�(Minimax) �ٻ�ġ(1th-degree Minimax approximation) ���
	 * - https://gist.github.com/publik-void/067f7f2fef32dbe5c27d6e215f824c91
	 */
	__forceinline float ASin(float value)
	{
		float x = std::fabsf(value);
		float omx = 1.0f - x;
		if (omx < 0.0f)
		{
			omx = 0.0f;
		}

		float root = sqrtf(omx);
		float result = ((((((-0.0012624911f * x + 0.0066700901f) * x - 0.0170881256f) * x + 0.0308918810f) * x - 0.0501743046f) * x + 0.0889789874f) * x - 0.2145988016f) * x + 1.5707963050f;
		result *= root;

		if (value >= 0.0f)
		{
			return (PI_DIV_2 - result);
		}
		else
		{
			return (result - PI_DIV_2);
		}
	}


	/**
	 * @brief �ε� �Ҽ��� ������ ��ũ �ڻ����� ����մϴ�.
	 *
	 * @param value -1.0 ���� 1.0 ������ ���Դϴ�.
	 *
	 * @return �Է��� ���� �ھ�ũ ����(�� ����) ���� ��ȯ�մϴ�.
	 *
	 * @note
	 * - DirectXMath�� XMScalarACos ����
	 * - �˰����� 7���� �̴ϸƽ�(Minimax) �ٻ�ġ(1th-degree Minimax approximation) ���
	 * - https://gist.github.com/publik-void/067f7f2fef32dbe5c27d6e215f824c91
	 */
	__forceinline float ACos(float value)
	{
		float x = std::fabsf(value);
		float omx = 1.0f - x;
		if (omx < 0.0f)
		{
			omx = 0.0f;
		}

		float root = sqrtf(omx);
		float result = ((((((-0.0012624911f * x + 0.0066700901f) * x - 0.0170881256f) * x + 0.0308918810f) * x - 0.0501743046f) * x + 0.0889789874f) * x - 0.2145988016f) * x + 1.5707963050f;
		result *= root;

		if (value >= 0.0f)
		{
			return result;
		}
		else
		{
			return PI - result;
		}
	}


	/**
	 * @brief �������� ����մϴ�.
	 *
	 * @param x �������� ����� �ε��Ҽ������Դϴ�.
	 *
	 * @return ������ ���� ��ȯ�մϴ�.
	 */
	__forceinline float Sqrt(float x)
	{
		return std::sqrtf(x);
	}
}