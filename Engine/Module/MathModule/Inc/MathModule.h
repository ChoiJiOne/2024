#pragma once

#include <cstdint>
#include <limits>


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
 * @brief ���Ƿ�(��) ���Դϴ�.
 */
const float Epsilon = 1.192092896e-07F;


/**
 * @brief ���� ���Ѵ� ���Դϴ�.
 */
const float Infinity = std::numeric_limits<float>::infinity();


/**
 * @brief ���� ���Ѵ� ���Դϴ�.
 */
const float NegInfinity = -std::numeric_limits<float>::infinity();


/**
 * ���� ���� ����� �����մϴ�.
 */
class MathModule
{
public:
	/**
	 * @brief ���� ���� ���ʺй� ������ ��ȯ�մϴ�.
	 *
	 * @param radian ��ȯ�� ���� ���Դϴ�.
	 *
	 * @return ��ȯ�� ���ʺй� ���Դϴ�.
	 */
	static __forceinline float ToDegree(float radian)
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
	static __forceinline float ToRadian(float degree)
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
	static bool NearZero(float value, float epsilon = Epsilon);


	/**
	 * @brief �� ���� ū ���� ��ȯ�մϴ�.
	 *
	 * @param lhs ũ�⸦ ���� �� �� ���� ���Դϴ�.
	 * @param rhs ũ�⸦ ���� �� �� ������ ���Դϴ�.
	 *
	 * @return �� �� �� ū ���� ��ȯ�մϴ�.
	 */
	template <typename T>
	static __forceinline T Max(const T& lhs, const T& rhs)
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
	static __forceinline T Min(const T& lhs, const T& rhs)
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
	static __forceinline float Sin(float radian)
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
	static __forceinline float Cos(float radian)
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
	static float ASin(float value);


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
	static float ACos(float value);


	/**
	 * @brief �������� ����մϴ�.
	 *
	 * @param x �������� ����� �ε��Ҽ������Դϴ�.
	 *
	 * @return ������ ���� ��ȯ�մϴ�.
	 */
	static float Sqrt(float x);


	/**
	 * @brief ������ ����մϴ�.
	 *
	 * @param x ������ ����� �ε��Ҽ������Դϴ�.
	 *
	 * @return ���밪�� ��ȯ�մϴ�.
	 */
	static float Abs(float x);


	/**
	 * @brief �ε� �Ҽ��� �������� ����մϴ�.
	 * 
	 * @param x �ε� �Ҽ��� �������� ����� ���� �ǿ������Դϴ�.
	 * @param y �ε� �Ҽ��� �������� ����� ������ �ǿ������Դϴ�.
	 * 
	 * @return ���� �ε� �Ҽ��� �������� ��ȯ�մϴ�.
	 */
	static float Fmod(float x, float y);


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
	static __forceinline T Clamp(const T& value, const T& lower, const T& upper)
	{
		return Min<T>(upper, Max<T>(lower, value));
	}
	

	/**
	 * @brief ������ ������ �����մϴ�.
	 *
	 * @param minValue ������ ���� ������ �ּڰ��Դϴ�.
	 * @param maxValue ������ ���� ������ �ִ��Դϴ�.
	 *
	 * @return ������ ������ ������ ��ȯ�մϴ�.
	 */
	static int32_t GenerateRandomInt(int32_t minValue, int32_t maxValue);


	/**
	 * @brief ������ �Ǽ��� �����մϴ�.
	 *
	 * @param minValue ������ ���� ������ �ּڰ��Դϴ�.
	 * @param maxValue ������ ���� ������ �ִ��Դϴ�.
	 *
	 * @return ������ ������ �Ǽ��� ��ȯ�մϴ�.
	 */
	static float GenerateRandomFloat(float minValue, float maxValue);
};