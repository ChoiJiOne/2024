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


	/**
	 * @brief ������ ����մϴ�.
	 *
	 * @param x ������ ����� �ε��Ҽ������Դϴ�.
	 *
	 * @return ���밪�� ��ȯ�մϴ�.
	 */
	__forceinline float Abs(float x)
	{
		return std::fabsf(x);
	}


	/**
	 * @brief �ε� �Ҽ��� �������� ����մϴ�.
	 *
	 * @param x �ε� �Ҽ��� �������� ����� ���� �ǿ������Դϴ�.
	 * @param y �ε� �Ҽ��� �������� ����� ������ �ǿ������Դϴ�.
	 *
	 * @return ���� �ε� �Ҽ��� �������� ��ȯ�մϴ�.
	 */
	__forceinline float Fmod(float x, float y)
	{
		return std::fmodf(x, y);
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
	__forceinline T Clamp(const T& value, const T& lower, const T& upper)
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
	__forceinline int32_t GenerateRandomInt(int32_t minValue, int32_t maxValue)
	{
		std::random_device randomDevice;
		std::mt19937 generator(randomDevice());
		std::uniform_int_distribution<int32_t> distribution(Min<int32_t>(minValue, maxValue), Max<int32_t>(minValue, maxValue));

		return distribution(generator);
	}


	/**
	 * @brief ������ �Ǽ��� �����մϴ�.
	 *
	 * @param minValue ������ ���� ������ �ּڰ��Դϴ�.
	 * @param maxValue ������ ���� ������ �ִ��Դϴ�.
	 *
	 * @return ������ ������ �Ǽ��� ��ȯ�մϴ�.
	 */
	__forceinline float GenerateRandomFloat(float minValue, float maxValue)
	{
		std::random_device randomDevice;
		std::mt19937 generator(randomDevice());
		std::uniform_real_distribution<float> distribution(Min<float>(minValue, maxValue), Max<float>(minValue, maxValue));

		return distribution(generator);
	}


/**
 * @brief ������ ������ Ÿ���� ������ 2���� �����Դϴ�.
 */
struct Vec2i
{
	/**
	 * @brief 2���� ������ �⺻ �������Դϴ�.
	 *
	 * @note ��� ������ ���� 0���� �ʱ�ȭ�մϴ�.
	 */
	Vec2i() noexcept : x(0), y(0) {}


	/**
	 * @brief 2���� ������ �������Դϴ�.
	 *
	 * @param xx ������ x �����Դϴ�.
	 * @param yy ������ y �����Դϴ�.
	 */
	Vec2i(int32_t&& xx, int32_t&& yy) noexcept : x(xx), y(yy) {}


	/**
	 * @brief 2���� ������ �������Դϴ�.
	 *
	 * @param xx ������ x �����Դϴ�.
	 * @param yy ������ y �����Դϴ�.
	 */
	Vec2i(const int32_t& xx, const int32_t& yy) noexcept : x(xx), y(yy) {}


	/**
	 * @brief 2���� ������ ���Ҹ� �ϳ��� ������ �ʱ�ȭ�մϴ�.
	 *
	 * @param e ��� ���Ҹ� �ʱ�ȭ �� ���Դϴ�.
	 */
	Vec2i(int32_t&& e) noexcept : x(e), y(e) {}


	/**
	 * @brief 2���� ������ ���Ҹ� �ϳ��� ������ �ʱ�ȭ�մϴ�.
	 *
	 * @param e ��� ���Ҹ� �ʱ�ȭ �� ���Դϴ�.
	 */
	Vec2i(const int32_t& e) noexcept : x(e), y(e) {}


	/**
	 * @brief 2���� ������ ���� �������Դϴ�.
	 *
	 * @param v ���Ҹ� ������ ���� ����ü�� �ν��Ͻ��Դϴ�.
	 */
	Vec2i(Vec2i&& v) noexcept : x(v.x), y(v.y) {}


	/**
	 * @brief 2���� ������ ���� �������Դϴ�.
	 *
	 * @param v ���Ҹ� ������ ������ �ν��Ͻ��Դϴ�.
	 */
	Vec2i(const Vec2i& v) noexcept : x(v.x), y(v.y) {}


	/**
	 * @brief 2���� ������ ���� ������ �Դϴ�.
	 *
	 * @param v ���Ҹ� ������ ���� ����ü�� �ν��Ͻ��Դϴ�.
	 *
	 * @return ������ ������ �����ڸ� ��ȯ�մϴ�.
	 */
	Vec2i& operator=(Vec2i&& v) noexcept
	{
		if (this == &v) return *this;

		x = v.x;
		y = v.y;

		return *this;
	}


	/**
	 * @brief 2���� ������ ���� ������ �Դϴ�.
	 *
	 * @param v ���Ҹ� ������ ���� ����ü�� �ν��Ͻ��Դϴ�.
	 *
	 * @return ������ ������ �����ڸ� ��ȯ�մϴ�.
	 */
	Vec2i& operator=(const Vec2i& v) noexcept
	{
		if (this == &v) return *this;

		x = v.x;
		y = v.y;

		return *this;
	}


	/**
	 * @brief 2���� ������ ���ҿ� -��ȣ�� ���մϴ�.
	 *
	 * @return 2���� ������ ���ҿ� -��ȣ�� ���� ���ο� ���͸� ��ȯ�մϴ�.
	 */
	Vec2i operator-() const
	{
		return Vec2i(-x, -y);
	}


	/**
	 * @brief �� 2���� ���Ϳ� �����ϴ� ���Ҹ� ���մϴ�.
	 *
	 * @param v ������ ������ ������ �ǿ������Դϴ�.
	 *
	 * @return �� ���Ϳ� �����ϴ� ���Ҹ� ���� ����� ��ȯ�մϴ�.
	 */
	Vec2i operator+(Vec2i&& v) const
	{
		return Vec2i(x + v.x, y + v.y);
	}


	/**
	 * @brief �� 2���� ���Ϳ� �����ϴ� ���Ҹ� ���մϴ�.
	 *
	 * @param v ������ ������ ������ �ǿ������Դϴ�.
	 *
	 * @return �� ���Ϳ� �����ϴ� ���Ҹ� ���� ����� ��ȯ�մϴ�.
	 */
	Vec2i operator+(const Vec2i& v) const
	{
		return Vec2i(x + v.x, y + v.y);
	}


	/**
	 * @brief �� 2���� ���Ϳ� �����ϴ� ���Ҹ� ���ϴ�.
	 *
	 * @param v ������ ������ ������ �ǿ������Դϴ�.
	 *
	 * @return �� ���Ϳ� �����ϴ� ���Ҹ� �� ����� ��ȯ�մϴ�.
	 */
	Vec2i operator-(Vec2i&& v) const
	{
		return Vec2i(x - v.x, y - v.y);
	}


	/**
	 * @brief �� 2���� ���Ϳ� �����ϴ� ���Ҹ� ���ϴ�.
	 *
	 * @param v ������ ������ ������ �ǿ������Դϴ�.
	 *
	 * @return �� ���Ϳ� �����ϴ� ���Ҹ� �� ����� ��ȯ�մϴ�.
	 */
	Vec2i operator-(const Vec2i& v) const
	{
		return Vec2i(x - v.x, y - v.y);
	}


	/**
	 * @brief �� 2���� ���Ϳ� �����ϴ� ���Ҹ� ���� ���մϴ�.
	 *
	 * @note �� ������ ������ ���� ����(Dot Product)�ʹ� �ٸ��ϴ�.
	 *
	 * @param v ������ ������ ������ �ǿ������Դϴ�.
	 *
	 * @return �� ���Ϳ� �����ϴ� ���Ҹ� ���� ����� ��ȯ�մϴ�.
	 */
	Vec2i operator*(Vec2i&& v) const
	{
		return Vec2i(x * v.x, y * v.y);
	}


	/**
	 * @brief �� 2���� ���Ϳ� �����ϴ� ���Ҹ� ���� ���մϴ�.
	 *
	 * @note �� ������ ������ ���� ����(Dot Product)�ʹ� �ٸ��ϴ�.
	 *
	 * @param v ������ ������ ������ �ǿ������Դϴ�.
	 *
	 * @return �� ���Ϳ� �����ϴ� ���Ҹ� ���� ����� ��ȯ�մϴ�.
	 */
	Vec2i operator*(const Vec2i& v) const
	{
		return Vec2i(x * v.x, y * v.y);
	}


	/**
	 * @brief �� 2���� ���Ϳ� �����ϴ� ���Ҹ� ���մϴ�.
	 *
	 * @param v ������ ������ �ǿ������Դϴ�.
	 *
	 * @return ������ ������ ������ �����ڸ� ��ȯ�մϴ�.
	 */
	Vec2i& operator+=(Vec2i&& v) noexcept
	{
		x += v.x;
		y += v.y;

		return *this;
	}


	/**
	 * @brief �� 2���� ���Ϳ� �����ϴ� ���Ҹ� ���մϴ�.
	 *
	 * @param v ������ ������ �ǿ������Դϴ�.
	 *
	 * @return ������ ������ ������ �����ڸ� ��ȯ�մϴ�.
	 */
	Vec2i& operator+=(const Vec2i& v) noexcept
	{
		x += v.x;
		y += v.y;

		return *this;
	}


	/**
	 * @brief �� 2���� ���Ϳ� �����ϴ� ���Ҹ� ���ϴ�.
	 *
	 * @param v ������ ������ �ǿ������Դϴ�.
	 *
	 * @return ������ ������ ������ �����ڸ� ��ȯ�մϴ�.
	 */
	Vec2i& operator-=(Vec2i&& v) noexcept
	{
		x -= v.x;
		y -= v.y;

		return *this;
	}


	/**
	 * @brief �� 2���� ���Ϳ� �����ϴ� ���Ҹ� ���ϴ�.
	 *
	 * @param v ������ ������ �ǿ������Դϴ�.
	 *
	 * @return ������ ������ ������ �����ڸ� ��ȯ�մϴ�.
	 */
	Vec2i& operator-=(const Vec2i& v) noexcept
	{
		x -= v.x;
		y -= v.y;

		return *this;
	}


	/**
	 * @brief �� 2���� ������ �����ϴ� ���Ұ� �������� Ȯ���մϴ�.
	 *
	 * @param v ������ ������ �ǿ������Դϴ�.
	 *
	 * @return �� 2���� ������ �����ϴ� ���Ұ� ��ġ�Ѵٸ� true, �׷��� ������ false�� ��ȯ�մϴ�.
	 */
	bool operator==(Vec2i&& v) noexcept
	{
		return (x == v.x) && (y == v.y);
	}


	/**
	 * @brief �� 2���� ������ �����ϴ� ���Ұ� �������� Ȯ���մϴ�.
	 *
	 * @param v ������ ������ �ǿ������Դϴ�.
	 *
	 * @return �� 2���� ������ �����ϴ� ���Ұ� ��ġ�Ѵٸ� true, �׷��� ������ false�� ��ȯ�մϴ�.
	 */
	bool operator==(const Vec2i& v) noexcept
	{
		return (x == v.x) && (y == v.y);
	}


	/**
	 * @brief �� 2���� ������ �����ϴ� ���Ұ� �������� ������ Ȯ���մϴ�.
	 *
	 * @param v ������ ������ �ǿ������Դϴ�.
	 *
	 * @return �� 2���� ������ �����ϴ� ���Ұ� ��ġ���� �ʴ´ٸ� true, �׷��ٸ� false�� ��ȯ�մϴ�.
	 */
	bool operator!=(Vec2i&& v) noexcept
	{
		return (x != v.x) || (y != v.y);
	}


	/**
	 * @brief �� 2���� ������ �����ϴ� ���Ұ� �������� ������ Ȯ���մϴ�.
	 *
	 * @param v ������ ������ �ǿ������Դϴ�.
	 *
	 * @return �� 2���� ������ �����ϴ� ���Ұ� ��ġ���� �ʴ´ٸ� true, �׷��ٸ� false�� ��ȯ�մϴ�.
	 */
	bool operator!=(const Vec2i& v) noexcept
	{
		return (x != v.x) || (y != v.y);
	}


	/**
	 * @brief 2���� ���� ���� �迭�� �����͸� ����ϴ�.
	 *
	 * @return 2���� ���� ���� �迭�� �����͸� ��ȯ�մϴ�.
	 */
	const int32_t* GetPtr() const { return &data[0]; }


	/**
	 * @brief 2���� ���� ���� �迭�� �����͸� ����ϴ�.
	 *
	 * @return 2���� ���� ���� �迭�� �����͸� ��ȯ�մϴ�.
	 */
	int32_t* GetPtr() { return &data[0]; }


	/**
	 * @brief 2���� ������ ���� ������ �����մϴ�.
	 *
	 * @param lhs ������ ���� ������ ������ ���� �ǿ������Դϴ�.
	 * @param rhs ������ ���� ������ ������ ���� �ǿ������Դϴ�.
	 *
	 * @return ���� ���� ����� ��ȯ�մϴ�.
	 */
	static inline int32_t Dot(const Vec2i& lhs, const Vec2i& rhs)
	{
		return lhs.x * rhs.x + lhs.y * rhs.y;
	}


	/**
	 * @brief 2���� ������ ���� ������ �����մϴ�.
	 *
	 * @param lhs ������ ���� ������ ������ ���� �ǿ������Դϴ�.
	 * @param rhs ������ ���� ������ ������ ���� �ǿ������Դϴ�.
	 *
	 * @return ���� ���� ����� ��ȯ�մϴ�.
	 *
	 * @note �Ϲ����� 3���� ���� ����� �ٸ��ϴ�.
	 */
	static inline int32_t Cross(const Vec2i& lhs, const Vec2i& rhs)
	{
		return lhs.x * rhs.y - lhs.y * rhs.x;
	}


	/**
	 * @brief 2���� ������ ũ�� ���� ���� ����մϴ�.
	 *
	 * @param v ũ�� ������ ����� �����Դϴ�.
	 *
	 * @return ���� ũ�� ���� ���� ��ȯ�մϴ�.
	 */
	static inline int32_t LengthSq(const Vec2i& v)
	{
		return v.x * v.x + v.y * v.y;
	}


	/**
	 * @brief 2���� ������ ũ�⸦ ����ϴ�.
	 *
	 * @param v ũ�⸦ ����� �����Դϴ�.
	 *
	 * @return ���� ũ�� ���� ��ȯ�մϴ�.
	 */
	static inline float Length(const Vec2i& v)
	{
		float lengthSq = static_cast<float>(LengthSq(v));
		return Sqrt(lengthSq);
	}


	/**
	 * @brief �� 2���� ���� ������ ���� ����մϴ�.
	 *
	 * @param lhs ���� ������ ���� ����� ���� �ǿ����� �����Դϴ�.
	 * @param rhs ���� ������ ���� ����� ������ �ǿ����� �����Դϴ�.
	 *
	 * @return �� 2���� ���� ������ ���� ������ ��ȯ�մϴ�.
	 */
	static inline float Radian(const Vec2i& lhs, const Vec2i& rhs)
	{
		float lengthL = Length(lhs);
		float lengthR = Length(rhs);
		float dot = Dot(lhs, rhs);

		return ACos(dot / (lengthL * lengthR));
	}


	/**
	 * @brief �� 2���� ���� ������ ���� ����մϴ�.
	 *
	 * @param lhs ���� ������ ���� ����� ���� �ǿ����� �����Դϴ�.
	 * @param rhs ���� ������ ���� ����� ������ �ǿ����� �����Դϴ�.
	 *
	 * @return �� 2���� ���� ������ ���ʺй� ������ ��ȯ�մϴ�.
	 */
	static inline float Degree(const Vec2i& lhs, const Vec2i& rhs)
	{
		float radian = Radian(lhs, rhs);
		return ToDegree(radian);
	}


	/**
	 * @brief 2���� ������ �پ��� ���� �����Դϴ�.
	 */
	union
	{
		struct
		{
			int32_t x;
			int32_t y;
		};
		int32_t data[2];
	};
};


/**
 * @brief ������ ������ Ÿ���� �ε� �Ҽ����� 2���� �����Դϴ�.
 */
struct Vec2f
{
	/**
	 * @brief 2���� ������ �⺻ �������Դϴ�.
	 *
	 * @note ��� ������ ���� 0���� �ʱ�ȭ�մϴ�.
	 */
	Vec2f() noexcept : x(0.0f), y(0.0f) {}


	/**
	 * @brief 2���� ������ �������Դϴ�.
	 *
	 * @param xx ������ x �����Դϴ�.
	 * @param yy ������ y �����Դϴ�.
	 */
	Vec2f(float&& xx, float&& yy) noexcept : x(xx), y(yy) {}


	/**
	 * @brief 2���� ������ �������Դϴ�.
	 *
	 * @param xx ������ x �����Դϴ�.
	 * @param yy ������ y �����Դϴ�.
	 */
	Vec2f(const float& xx, const float& yy) noexcept : x(xx), y(yy) {}


	/**
	 * @brief 2���� ������ ���Ҹ� �ϳ��� ������ �ʱ�ȭ�մϴ�.
	 *
	 * @param e ��� ���Ҹ� �ʱ�ȭ �� ���Դϴ�.
	 */
	Vec2f(float&& e) noexcept : x(e), y(e) {}


	/**
	 * @brief 2���� ������ ���Ҹ� �ϳ��� ������ �ʱ�ȭ�մϴ�.
	 *
	 * @param e ��� ���Ҹ� �ʱ�ȭ �� ���Դϴ�.
	 */
	Vec2f(const float& e) noexcept : x(e), y(e) {}


	/**
	 * @brief 2���� ������ ���� �������Դϴ�.
	 *
	 * @param v ���Ҹ� ������ ���� ����ü�� �ν��Ͻ��Դϴ�.
	 */
	Vec2f(Vec2f&& v) noexcept : x(v.x), y(v.y) {}


	/**
	 * @brief 2���� ������ ���� �������Դϴ�.
	 *
	 * @param v ���Ҹ� ������ ������ �ν��Ͻ��Դϴ�.
	 */
	Vec2f(const Vec2f& v) noexcept : x(v.x), y(v.y) {}


	/**
	 * @brief 2���� ������ ���� ������ �Դϴ�.
	 *
	 * @param v ���Ҹ� ������ ���� ����ü�� �ν��Ͻ��Դϴ�.
	 *
	 * @return ������ ������ �����ڸ� ��ȯ�մϴ�.
	 */
	Vec2f& operator=(Vec2f&& v) noexcept
	{
		if (this == &v) return *this;

		x = v.x;
		y = v.y;

		return *this;
	}


	/**
	 * @brief 2���� ������ ���� ������ �Դϴ�.
	 *
	 * @param v ���Ҹ� ������ ���� ����ü�� �ν��Ͻ��Դϴ�.
	 *
	 * @return ������ ������ �����ڸ� ��ȯ�մϴ�.
	 */
	Vec2f& operator=(const Vec2f& v) noexcept
	{
		if (this == &v) return *this;

		x = v.x;
		y = v.y;

		return *this;
	}


	/**
	 * @brief 2���� ������ ���ҿ� -��ȣ�� ���մϴ�.
	 *
	 * @return 2���� ������ ���ҿ� -��ȣ�� ���� ���ο� ���͸� ��ȯ�մϴ�.
	 */
	Vec2f operator-() const
	{
		return Vec2f(-x, -y);
	}


	/**
	 * @brief �� 2���� ���Ϳ� �����ϴ� ���Ҹ� ���մϴ�.
	 *
	 * @param v ������ ������ ������ �ǿ������Դϴ�.
	 *
	 * @return �� ���Ϳ� �����ϴ� ���Ҹ� ���� ����� ��ȯ�մϴ�.
	 */
	Vec2f operator+(Vec2f&& v) const
	{
		return Vec2f(x + v.x, y + v.y);
	}


	/**
	 * @brief �� 2���� ���Ϳ� �����ϴ� ���Ҹ� ���մϴ�.
	 *
	 * @param v ������ ������ ������ �ǿ������Դϴ�.
	 *
	 * @return �� ���Ϳ� �����ϴ� ���Ҹ� ���� ����� ��ȯ�մϴ�.
	 */
	Vec2f operator+(const Vec2f& v) const
	{
		return Vec2f(x + v.x, y + v.y);
	}


	/**
	 * @brief �� 2���� ���Ϳ� �����ϴ� ���Ҹ� ���ϴ�.
	 *
	 * @param v ������ ������ ������ �ǿ������Դϴ�.
	 *
	 * @return �� ���Ϳ� �����ϴ� ���Ҹ� �� ����� ��ȯ�մϴ�.
	 */
	Vec2f operator-(Vec2f&& v) const
	{
		return Vec2f(x - v.x, y - v.y);
	}


	/**
	 * @brief �� 2���� ���Ϳ� �����ϴ� ���Ҹ� ���ϴ�.
	 *
	 * @param v ������ ������ ������ �ǿ������Դϴ�.
	 *
	 * @return �� ���Ϳ� �����ϴ� ���Ҹ� �� ����� ��ȯ�մϴ�.
	 */
	Vec2f operator-(const Vec2f& v) const
	{
		return Vec2f(x - v.x, y - v.y);
	}


	/**
	 * @brief �� 2���� ���Ϳ� �����ϴ� ���Ҹ� ���� ���մϴ�.
	 *
	 * @note �� ������ ������ ���� ����(Dot Product)�ʹ� �ٸ��ϴ�.
	 *
	 * @param v ������ ������ ������ �ǿ������Դϴ�.
	 *
	 * @return �� ���Ϳ� �����ϴ� ���Ҹ� ���� ����� ��ȯ�մϴ�.
	 */
	Vec2f operator*(Vec2f&& v) const
	{
		return Vec2f(x * v.x, y * v.y);
	}


	/**
	 * @brief �� 2���� ���Ϳ� �����ϴ� ���Ҹ� ���� ���մϴ�.
	 *
	 * @note �� ������ ������ ���� ����(Dot Product)�ʹ� �ٸ��ϴ�.
	 *
	 * @param v ������ ������ ������ �ǿ������Դϴ�.
	 *
	 * @return �� ���Ϳ� �����ϴ� ���Ҹ� ���� ����� ��ȯ�մϴ�.
	 */
	Vec2f operator*(const Vec2f& v) const
	{
		return Vec2f(x * v.x, y * v.y);
	}


	/**
	 * @brief �� 2���� ���Ϳ� �����ϴ� ���Ҹ� ���մϴ�.
	 *
	 * @param v ������ ������ �ǿ������Դϴ�.
	 *
	 * @return ������ ������ ������ �����ڸ� ��ȯ�մϴ�.
	 */
	Vec2f& operator+=(Vec2f&& v) noexcept
	{
		x += v.x;
		y += v.y;

		return *this;
	}


	/**
	 * @brief �� 2���� ���Ϳ� �����ϴ� ���Ҹ� ���մϴ�.
	 *
	 * @param v ������ ������ �ǿ������Դϴ�.
	 *
	 * @return ������ ������ ������ �����ڸ� ��ȯ�մϴ�.
	 */
	Vec2f& operator+=(const Vec2f& v) noexcept
	{
		x += v.x;
		y += v.y;

		return *this;
	}


	/**
	 * @brief �� 2���� ���Ϳ� �����ϴ� ���Ҹ� ���ϴ�.
	 *
	 * @param v ������ ������ �ǿ������Դϴ�.
	 *
	 * @return ������ ������ ������ �����ڸ� ��ȯ�մϴ�.
	 */
	Vec2f& operator-=(Vec2f&& v) noexcept
	{
		x -= v.x;
		y -= v.y;

		return *this;
	}


	/**
	 * @brief �� 2���� ���Ϳ� �����ϴ� ���Ҹ� ���ϴ�.
	 *
	 * @param v ������ ������ �ǿ������Դϴ�.
	 *
	 * @return ������ ������ ������ �����ڸ� ��ȯ�մϴ�.
	 */
	Vec2f& operator-=(const Vec2f& v) noexcept
	{
		x -= v.x;
		y -= v.y;

		return *this;
	}


	/**
	 * @brief �� 2���� ������ �����ϴ� ���Ұ� �������� Ȯ���մϴ�.
	 *
	 * @param v ������ ������ �ǿ������Դϴ�.
	 *
	 * @return �� 2���� ������ �����ϴ� ���Ұ� ��ġ�Ѵٸ� true, �׷��� ������ false�� ��ȯ�մϴ�.
	 */
	bool operator==(Vec2f&& v) noexcept
	{
		return Abs(x - v.x) <= EPSILON && Abs(y - v.y) <= EPSILON;
	}


	/**
	 * @brief �� 2���� ������ �����ϴ� ���Ұ� �������� Ȯ���մϴ�.
	 *
	 * @param v ������ ������ �ǿ������Դϴ�.
	 *
	 * @return �� 2���� ������ �����ϴ� ���Ұ� ��ġ�Ѵٸ� true, �׷��� ������ false�� ��ȯ�մϴ�.
	 */
	bool operator==(const Vec2f& v) noexcept
	{
		return Abs(x - v.x) <= EPSILON && Abs(y - v.y) <= EPSILON;
	}


	/**
	 * @brief �� 2���� ������ �����ϴ� ���Ұ� �������� ������ Ȯ���մϴ�.
	 *
	 * @param v ������ ������ �ǿ������Դϴ�.
	 *
	 * @return �� 2���� ������ �����ϴ� ���Ұ� ��ġ���� �ʴ´ٸ� true, �׷��ٸ� false�� ��ȯ�մϴ�.
	 */
	bool operator!=(Vec2f&& v) noexcept
	{
		return Abs(x - v.x) > EPSILON || Abs(y - v.y) > EPSILON;
	}


	/**
	 * @brief �� 2���� ������ �����ϴ� ���Ұ� �������� ������ Ȯ���մϴ�.
	 *
	 * @param v ������ ������ �ǿ������Դϴ�.
	 *
	 * @return �� 2���� ������ �����ϴ� ���Ұ� ��ġ���� �ʴ´ٸ� true, �׷��ٸ� false�� ��ȯ�մϴ�.
	 */
	bool operator!=(const Vec2f& v) noexcept
	{
		return Abs(x - v.x) > EPSILON || Abs(y - v.y) > EPSILON;
	}


	/**
	 * @brief 2���� ���� ���� �迭�� �����͸� ����ϴ�.
	 *
	 * @return 2���� ���� ���� �迭�� �����͸� ��ȯ�մϴ�.
	 */
	const float* GetPtr() const { return &data[0]; }


	/**
	 * @brief 2���� ���� ���� �迭�� �����͸� ����ϴ�.
	 *
	 * @return 2���� ���� ���� �迭�� �����͸� ��ȯ�մϴ�.
	 */
	float* GetPtr() { return &data[0]; }


	/**
	 * @brief 2���� ������ ���� ������ �����մϴ�.
	 *
	 * @param lhs ������ ���� ������ ������ ���� �ǿ������Դϴ�.
	 * @param rhs ������ ���� ������ ������ ���� �ǿ������Դϴ�.
	 *
	 * @return ���� ���� ����� ��ȯ�մϴ�.
	 */
	static inline float Dot(const Vec2f& lhs, const Vec2f& rhs)
	{
		return lhs.x * rhs.x + lhs.y * rhs.y;
	}


	/**
	 * @brief 2���� ������ ���� ������ �����մϴ�.
	 *
	 * @param lhs ������ ���� ������ ������ ���� �ǿ������Դϴ�.
	 * @param rhs ������ ���� ������ ������ ���� �ǿ������Դϴ�.
	 *
	 * @return ���� ���� ����� ��ȯ�մϴ�.
	 *
	 * @note �Ϲ����� 3���� ���� ����� �ٸ��ϴ�.
	 */
	static inline float Cross(const Vec2f& lhs, const Vec2f& rhs)
	{
		return lhs.x * rhs.y - lhs.y * rhs.x;
	}


	/**
	 * @brief 2���� ������ ũ�� ���� ���� ����մϴ�.
	 *
	 * @param v ũ�� ������ ����� �����Դϴ�.
	 *
	 * @return ���� ũ�� ���� ���� ��ȯ�մϴ�.
	 */
	static inline float LengthSq(const Vec2f& v)
	{
		return v.x * v.x + v.y * v.y;
	}


	/**
	 * @brief 2���� ������ ũ�⸦ ����ϴ�.
	 *
	 * @param v ũ�⸦ ����� �����Դϴ�.
	 *
	 * @return ���� ũ�� ���� ��ȯ�մϴ�.
	 */
	static inline float Length(const Vec2f& v)
	{
		float lengthSq = LengthSq(v);
		return Sqrt(lengthSq);
	}


	/**
	 * @brief 2���� ���͸� ����ȭ�մϴ�.
	 *
	 * @param v ����ȭ �� �����Դϴ�.
	 *
	 * @return ����ȭ�� ���͸� ��ȯ�մϴ�.
	 */
	static inline Vec2f Normalize(const Vec2f& v)
	{
		float length = Length(v);

		if (NearZero(length))
		{
			return v;
		}

		float invLength = 1.0f / length;
		return Vec2f(v.x * invLength, v.y * invLength);
	}


	/**
	 * @brief �� 2���� ���� ������ ���� ����մϴ�.
	 *
	 * @param lhs ���� ������ ���� ����� ���� �ǿ����� �����Դϴ�.
	 * @param rhs ���� ������ ���� ����� ������ �ǿ����� �����Դϴ�.
	 *
	 * @return �� 2���� ���� ������ ���� ������ ��ȯ�մϴ�.
	 */
	static inline float Radian(const Vec2f& lhs, const Vec2f& rhs)
	{
		float lengthL = Length(lhs);
		float lengthR = Length(rhs);
		float dot = Dot(lhs, rhs);

		return ACos(dot / (lengthL * lengthR));
	}


	/**
	 * @brief �� 2���� ���� ������ ���� ����մϴ�.
	 *
	 * @param lhs ���� ������ ���� ����� ���� �ǿ����� �����Դϴ�.
	 * @param rhs ���� ������ ���� ����� ������ �ǿ����� �����Դϴ�.
	 *
	 * @return �� 2���� ���� ������ ���ʺй� ������ ��ȯ�մϴ�.
	 */
	static inline float Degree(const Vec2f& lhs, const Vec2f& rhs)
	{
		float radian = Radian(lhs, rhs);
		return ToDegree(radian);
	}


	/**
	 * @brief Base 2���� ���Ϳ� Target 2���� ���͸� �����մϴ�.
	 *
	 * @param target ���� ��� ������ �����Դϴ�.
	 * @param base ���� ����� �Ǵ� �����Դϴ�.
	 *
	 * @return base�� ������ target ���͸� ��ȯ�մϴ�.
	 */
	static inline Vec2f Project(const Vec2f& target, const Vec2f& base)
	{
		float dot = Dot(target, base);
		float lengthSq = LengthSq(base);
		float scale = dot / lengthSq;

		return Vec2f(base.x * scale, base.y * scale);
	}


	/**
	 * @brief Base 2���� ���Ϳ� Target 2���� ���͸� ������ ���Ϳ� ������ ���͸� ����մϴ�.
	 *
	 * @param target ���� ��� ������ �����Դϴ�.
	 * @param base ���� ����� �Ǵ� �����Դϴ�.
	 *
	 * @return ������ ������ ������ ���͸� ��ȯ�մϴ�.
	 */
	static inline Vec2f Reject(const Vec2f& target, const Vec2f& base)
	{
		Vec2f project = Project(target, base);
		return target - project;
	}


	/**
	 * @brief �� ���͸� ���� ������ ���͸� ����մϴ�.
	 *
	 * @param s ������ ���� �����Դϴ�.
	 * @param e ������ �� �����Դϴ�.
	 * @param t �� ������ ���� �����Դϴ�.
	 *
	 * @return ������ ���͸� ��ȯ�մϴ�.
	 */
	static inline Vec2f Lerp(const Vec2f& s, const Vec2f& e, const float& t)
	{
		return s * (1.0f - t) + e * t;
	}


	/**
	 * @brief �� ���͸� ���� ���� ������ ���͸� ����մϴ�.
	 *
	 * @param s ������ ���� �����Դϴ�.
	 * @param e ������ �� �����Դϴ�.
	 * @param t �� ������ ���� �����Դϴ�.
	 *
	 * @return ������ ���͸� ��ȯ�մϴ�.
	 */
	static inline Vec2f Slerp(const Vec2f& s, const Vec2f& e, const float& t)
	{
		Vec2f start = Normalize(s);
		Vec2f end = Normalize(e);

		float theta = Radian(start, end);
		float sinTheta = Sin(theta);

		float a = Sin((1.0f - t) * theta) / sinTheta;
		float b = Sin(t * theta) / sinTheta;

		return s * a + e * b;
	}


	/**
	 * @brief 2���� ������ �پ��� ���� �����Դϴ�.
	 */
	union
	{
		struct
		{
			float x;
			float y;
		};
		float data[2];
	};
};


/**
 * @brief ������ ������ Ÿ���� ������ 3���� �����Դϴ�.
 */
struct Vec3i
{
	/**
	 * @brief 3���� ������ �⺻ �������Դϴ�.
	 *
	 * @note ��� ������ ���� 0���� �ʱ�ȭ�մϴ�.
	 */
	Vec3i() noexcept : x(0), y(0), z(0) {}


	/**
	 * @brief 3���� ������ �������Դϴ�.
	 *
	 * @param xx ������ x �����Դϴ�.
	 * @param yy ������ y �����Դϴ�.
	 * @param zz ������ z �����Դϴ�.
	 */
	Vec3i(int32_t&& xx, int32_t&& yy, int32_t&& zz) noexcept : x(xx), y(yy), z(zz) {}


	/**
	 * @brief 3���� ������ �������Դϴ�.
	 *
	 * @param xx ������ x �����Դϴ�.
	 * @param yy ������ y �����Դϴ�.
	 * @param zz ������ z �����Դϴ�.
	 */
	Vec3i(const int32_t& xx, const int32_t& yy, const int32_t& zz) noexcept : x(xx), y(yy), z(zz) {}


	/**
	 * @brief 3���� ������ ���Ҹ� �ϳ��� ������ �ʱ�ȭ�մϴ�.
	 *
	 * @param e ��� ���Ҹ� �ʱ�ȭ �� ���Դϴ�.
	 */
	Vec3i(int32_t&& e) noexcept : x(e), y(e), z(e) {}


	/**
	 * @brief 3���� ������ ���Ҹ� �ϳ��� ������ �ʱ�ȭ�մϴ�.
	 *
	 * @param e ��� ���Ҹ� �ʱ�ȭ �� ���Դϴ�.
	 */
	Vec3i(const int32_t& e) noexcept : x(e), y(e), z(e) {}


	/**
	 * @brief 3���� ������ ���� �������Դϴ�.
	 *
	 * @param v ���Ҹ� ������ ���� ����ü�� �ν��Ͻ��Դϴ�.
	 */
	Vec3i(Vec3i&& v) noexcept : x(v.x), y(v.y), z(v.z) {}


	/**
	 * @brief 3���� ������ ���� �������Դϴ�.
	 *
	 * @param v ���Ҹ� ������ ������ �ν��Ͻ��Դϴ�.
	 */
	Vec3i(const Vec3i& v) noexcept : x(v.x), y(v.y), z(v.z) {}


	/**
	 * @brief 3���� ������ ���� ������ �Դϴ�.
	 *
	 * @param v ���Ҹ� ������ ���� ����ü�� �ν��Ͻ��Դϴ�.
	 *
	 * @return ������ ������ �����ڸ� ��ȯ�մϴ�.
	 */
	Vec3i& operator=(Vec3i&& v) noexcept
	{
		if (this == &v) return *this;

		x = v.x;
		y = v.y;
		z = v.z;

		return *this;
	}


	/**
	 * @brief 3���� ������ ���� ������ �Դϴ�.
	 *
	 * @param v ���Ҹ� ������ ���� ����ü�� �ν��Ͻ��Դϴ�.
	 *
	 * @return ������ ������ �����ڸ� ��ȯ�մϴ�.
	 */
	Vec3i& operator=(const Vec3i& v) noexcept
	{
		if (this == &v) return *this;

		x = v.x;
		y = v.y;
		z = v.z;

		return *this;
	}


	/**
	 * @brief 3���� ������ ���ҿ� -��ȣ�� ���մϴ�.
	 *
	 * @return 3���� ������ ���ҿ� -��ȣ�� ���� ���ο� ���͸� ��ȯ�մϴ�.
	 */
	Vec3i operator-() const
	{
		return Vec3i(-x, -y, -z);
	}


	/**
	 * @brief �� 3���� ���Ϳ� �����ϴ� ���Ҹ� ���մϴ�.
	 *
	 * @param v ������ ������ ������ �ǿ������Դϴ�.
	 *
	 * @return �� ���Ϳ� �����ϴ� ���Ҹ� ���� ����� ��ȯ�մϴ�.
	 */
	Vec3i operator+(Vec3i&& v) const
	{
		return Vec3i(x + v.x, y + v.y, z + v.z);
	}


	/**
	 * @brief �� 3���� ���Ϳ� �����ϴ� ���Ҹ� ���մϴ�.
	 *
	 * @param v ������ ������ ������ �ǿ������Դϴ�.
	 *
	 * @return �� ���Ϳ� �����ϴ� ���Ҹ� ���� ����� ��ȯ�մϴ�.
	 */
	Vec3i operator+(const Vec3i& v) const
	{
		return Vec3i(x + v.x, y + v.y, z + v.z);
	}


	/**
	 * @brief �� 3���� ���Ϳ� �����ϴ� ���Ҹ� ���ϴ�.
	 *
	 * @param v ������ ������ ������ �ǿ������Դϴ�.
	 *
	 * @return �� ���Ϳ� �����ϴ� ���Ҹ� �� ����� ��ȯ�մϴ�.
	 */
	Vec3i operator-(Vec3i&& v) const
	{
		return Vec3i(x - v.x, y - v.y, z - v.z);
	}


	/**
	 * @brief �� 3���� ���Ϳ� �����ϴ� ���Ҹ� ���ϴ�.
	 *
	 * @param v ������ ������ ������ �ǿ������Դϴ�.
	 *
	 * @return �� ���Ϳ� �����ϴ� ���Ҹ� �� ����� ��ȯ�մϴ�.
	 */
	Vec3i operator-(const Vec3i& v) const
	{
		return Vec3i(x - v.x, y - v.y, z - v.z);
	}


	/**
	 * @brief �� 3���� ���Ϳ� �����ϴ� ���Ҹ� ���� ���մϴ�.
	 *
	 * @note �� ������ ������ ���� ����(Dot Product)�ʹ� �ٸ��ϴ�.
	 *
	 * @param v ������ ������ ������ �ǿ������Դϴ�.
	 *
	 * @return �� ���Ϳ� �����ϴ� ���Ҹ� ���� ����� ��ȯ�մϴ�.
	 */
	Vec3i operator*(Vec3i&& v) const
	{
		return Vec3i(x * v.x, y * v.y, z * v.z);
	}


	/**
	 * @brief �� 3���� ���Ϳ� �����ϴ� ���Ҹ� ���� ���մϴ�.
	 *
	 * @note �� ������ ������ ���� ����(Dot Product)�ʹ� �ٸ��ϴ�.
	 *
	 * @param v ������ ������ ������ �ǿ������Դϴ�.
	 *
	 * @return �� ���Ϳ� �����ϴ� ���Ҹ� ���� ����� ��ȯ�մϴ�.
	 */
	Vec3i operator*(const Vec3i& v) const
	{
		return Vec3i(x * v.x, y * v.y, z * v.z);
	}


	/**
	 * @brief �� 3���� ���Ϳ� �����ϴ� ���Ҹ� ���մϴ�.
	 *
	 * @param v ������ ������ �ǿ������Դϴ�.
	 *
	 * @return ������ ������ ������ �����ڸ� ��ȯ�մϴ�.
	 */
	Vec3i& operator+=(Vec3i&& v) noexcept
	{
		x += v.x;
		y += v.y;
		z += v.z;

		return *this;
	}


	/**
	 * @brief �� 3���� ���Ϳ� �����ϴ� ���Ҹ� ���մϴ�.
	 *
	 * @param v ������ ������ �ǿ������Դϴ�.
	 *
	 * @return ������ ������ ������ �����ڸ� ��ȯ�մϴ�.
	 */
	Vec3i& operator+=(const Vec3i& v) noexcept
	{
		x += v.x;
		y += v.y;
		z += v.z;

		return *this;
	}


	/**
	 * @brief �� 3���� ���Ϳ� �����ϴ� ���Ҹ� ���ϴ�.
	 *
	 * @param v ������ ������ �ǿ������Դϴ�.
	 *
	 * @return ������ ������ ������ �����ڸ� ��ȯ�մϴ�.
	 */
	Vec3i& operator-=(Vec3i&& v) noexcept
	{
		x -= v.x;
		y -= v.y;
		z -= v.z;

		return *this;
	}


	/**
	 * @brief �� 3���� ���Ϳ� �����ϴ� ���Ҹ� ���ϴ�.
	 *
	 * @param v ������ ������ �ǿ������Դϴ�.
	 *
	 * @return ������ ������ ������ �����ڸ� ��ȯ�մϴ�.
	 */
	Vec3i& operator-=(const Vec3i& v) noexcept
	{
		x -= v.x;
		y -= v.y;
		z -= v.z;

		return *this;
	}


	/**
	 * @brief �� 3���� ���Ͱ� �������� �˻��մϴ�.
	 *
	 * @param v �˻縦 ������ �ǿ������Դϴ�.
	 *
	 * @return �� ���Ͱ� �����ϴٸ� true, �׷��� ������ false�� ��ȯ�մϴ�.
	 */
	bool operator==(Vec3i&& v) const
	{
		return (x == v.x) && (y == v.y) && (z == v.z);
	}


	/**
	 * @brief �� 3���� ���Ͱ� �������� �˻��մϴ�.
	 *
	 * @param v �˻縦 ������ �ǿ������Դϴ�.
	 *
	 * @return �� ���Ͱ� �����ϴٸ� true, �׷��� ������ false�� ��ȯ�մϴ�.
	 */
	bool operator==(const Vec3i& v) const
	{
		return (x == v.x) && (y == v.y) && (z == v.z);
	}


	/**
	 * @brief �� 3���� ���Ͱ� �������� ������ �˻��մϴ�.
	 *
	 * @param v �˻縦 ������ �ǿ������Դϴ�.
	 *
	 * @return �� ���Ͱ� �������� �ʴٸ� true, �׷��ٸ� false�� ��ȯ�մϴ�.
	 */
	bool operator!=(Vec3i&& v) const
	{
		return (x != v.x) || (y != v.y) || (z != v.z);
	}


	/**
	 * @brief �� 3���� ���Ͱ� �������� ������ �˻��մϴ�.
	 *
	 * @param v �˻縦 ������ �ǿ������Դϴ�.
	 *
	 * @return �� ���Ͱ� �������� �ʴٸ� true, �׷��ٸ� false�� ��ȯ�մϴ�.
	 */
	bool operator!=(const Vec3i& v) const
	{
		return (x != v.x) || (y != v.y) || (z != v.z);
	}


	/**
	 * @brief 3���� ���� ���� �迭�� �����͸� ����ϴ�.
	 *
	 * @return 3���� ���� ���� �迭�� �����͸� ��ȯ�մϴ�.
	 */
	const int32_t* GetPtr() const { return &data[0]; }


	/**
	 * @brief 3���� ���� ���� �迭�� �����͸� ����ϴ�.
	 *
	 * @return 3���� ���� ���� �迭�� �����͸� ��ȯ�մϴ�.
	 */
	int32_t* GetPtr() { return &data[0]; }


	/**
	 * @brief 3���� ������ ���� ������ �����մϴ�.
	 *
	 * @param lhs ������ ���� ������ ������ ���� �ǿ������Դϴ�.
	 * @param rhs ������ ���� ������ ������ ���� �ǿ������Դϴ�.
	 *
	 * @return ���� ���� ����� ��ȯ�մϴ�.
	 */
	static inline int32_t Dot(const Vec3i& lhs, const Vec3i& rhs)
	{
		return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z;
	}


	/**
	 * @brief 3���� ������ ���� ������ �����մϴ�.
	 *
	 * @param lhs ������ ���� ������ ������ ���� �ǿ������Դϴ�.
	 * @param rhs ������ ���� ������ ������ ���� �ǿ������Դϴ�.
	 *
	 * @return ���� ���� ����� ��ȯ�մϴ�.
	 */
	static inline Vec3i Cross(const Vec3i& lhs, const Vec3i& rhs)
	{
		return Vec3i(
			lhs.y * rhs.z - lhs.z * rhs.y,
			lhs.z * rhs.x - lhs.x * rhs.z,
			lhs.x * rhs.y - lhs.y * rhs.x
		);
	}


	/**
	 * @brief 3���� ������ ũ�� ���� ���� ����մϴ�.
	 *
	 * @param v ũ�� ������ ����� �����Դϴ�.
	 *
	 * @return ���� ũ�� ���� ���� ��ȯ�մϴ�.
	 */
	static inline int32_t LengthSq(const Vec3i& v)
	{
		return v.x * v.x + v.y * v.y + v.z * v.z;
	}


	/**
	 * @brief 3���� ������ ũ�⸦ ����ϴ�.
	 *
	 * @param v ũ�⸦ ����� �����Դϴ�.
	 *
	 * @return ���� ũ�� ���� ��ȯ�մϴ�.
	 */
	static inline float Length(const Vec3i& v)
	{
		float lengthSq = static_cast<float>(LengthSq(v));
		return Sqrt(lengthSq);
	}


	/**
	 * @brief �� 3���� ���� ������ ���� ����մϴ�.
	 *
	 * @param lhs ���� ������ ���� ����� ���� �ǿ����� �����Դϴ�.
	 * @param rhs ���� ������ ���� ����� ������ �ǿ����� �����Դϴ�.
	 *
	 * @return �� 3���� ���� ������ ���� ������ ��ȯ�մϴ�.
	 */
	static inline float Radian(const Vec3i& lhs, const Vec3i& rhs)
	{
		float lengthL = Length(lhs);
		float lengthR = Length(rhs);
		float dot = Dot(lhs, rhs);

		return ACos(dot / (lengthL * lengthR));
	}


	/**
	 * @brief �� 3���� ���� ������ ���� ����մϴ�.
	 *
	 * @param lhs ���� ������ ���� ����� ���� �ǿ����� �����Դϴ�.
	 * @param rhs ���� ������ ���� ����� ������ �ǿ����� �����Դϴ�.
	 *
	 * @return �� 3���� ���� ������ ���ʺй� ������ ��ȯ�մϴ�.
	 */
	static inline float Degree(const Vec3i& lhs, const Vec3i& rhs)
	{
		float radian = Radian(lhs, rhs);
		return ToDegree(radian);
	}


	/**
	 * @brief 3���� ������ �پ��� ���� �����Դϴ�.
	 */
	union
	{
		struct
		{
			int32_t x;
			int32_t y;
			int32_t z;
		};
		int32_t data[3];
	};
};


/**
 * @brief ������ ������ Ÿ���� �ε� �Ҽ����� 3���� �����Դϴ�.
 */
struct Vec3f
{
	/**
	 * @brief 3���� ������ �⺻ �������Դϴ�.
	 *
	 * @note ��� ������ ���� 0���� �ʱ�ȭ�մϴ�.
	 */
	Vec3f() noexcept : x(0.0f), y(0.0f), z(0.0f) {}


	/**
	 * @brief 3���� ������ �������Դϴ�.
	 *
	 * @param xx ������ x �����Դϴ�.
	 * @param yy ������ y �����Դϴ�.
	 * @param zz ������ z �����Դϴ�.
	 */
	Vec3f(float&& xx, float&& yy, float&& zz) noexcept : x(xx), y(yy), z(zz) {}


	/**
	 * @brief 3���� ������ �������Դϴ�.
	 *
	 * @param xx ������ x �����Դϴ�.
	 * @param yy ������ y �����Դϴ�.
	 * @param zz ������ z �����Դϴ�.
	 */
	Vec3f(const float& xx, const float& yy, const float& zz) noexcept : x(xx), y(yy), z(zz) {}


	/**
	 * @brief 3���� ������ ���Ҹ� �ϳ��� ������ �ʱ�ȭ�մϴ�.
	 *
	 * @param e ��� ���Ҹ� �ʱ�ȭ �� ���Դϴ�.
	 */
	Vec3f(float&& e) noexcept : x(e), y(e), z(e) {}


	/**
	 * @brief 3���� ������ ���Ҹ� �ϳ��� ������ �ʱ�ȭ�մϴ�.
	 *
	 * @param e ��� ���Ҹ� �ʱ�ȭ �� ���Դϴ�.
	 */
	Vec3f(const float& e) noexcept : x(e), y(e), z(e) {}


	/**
	 * @brief 3���� ������ ���� �������Դϴ�.
	 *
	 * @param v ���Ҹ� ������ ���� ����ü�� �ν��Ͻ��Դϴ�.
	 */
	Vec3f(Vec3f&& v) noexcept : x(v.x), y(v.y), z(v.z) {}


	/**
	 * @brief 3���� ������ ���� �������Դϴ�.
	 *
	 * @param v ���Ҹ� ������ ������ �ν��Ͻ��Դϴ�.
	 */
	Vec3f(const Vec3f& v) noexcept : x(v.x), y(v.y), z(v.z) {}


	/**
	 * @brief 3���� ������ ���� ������ �Դϴ�.
	 *
	 * @param v ���Ҹ� ������ ���� ����ü�� �ν��Ͻ��Դϴ�.
	 *
	 * @return ������ ������ �����ڸ� ��ȯ�մϴ�.
	 */
	Vec3f& operator=(Vec3f&& v) noexcept
	{
		if (this == &v) return *this;

		x = v.x;
		y = v.y;
		z = v.z;

		return *this;
	}


	/**
	 * @brief 3���� ������ ���� ������ �Դϴ�.
	 *
	 * @param v ���Ҹ� ������ ���� ����ü�� �ν��Ͻ��Դϴ�.
	 *
	 * @return ������ ������ �����ڸ� ��ȯ�մϴ�.
	 */
	Vec3f& operator=(const Vec3f& v) noexcept
	{
		if (this == &v) return *this;

		x = v.x;
		y = v.y;
		z = v.z;

		return *this;
	}


	/**
	 * @brief 3���� ������ ���ҿ� -��ȣ�� ���մϴ�.
	 *
	 * @return 3���� ������ ���ҿ� -��ȣ�� ���� ���ο� ���͸� ��ȯ�մϴ�.
	 */
	Vec3f operator-() const
	{
		return Vec3f(-x, -y, -z);
	}


	/**
	 * @brief �� 3���� ���Ϳ� �����ϴ� ���Ҹ� ���մϴ�.
	 *
	 * @param v ������ ������ ������ �ǿ������Դϴ�.
	 *
	 * @return �� ���Ϳ� �����ϴ� ���Ҹ� ���� ����� ��ȯ�մϴ�.
	 */
	Vec3f operator+(Vec3f&& v) const
	{
		return Vec3f(x + v.x, y + v.y, z + v.z);
	}


	/**
	 * @brief �� 3���� ���Ϳ� �����ϴ� ���Ҹ� ���մϴ�.
	 *
	 * @param v ������ ������ ������ �ǿ������Դϴ�.
	 *
	 * @return �� ���Ϳ� �����ϴ� ���Ҹ� ���� ����� ��ȯ�մϴ�.
	 */
	Vec3f operator+(const Vec3f& v) const
	{
		return Vec3f(x + v.x, y + v.y, z + v.z);
	}


	/**
	 * @brief �� 3���� ���Ϳ� �����ϴ� ���Ҹ� ���ϴ�.
	 *
	 * @param v ������ ������ ������ �ǿ������Դϴ�.
	 *
	 * @return �� ���Ϳ� �����ϴ� ���Ҹ� �� ����� ��ȯ�մϴ�.
	 */
	Vec3f operator-(Vec3f&& v) const
	{
		return Vec3f(x - v.x, y - v.y, z - v.z);
	}


	/**
	 * @brief �� 3���� ���Ϳ� �����ϴ� ���Ҹ� ���ϴ�.
	 *
	 * @param v ������ ������ ������ �ǿ������Դϴ�.
	 *
	 * @return �� ���Ϳ� �����ϴ� ���Ҹ� �� ����� ��ȯ�մϴ�.
	 */
	Vec3f operator-(const Vec3f& v) const
	{
		return Vec3f(x - v.x, y - v.y, z - v.z);
	}


	/**
	 * @brief �� 3���� ���Ϳ� �����ϴ� ���Ҹ� ���� ���մϴ�.
	 *
	 * @note �� ������ ������ ���� ����(Dot Product)�ʹ� �ٸ��ϴ�.
	 *
	 * @param v ������ ������ ������ �ǿ������Դϴ�.
	 *
	 * @return �� ���Ϳ� �����ϴ� ���Ҹ� ���� ����� ��ȯ�մϴ�.
	 */
	Vec3f operator*(Vec3f&& v) const
	{
		return Vec3f(x * v.x, y * v.y, z * v.z);
	}


	/**
	 * @brief �� 3���� ���Ϳ� �����ϴ� ���Ҹ� ���� ���մϴ�.
	 *
	 * @note �� ������ ������ ���� ����(Dot Product)�ʹ� �ٸ��ϴ�.
	 *
	 * @param v ������ ������ ������ �ǿ������Դϴ�.
	 *
	 * @return �� ���Ϳ� �����ϴ� ���Ҹ� ���� ����� ��ȯ�մϴ�.
	 */
	Vec3f operator*(const Vec3f& v) const
	{
		return Vec3f(x * v.x, y * v.y, z * v.z);
	}


	/**
	 * @brief �� 3���� ���Ϳ� �����ϴ� ���Ҹ� ���մϴ�.
	 *
	 * @param v ������ ������ �ǿ������Դϴ�.
	 *
	 * @return ������ ������ ������ �����ڸ� ��ȯ�մϴ�.
	 */
	Vec3f& operator+=(Vec3f&& v) noexcept
	{
		x += v.x;
		y += v.y;
		z += v.z;

		return *this;
	}


	/**
	 * @brief �� 3���� ���Ϳ� �����ϴ� ���Ҹ� ���մϴ�.
	 *
	 * @param v ������ ������ �ǿ������Դϴ�.
	 *
	 * @return ������ ������ ������ �����ڸ� ��ȯ�մϴ�.
	 */
	Vec3f& operator+=(const Vec3f& v) noexcept
	{
		x += v.x;
		y += v.y;
		z += v.z;

		return *this;
	}


	/**
	 * @brief �� 3���� ���Ϳ� �����ϴ� ���Ҹ� ���ϴ�.
	 *
	 * @param v ������ ������ �ǿ������Դϴ�.
	 *
	 * @return ������ ������ ������ �����ڸ� ��ȯ�մϴ�.
	 */
	Vec3f& operator-=(Vec3f&& v) noexcept
	{
		x -= v.x;
		y -= v.y;
		z -= v.z;

		return *this;
	}


	/**
	 * @brief �� 3���� ���Ϳ� �����ϴ� ���Ҹ� ���ϴ�.
	 *
	 * @param v ������ ������ �ǿ������Դϴ�.
	 *
	 * @return ������ ������ ������ �����ڸ� ��ȯ�մϴ�.
	 */
	Vec3f& operator-=(const Vec3f& v) noexcept
	{
		x -= v.x;
		y -= v.y;
		z -= v.z;

		return *this;
	}


	/**
	 * @brief �� 3���� ���Ͱ� �������� �˻��մϴ�.
	 *
	 * @param v �˻縦 ������ �ǿ������Դϴ�.
	 *
	 * @return �� ���Ͱ� �����ϴٸ� true, �׷��� ������ false�� ��ȯ�մϴ�.
	 */
	bool operator==(Vec3f&& v) const
	{
		return Abs(x - v.x) <= EPSILON && Abs(y - v.y) <= EPSILON && Abs(z - v.z) <= EPSILON;
	}


	/**
	 * @brief �� 3���� ���Ͱ� �������� �˻��մϴ�.
	 *
	 * @param v �˻縦 ������ �ǿ������Դϴ�.
	 *
	 * @return �� ���Ͱ� �����ϴٸ� true, �׷��� ������ false�� ��ȯ�մϴ�.
	 */
	bool operator==(const Vec3f& v) const
	{
		return Abs(x - v.x) <= EPSILON && Abs(y - v.y) <= EPSILON && Abs(z - v.z) <= EPSILON;
	}


	/**
	 * @brief �� 3���� ���Ͱ� �������� ������ �˻��մϴ�.
	 *
	 * @param v �˻縦 ������ �ǿ������Դϴ�.
	 *
	 * @return �� ���Ͱ� �������� �ʴٸ� true, �׷��ٸ� false�� ��ȯ�մϴ�.
	 */
	bool operator!=(Vec3f&& v) const
	{
		return Abs(x - v.x) > EPSILON || Abs(y - v.y) > EPSILON || Abs(z - v.z) > EPSILON;
	}


	/**
	 * @brief �� 3���� ���Ͱ� �������� ������ �˻��մϴ�.
	 *
	 * @param v �˻縦 ������ �ǿ������Դϴ�.
	 *
	 * @return �� ���Ͱ� �������� �ʴٸ� true, �׷��ٸ� false�� ��ȯ�մϴ�.
	 */
	bool operator!=(const Vec3f& v) const
	{
		return Abs(x - v.x) > EPSILON || Abs(y - v.y) > EPSILON || Abs(z - v.z) > EPSILON;
	}


	/**
	 * @brief 3���� ���� ���� �迭�� �����͸� ����ϴ�.
	 *
	 * @return 3���� ���� ���� �迭�� �����͸� ��ȯ�մϴ�.
	 */
	const float* GetPtr() const { return &data[0]; }


	/**
	 * @brief 3���� ���� ���� �迭�� �����͸� ����ϴ�.
	 *
	 * @return 3���� ���� ���� �迭�� �����͸� ��ȯ�մϴ�.
	 */
	float* GetPtr() { return &data[0]; }


	/**
	 * @brief 3���� ������ ���� ������ �����մϴ�.
	 *
	 * @param lhs ������ ���� ������ ������ ���� �ǿ������Դϴ�.
	 * @param rhs ������ ���� ������ ������ ���� �ǿ������Դϴ�.
	 *
	 * @return ���� ���� ����� ��ȯ�մϴ�.
	 */
	static inline float Dot(const Vec3f& lhs, const Vec3f& rhs)
	{
		return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z;
	}


	/**
	 * @brief 3���� ������ ���� ������ �����մϴ�.
	 *
	 * @param lhs ������ ���� ������ ������ ���� �ǿ������Դϴ�.
	 * @param rhs ������ ���� ������ ������ ���� �ǿ������Դϴ�.
	 *
	 * @return ���� ���� ����� ��ȯ�մϴ�.
	 */
	static inline Vec3f Cross(const Vec3f& lhs, const Vec3f& rhs)
	{
		return Vec3f(
			lhs.y * rhs.z - lhs.z * rhs.y,
			lhs.z * rhs.x - lhs.x * rhs.z,
			lhs.x * rhs.y - lhs.y * rhs.x
		);
	}


	/**
	 * @brief 3���� ������ ũ�� ���� ���� ����մϴ�.
	 *
	 * @param v ũ�� ������ ����� �����Դϴ�.
	 *
	 * @return ���� ũ�� ���� ���� ��ȯ�մϴ�.
	 */
	static inline float LengthSq(const Vec3f& v)
	{
		return v.x * v.x + v.y * v.y + v.z * v.z;
	}


	/**
	 * @brief 3���� ������ ũ�⸦ ����ϴ�.
	 *
	 * @param v ũ�⸦ ����� �����Դϴ�.
	 *
	 * @return ���� ũ�� ���� ��ȯ�մϴ�.
	 */
	static inline float Length(const Vec3f& v)
	{
		float lengthSq = LengthSq(v);
		return Sqrt(lengthSq);
	}


	/**
	 * @brief 3���� ���͸� ����ȭ�մϴ�.
	 *
	 * @param v ����ȭ �� �����Դϴ�.
	 *
	 * @return ����ȭ�� ���͸� ��ȯ�մϴ�.
	 */
	static inline Vec3f Normalize(const Vec3f& v)
	{
		float length = Length(v);

		if (NearZero(length))
		{
			return v;
		}

		float invLength = 1.0f / length;
		return Vec3f(v.x * invLength, v.y * invLength, v.z * invLength);
	}


	/**
	 * @brief �� 3���� ���� ������ ���� ����մϴ�.
	 *
	 * @param lhs ���� ������ ���� ����� ���� �ǿ����� �����Դϴ�.
	 * @param rhs ���� ������ ���� ����� ������ �ǿ����� �����Դϴ�.
	 *
	 * @return �� 3���� ���� ������ ���� ������ ��ȯ�մϴ�.
	 */
	static inline float Radian(const Vec3f& lhs, const Vec3f& rhs)
	{
		float lengthL = Length(lhs);
		float lengthR = Length(rhs);
		float dot = Dot(lhs, rhs);

		return ACos(dot / (lengthL * lengthR));
	}


	/**
	 * @brief �� 3���� ���� ������ ���� ����մϴ�.
	 *
	 * @param lhs ���� ������ ���� ����� ���� �ǿ����� �����Դϴ�.
	 * @param rhs ���� ������ ���� ����� ������ �ǿ����� �����Դϴ�.
	 *
	 * @return �� 3���� ���� ������ ���ʺй� ������ ��ȯ�մϴ�.
	 */
	static inline float Degree(const Vec3f& lhs, const Vec3f& rhs)
	{
		float radian = Radian(lhs, rhs);
		return ToDegree(radian);
	}


	/**
	 * @brief Base 3���� ���Ϳ� Target 3���� ���͸� �����մϴ�.
	 *
	 * @param target ���� ��� ������ �����Դϴ�.
	 * @param base ���� ����� �Ǵ� �����Դϴ�.
	 *
	 * @return base�� ������ target ���͸� ��ȯ�մϴ�.
	 */
	static inline Vec3f Project(const Vec3f& target, const Vec3f& base)
	{
		float dot = Dot(target, base);
		float lengthSq = LengthSq(base);
		float scale = dot / lengthSq;

		return Vec3f(base.x * scale, base.y * scale, base.z * scale);
	}


	/**
	 * @brief Base 3���� ���Ϳ� Target 3���� ���͸� ������ ���Ϳ� ������ ���͸� ����մϴ�.
	 *
	 * @param target ���� ��� ������ �����Դϴ�.
	 * @param base ���� ����� �Ǵ� �����Դϴ�.
	 *
	 * @return ������ ������ ������ ���͸� ��ȯ�մϴ�.
	 */
	static inline Vec3f Reject(const Vec3f& target, const Vec3f& base)
	{
		Vec3f project = Project(target, base);
		return target - project;
	}


	/**
	 * @brief �� ���͸� ���� ������ ���͸� ����մϴ�.
	 *
	 * @param s ������ ���� �����Դϴ�.
	 * @param e ������ �� �����Դϴ�.
	 * @param t �� ������ ���� �����Դϴ�.
	 *
	 * @return ������ ���͸� ��ȯ�մϴ�.
	 */
	static inline Vec3f Lerp(const Vec3f& s, const Vec3f& e, const float& t)
	{
		return s * (1.0f - t) + e * t;
	}


	/**
	 * @brief �� ���͸� ���� ���� ������ ���͸� ����մϴ�.
	 *
	 * @param s ������ ���� �����Դϴ�.
	 * @param e ������ �� �����Դϴ�.
	 * @param t �� ������ ���� �����Դϴ�.
	 *
	 * @return ������ ���͸� ��ȯ�մϴ�.
	 */
	static inline Vec3f Slerp(const Vec3f& s, const Vec3f& e, const float& t)
	{
		Vec3f start = Normalize(s);
		Vec3f end = Normalize(e);

		float theta = Radian(start, end);
		float sinTheta = Sin(theta);

		float a = Sin((1.0f - t) * theta) / sinTheta;
		float b = Sin(t * theta) / sinTheta;

		return s * a + e * b;
	}


	/**
	 * @brief 3���� ������ �پ��� ���� �����Դϴ�.
	 */
	union
	{
		struct
		{
			float x;
			float y;
			float z;
		};
		float data[3];
	};
};


/**
 * @brief ������ ������ Ÿ���� ������ 3���� �����Դϴ�.
 */
struct Vec4i
{
	/**
	 * @brief 4���� ������ �⺻ �������Դϴ�.
	 *
	 * @note ��� ������ ���� 0���� �ʱ�ȭ�մϴ�.
	 */
	Vec4i() noexcept : x(0), y(0), z(0), w(0) {}


	/**
	 * @brief 4���� ������ �������Դϴ�.
	 *
	 * @param xx ������ x �����Դϴ�.
	 * @param yy ������ y �����Դϴ�.
	 * @param zz ������ z �����Դϴ�.
	 * @param ww ������ w �����Դϴ�.
	 */
	Vec4i(int32_t&& xx, int32_t&& yy, int32_t&& zz, int32_t&& ww) noexcept : x(xx), y(yy), z(zz), w(ww) {}


	/**
	 * @brief 4���� ������ �������Դϴ�.
	 *
	 * @param xx ������ x �����Դϴ�.
	 * @param yy ������ y �����Դϴ�.
	 * @param zz ������ z �����Դϴ�.
	 * @param ww ������ w �����Դϴ�.
	 */
	Vec4i(const int32_t& xx, const int32_t& yy, const int32_t& zz, const int32_t& ww) noexcept : x(xx), y(yy), z(zz), w(ww) {}


	/**
	 * @brief 4���� ������ ���Ҹ� �ϳ��� ������ �ʱ�ȭ�մϴ�.
	 *
	 * @param e ��� ���Ҹ� �ʱ�ȭ �� ���Դϴ�.
	 */
	Vec4i(int32_t&& e) noexcept : x(e), y(e), z(e), w(e) {}


	/**
	 * @brief 4���� ������ ���Ҹ� �ϳ��� ������ �ʱ�ȭ�մϴ�.
	 *
	 * @param e ��� ���Ҹ� �ʱ�ȭ �� ���Դϴ�.
	 */
	Vec4i(const int32_t& e) noexcept : x(e), y(e), z(e), w(e) {}


	/**
	 * @brief 4���� ������ ���� �������Դϴ�.
	 *
	 * @param v ���Ҹ� ������ ���� ����ü�� �ν��Ͻ��Դϴ�.
	 */
	Vec4i(Vec4i&& v) noexcept : x(v.x), y(v.y), z(v.z), w(v.w) {}


	/**
	 * @brief 4���� ������ ���� �������Դϴ�.
	 *
	 * @param v ���Ҹ� ������ ������ �ν��Ͻ��Դϴ�.
	 */
	Vec4i(const Vec4i& v) noexcept : x(v.x), y(v.y), z(v.z), w(v.w) {}


	/**
	 * @brief 4���� ������ ���� ������ �Դϴ�.
	 *
	 * @param v ���Ҹ� ������ ���� ����ü�� �ν��Ͻ��Դϴ�.
	 *
	 * @return ������ ������ �����ڸ� ��ȯ�մϴ�.
	 */
	Vec4i& operator=(Vec4i&& v) noexcept
	{
		if (this == &v) return *this;

		x = v.x;
		y = v.y;
		z = v.z;
		w = v.w;

		return *this;
	}


	/**
	 * @brief 4���� ������ ���� ������ �Դϴ�.
	 *
	 * @param v ���Ҹ� ������ ���� ����ü�� �ν��Ͻ��Դϴ�.
	 *
	 * @return ������ ������ �����ڸ� ��ȯ�մϴ�.
	 */
	Vec4i& operator=(const Vec4i& v) noexcept
	{
		if (this == &v) return *this;

		x = v.x;
		y = v.y;
		z = v.z;
		w = v.w;

		return *this;
	}


	/**
	 * @brief 4���� ������ ���ҿ� -��ȣ�� ���մϴ�.
	 *
	 * @return 4���� ������ ���ҿ� -��ȣ�� ���� ���ο� ���͸� ��ȯ�մϴ�.
	 */
	Vec4i operator-() const
	{
		return Vec4i(-x, -y, -z, -w);
	}


	/**
	 * @brief �� 4���� ���Ϳ� �����ϴ� ���Ҹ� ���մϴ�.
	 *
	 * @param v ������ ������ ������ �ǿ������Դϴ�.
	 *
	 * @return �� ���Ϳ� �����ϴ� ���Ҹ� ���� ����� ��ȯ�մϴ�.
	 */
	Vec4i operator+(Vec4i&& v) const
	{
		return Vec4i(x + v.x, y + v.y, z + v.z, w + v.w);
	}


	/**
	 * @brief �� 4���� ���Ϳ� �����ϴ� ���Ҹ� ���մϴ�.
	 *
	 * @param v ������ ������ ������ �ǿ������Դϴ�.
	 *
	 * @return �� ���Ϳ� �����ϴ� ���Ҹ� ���� ����� ��ȯ�մϴ�.
	 */
	Vec4i operator+(const Vec4i& v) const
	{
		return Vec4i(x + v.x, y + v.y, z + v.z, w + v.w);
	}


	/**
	 * @brief �� 4���� ���Ϳ� �����ϴ� ���Ҹ� ���ϴ�.
	 *
	 * @param v ������ ������ ������ �ǿ������Դϴ�.
	 *
	 * @return �� ���Ϳ� �����ϴ� ���Ҹ� �� ����� ��ȯ�մϴ�.
	 */
	Vec4i operator-(Vec4i&& v) const
	{
		return Vec4i(x - v.x, y - v.y, z - v.z, w - v.w);
	}


	/**
	 * @brief �� 4���� ���Ϳ� �����ϴ� ���Ҹ� ���ϴ�.
	 *
	 * @param v ������ ������ ������ �ǿ������Դϴ�.
	 *
	 * @return �� ���Ϳ� �����ϴ� ���Ҹ� �� ����� ��ȯ�մϴ�.
	 */
	Vec4i operator-(const Vec4i& v) const
	{
		return Vec4i(x - v.x, y - v.y, z - v.z, w - v.w);
	}


	/**
	 * @brief �� 4���� ���Ϳ� �����ϴ� ���Ҹ� ���� ���մϴ�.
	 *
	 * @note �� ������ ������ ���� ����(Dot Product)�ʹ� �ٸ��ϴ�.
	 *
	 * @param v ������ ������ ������ �ǿ������Դϴ�.
	 *
	 * @return �� ���Ϳ� �����ϴ� ���Ҹ� ���� ����� ��ȯ�մϴ�.
	 */
	Vec4i operator*(Vec4i&& v) const
	{
		return Vec4i(x * v.x, y * v.y, z * v.z, w * v.w);
	}


	/**
	 * @brief �� 4���� ���Ϳ� �����ϴ� ���Ҹ� ���� ���մϴ�.
	 *
	 * @note �� ������ ������ ���� ����(Dot Product)�ʹ� �ٸ��ϴ�.
	 *
	 * @param v ������ ������ ������ �ǿ������Դϴ�.
	 *
	 * @return �� ���Ϳ� �����ϴ� ���Ҹ� ���� ����� ��ȯ�մϴ�.
	 */
	Vec4i operator*(const Vec4i& v) const
	{
		return Vec4i(x * v.x, y * v.y, z * v.z, w * v.w);
	}


	/**
	 * @brief �� 4���� ���Ϳ� �����ϴ� ���Ҹ� ���մϴ�.
	 *
	 * @param v ������ ������ �ǿ������Դϴ�.
	 *
	 * @return ������ ������ ������ �����ڸ� ��ȯ�մϴ�.
	 */
	Vec4i& operator+=(Vec4i&& v) noexcept
	{
		x += v.x;
		y += v.y;
		z += v.z;
		w += v.w;

		return *this;
	}


	/**
	 * @brief �� 4���� ���Ϳ� �����ϴ� ���Ҹ� ���մϴ�.
	 *
	 * @param v ������ ������ �ǿ������Դϴ�.
	 *
	 * @return ������ ������ ������ �����ڸ� ��ȯ�մϴ�.
	 */
	Vec4i& operator+=(const Vec4i& v) noexcept
	{
		x += v.x;
		y += v.y;
		z += v.z;
		w += v.w;

		return *this;
	}


	/**
	 * @brief �� 4���� ���Ϳ� �����ϴ� ���Ҹ� ���ϴ�.
	 *
	 * @param v ������ ������ �ǿ������Դϴ�.
	 *
	 * @return ������ ������ ������ �����ڸ� ��ȯ�մϴ�.
	 */
	Vec4i& operator-=(Vec4i&& v) noexcept
	{
		x -= v.x;
		y -= v.y;
		z -= v.z;
		w -= v.w;

		return *this;
	}


	/**
	 * @brief �� 4���� ���Ϳ� �����ϴ� ���Ҹ� ���ϴ�.
	 *
	 * @param v ������ ������ �ǿ������Դϴ�.
	 *
	 * @return ������ ������ ������ �����ڸ� ��ȯ�մϴ�.
	 */
	Vec4i& operator-=(const Vec4i& v) noexcept
	{
		x -= v.x;
		y -= v.y;
		z -= v.z;
		w -= v.w;

		return *this;
	}


	/**
	 * @brief �� 4���� ���Ͱ� �������� �˻��մϴ�.
	 *
	 * @param v �˻縦 ������ �ǿ������Դϴ�.
	 *
	 * @return �� ���Ͱ� �����ϴٸ� true, �׷��� ������ false�� ��ȯ�մϴ�.
	 */
	bool operator==(Vec4i&& v) const
	{
		return (x == v.x) && (y == v.y) && (z == v.z) && (w == v.w);
	}


	/**
	 * @brief �� 4���� ���Ͱ� �������� �˻��մϴ�.
	 *
	 * @param v �˻縦 ������ �ǿ������Դϴ�.
	 *
	 * @return �� ���Ͱ� �����ϴٸ� true, �׷��� ������ false�� ��ȯ�մϴ�.
	 */
	bool operator==(const Vec4i& v) const
	{
		return (x == v.x) && (y == v.y) && (z == v.z) && (w == v.w);
	}


	/**
	 * @brief �� 4���� ���Ͱ� �������� ������ �˻��մϴ�.
	 *
	 * @param v �˻縦 ������ �ǿ������Դϴ�.
	 *
	 * @return �� ���Ͱ� �������� �ʴٸ� true, �׷��ٸ� false�� ��ȯ�մϴ�.
	 */
	bool operator!=(Vec4i&& v) const
	{
		return (x != v.x) || (y != v.y) || (z != v.z) || (w != v.w);
	}


	/**
	 * @brief �� 4���� ���Ͱ� �������� ������ �˻��մϴ�.
	 *
	 * @param v �˻縦 ������ �ǿ������Դϴ�.
	 *
	 * @return �� ���Ͱ� �������� �ʴٸ� true, �׷��ٸ� false�� ��ȯ�մϴ�.
	 */
	bool operator!=(const Vec4i& v) const
	{
		return (x != v.x) || (y != v.y) || (z != v.z) || (w != v.w);
	}


	/**
	 * @brief 4���� ���� ���� �迭�� �����͸� ����ϴ�.
	 *
	 * @return 4���� ���� ���� �迭�� �����͸� ��ȯ�մϴ�.
	 */
	const int32_t* GetPtr() const { return &data[0]; }


	/**
	 * @brief 4���� ���� ���� �迭�� �����͸� ����ϴ�.
	 *
	 * @return 4���� ���� ���� �迭�� �����͸� ��ȯ�մϴ�.
	 */
	int32_t* GetPtr() { return &data[0]; }


	/**
	 * @brief 4���� ������ ���� ������ �����մϴ�.
	 *
	 * @param lhs ������ ���� ������ ������ ���� �ǿ������Դϴ�.
	 * @param rhs ������ ���� ������ ������ ���� �ǿ������Դϴ�.
	 *
	 * @return ���� ���� ����� ��ȯ�մϴ�.
	 */
	static inline int32_t Dot(const Vec4i& lhs, const Vec4i& rhs)
	{
		return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z + lhs.w * rhs.w;
	}


	/**
	 * @brief 4���� ������ ũ�� ���� ���� ����մϴ�.
	 *
	 * @param v ũ�� ������ ����� �����Դϴ�.
	 *
	 * @return ���� ũ�� ���� ���� ��ȯ�մϴ�.
	 */
	static inline int32_t LengthSq(const Vec4i& v)
	{
		return v.x * v.x + v.y * v.y + v.z * v.z + v.w * v.w;
	}


	/**
	 * @brief 4���� ������ ũ�⸦ ����ϴ�.
	 *
	 * @param v ũ�⸦ ����� �����Դϴ�.
	 *
	 * @return ���� ũ�� ���� ��ȯ�մϴ�.
	 */
	static inline float Length(const Vec4i& v)
	{
		float lengthSq = static_cast<float>(LengthSq(v));
		return Sqrt(lengthSq);
	}


	/**
	 * @brief �� 4���� ���� ������ ���� ����մϴ�.
	 *
	 * @param lhs ���� ������ ���� ����� ���� �ǿ����� �����Դϴ�.
	 * @param rhs ���� ������ ���� ����� ������ �ǿ����� �����Դϴ�.
	 *
	 * @return �� 4���� ���� ������ ���� ������ ��ȯ�մϴ�.
	 */
	static inline float Radian(const Vec4i& lhs, const Vec4i& rhs)
	{
		float lengthL = Length(lhs);
		float lengthR = Length(rhs);
		float dot = Dot(lhs, rhs);

		return ACos(dot / (lengthL * lengthR));
	}


	/**
	 * @brief �� 4���� ���� ������ ���� ����մϴ�.
	 *
	 * @param lhs ���� ������ ���� ����� ���� �ǿ����� �����Դϴ�.
	 * @param rhs ���� ������ ���� ����� ������ �ǿ����� �����Դϴ�.
	 *
	 * @return �� 4���� ���� ������ ���ʺй� ������ ��ȯ�մϴ�.
	 */
	static inline float Degree(const Vec4i& lhs, const Vec4i& rhs)
	{
		float radian = Radian(lhs, rhs);
		return ToDegree(radian);
	}


	/**
	 * @brief 4���� ������ �پ��� ���� �����Դϴ�.
	 */
	union
	{
		struct
		{
			int32_t x;
			int32_t y;
			int32_t z;
			int32_t w;
		};
		int32_t data[4];
	};
};


/**
 * @brief ������ ������ Ÿ���� �ε� �Ҽ����� 4���� �����Դϴ�.
 */
struct Vec4f
{
	/**
	 * @brief 4���� ������ �⺻ �������Դϴ�.
	 *
	 * @note ��� ������ ���� 0���� �ʱ�ȭ�մϴ�.
	 */
	Vec4f() noexcept : x(0.0f), y(0.0f), z(0.0f), w(0.0f) {}


	/**
	 * @brief 4���� ������ �������Դϴ�.
	 *
	 * @param xx ������ x �����Դϴ�.
	 * @param yy ������ y �����Դϴ�.
	 * @param zz ������ z �����Դϴ�.
	 * @param ww ������ w �����Դϴ�.
	 */
	Vec4f(float&& xx, float&& yy, float&& zz, float&& ww) noexcept : x(xx), y(yy), z(zz), w(ww) {}


	/**
	 * @brief 4���� ������ �������Դϴ�.
	 *
	 * @param xx ������ x �����Դϴ�.
	 * @param yy ������ y �����Դϴ�.
	 * @param zz ������ z �����Դϴ�.
	 * @param ww ������ w �����Դϴ�.
	 */
	Vec4f(const float& xx, const float& yy, const float& zz, const float& ww) noexcept : x(xx), y(yy), z(zz), w(ww) {}


	/**
	 * @brief 4���� ������ ���Ҹ� �ϳ��� ������ �ʱ�ȭ�մϴ�.
	 *
	 * @param e ��� ���Ҹ� �ʱ�ȭ �� ���Դϴ�.
	 */
	Vec4f(float&& e) noexcept : x(e), y(e), z(e), w(e) {}


	/**
	 * @brief 4���� ������ ���Ҹ� �ϳ��� ������ �ʱ�ȭ�մϴ�.
	 *
	 * @param e ��� ���Ҹ� �ʱ�ȭ �� ���Դϴ�.
	 */
	Vec4f(const float& e) noexcept : x(e), y(e), z(e), w(e) {}


	/**
	 * @brief 4���� ������ ���� �������Դϴ�.
	 *
	 * @param v ���Ҹ� ������ ���� ����ü�� �ν��Ͻ��Դϴ�.
	 */
	Vec4f(Vec4f&& v) noexcept : x(v.x), y(v.y), z(v.z), w(v.w) {}


	/**
	 * @brief 4���� ������ ���� �������Դϴ�.
	 *
	 * @param v ���Ҹ� ������ ������ �ν��Ͻ��Դϴ�.
	 */
	Vec4f(const Vec4f& v) noexcept : x(v.x), y(v.y), z(v.z), w(v.w) {}


	/**
	 * @brief 4���� ������ ���� ������ �Դϴ�.
	 *
	 * @param v ���Ҹ� ������ ���� ����ü�� �ν��Ͻ��Դϴ�.
	 *
	 * @return ������ ������ �����ڸ� ��ȯ�մϴ�.
	 */
	Vec4f& operator=(Vec4f&& v) noexcept
	{
		if (this == &v) return *this;

		x = v.x;
		y = v.y;
		z = v.z;
		w = v.w;

		return *this;
	}


	/**
	 * @brief 4���� ������ ���� ������ �Դϴ�.
	 *
	 * @param v ���Ҹ� ������ ���� ����ü�� �ν��Ͻ��Դϴ�.
	 *
	 * @return ������ ������ �����ڸ� ��ȯ�մϴ�.
	 */
	Vec4f& operator=(const Vec4f& v) noexcept
	{
		if (this == &v) return *this;

		x = v.x;
		y = v.y;
		z = v.z;
		w = v.w;

		return *this;
	}


	/**
	 * @brief 4���� ������ ���ҿ� -��ȣ�� ���մϴ�.
	 *
	 * @return 4���� ������ ���ҿ� -��ȣ�� ���� ���ο� ���͸� ��ȯ�մϴ�.
	 */
	Vec4f operator-() const
	{
		return Vec4f(-x, -y, -z, -w);
	}


	/**
	 * @brief �� 4���� ���Ϳ� �����ϴ� ���Ҹ� ���մϴ�.
	 *
	 * @param v ������ ������ ������ �ǿ������Դϴ�.
	 *
	 * @return �� ���Ϳ� �����ϴ� ���Ҹ� ���� ����� ��ȯ�մϴ�.
	 */
	Vec4f operator+(Vec4f&& v) const
	{
		return Vec4f(x + v.x, y + v.y, z + v.z, w + v.w);
	}


	/**
	 * @brief �� 4���� ���Ϳ� �����ϴ� ���Ҹ� ���մϴ�.
	 *
	 * @param v ������ ������ ������ �ǿ������Դϴ�.
	 *
	 * @return �� ���Ϳ� �����ϴ� ���Ҹ� ���� ����� ��ȯ�մϴ�.
	 */
	Vec4f operator+(const Vec4f& v) const
	{
		return Vec4f(x + v.x, y + v.y, z + v.z, w + v.w);
	}


	/**
	 * @brief �� 4���� ���Ϳ� �����ϴ� ���Ҹ� ���ϴ�.
	 *
	 * @param v ������ ������ ������ �ǿ������Դϴ�.
	 *
	 * @return �� ���Ϳ� �����ϴ� ���Ҹ� �� ����� ��ȯ�մϴ�.
	 */
	Vec4f operator-(Vec4f&& v) const
	{
		return Vec4f(x - v.x, y - v.y, z - v.z, w - v.w);
	}


	/**
	 * @brief �� 4���� ���Ϳ� �����ϴ� ���Ҹ� ���ϴ�.
	 *
	 * @param v ������ ������ ������ �ǿ������Դϴ�.
	 *
	 * @return �� ���Ϳ� �����ϴ� ���Ҹ� �� ����� ��ȯ�մϴ�.
	 */
	Vec4f operator-(const Vec4f& v) const
	{
		return Vec4f(x - v.x, y - v.y, z - v.z, w - v.w);
	}


	/**
	 * @brief �� 4���� ���Ϳ� �����ϴ� ���Ҹ� ���� ���մϴ�.
	 *
	 * @note �� ������ ������ ���� ����(Dot Product)�ʹ� �ٸ��ϴ�.
	 *
	 * @param v ������ ������ ������ �ǿ������Դϴ�.
	 *
	 * @return �� ���Ϳ� �����ϴ� ���Ҹ� ���� ����� ��ȯ�մϴ�.
	 */
	Vec4f operator*(Vec4f&& v) const
	{
		return Vec4f(x * v.x, y * v.y, z * v.z, w * v.w);
	}


	/**
	 * @brief �� 4���� ���Ϳ� �����ϴ� ���Ҹ� ���� ���մϴ�.
	 *
	 * @note �� ������ ������ ���� ����(Dot Product)�ʹ� �ٸ��ϴ�.
	 *
	 * @param v ������ ������ ������ �ǿ������Դϴ�.
	 *
	 * @return �� ���Ϳ� �����ϴ� ���Ҹ� ���� ����� ��ȯ�մϴ�.
	 */
	Vec4f operator*(const Vec4f& v) const
	{
		return Vec4f(x * v.x, y * v.y, z * v.z, w * v.w);
	}


	/**
	 * @brief �� 4���� ���Ϳ� �����ϴ� ���Ҹ� ���մϴ�.
	 *
	 * @param v ������ ������ �ǿ������Դϴ�.
	 *
	 * @return ������ ������ ������ �����ڸ� ��ȯ�մϴ�.
	 */
	Vec4f& operator+=(Vec4f&& v) noexcept
	{
		x += v.x;
		y += v.y;
		z += v.z;
		w += v.w;

		return *this;
	}


	/**
	 * @brief �� 4���� ���Ϳ� �����ϴ� ���Ҹ� ���մϴ�.
	 *
	 * @param v ������ ������ �ǿ������Դϴ�.
	 *
	 * @return ������ ������ ������ �����ڸ� ��ȯ�մϴ�.
	 */
	Vec4f& operator+=(const Vec4f& v) noexcept
	{
		x += v.x;
		y += v.y;
		z += v.z;
		w += v.w;

		return *this;
	}


	/**
	 * @brief �� 4���� ���Ϳ� �����ϴ� ���Ҹ� ���ϴ�.
	 *
	 * @param v ������ ������ �ǿ������Դϴ�.
	 *
	 * @return ������ ������ ������ �����ڸ� ��ȯ�մϴ�.
	 */
	Vec4f& operator-=(Vec4f&& v) noexcept
	{
		x -= v.x;
		y -= v.y;
		z -= v.z;
		w -= v.w;

		return *this;
	}


	/**
	 * @brief �� 4���� ���Ϳ� �����ϴ� ���Ҹ� ���ϴ�.
	 *
	 * @param v ������ ������ �ǿ������Դϴ�.
	 *
	 * @return ������ ������ ������ �����ڸ� ��ȯ�մϴ�.
	 */
	Vec4f& operator-=(const Vec4f& v) noexcept
	{
		x -= v.x;
		y -= v.y;
		z -= v.z;
		w -= v.w;

		return *this;
	}


	/**
	 * @brief �� 4���� ���Ͱ� �������� �˻��մϴ�.
	 *
	 * @param v �˻縦 ������ �ǿ������Դϴ�.
	 *
	 * @return �� ���Ͱ� �����ϴٸ� true, �׷��� ������ false�� ��ȯ�մϴ�.
	 */
	bool operator==(Vec4f&& v) const
	{
		return Abs(x - v.x) <= EPSILON && Abs(y - v.y) <= EPSILON && Abs(z - v.z) <= EPSILON && Abs(w - v.w) <= EPSILON;
	}


	/**
	 * @brief �� 4���� ���Ͱ� �������� �˻��մϴ�.
	 *
	 * @param v �˻縦 ������ �ǿ������Դϴ�.
	 *
	 * @return �� ���Ͱ� �����ϴٸ� true, �׷��� ������ false�� ��ȯ�մϴ�.
	 */
	bool operator==(const Vec4f& v) const
	{
		return Abs(x - v.x) <= EPSILON && Abs(y - v.y) <= EPSILON && Abs(z - v.z) <= EPSILON && Abs(w - v.w) <= EPSILON;
	}


	/**
	 * @brief �� 4���� ���Ͱ� �������� ������ �˻��մϴ�.
	 *
	 * @param v �˻縦 ������ �ǿ������Դϴ�.
	 *
	 * @return �� ���Ͱ� �������� �ʴٸ� true, �׷��ٸ� false�� ��ȯ�մϴ�.
	 */
	bool operator!=(Vec4f&& v) const
	{
		return Abs(x - v.x) > EPSILON || Abs(y - v.y) > EPSILON || Abs(z - v.z) > EPSILON || Abs(w - v.w) > EPSILON;
	}


	/**
	 * @brief �� 4���� ���Ͱ� �������� ������ �˻��մϴ�.
	 *
	 * @param v �˻縦 ������ �ǿ������Դϴ�.
	 *
	 * @return �� ���Ͱ� �������� �ʴٸ� true, �׷��ٸ� false�� ��ȯ�մϴ�.
	 */
	bool operator!=(const Vec4f& v) const
	{
		return Abs(x - v.x) > EPSILON || Abs(y - v.y) > EPSILON || Abs(z - v.z) > EPSILON || Abs(w - v.w) > EPSILON;
	}


	/**
	 * @brief 4���� ���� ���� �迭�� �����͸� ����ϴ�.
	 *
	 * @return 4���� ���� ���� �迭�� �����͸� ��ȯ�մϴ�.
	 */
	const float* GetPtr() const { return &data[0]; }


	/**
	 * @brief 4���� ���� ���� �迭�� �����͸� ����ϴ�.
	 *
	 * @return 4���� ���� ���� �迭�� �����͸� ��ȯ�մϴ�.
	 */
	float* GetPtr() { return &data[0]; }


	/**
	 * @brief 4���� ������ ���� ������ �����մϴ�.
	 *
	 * @param lhs ������ ���� ������ ������ ���� �ǿ������Դϴ�.
	 * @param rhs ������ ���� ������ ������ ���� �ǿ������Դϴ�.
	 *
	 * @return ���� ���� ����� ��ȯ�մϴ�.
	 */
	static inline float Dot(const Vec4f& lhs, const Vec4f& rhs)
	{
		return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z + lhs.w * rhs.w;
	}


	/**
	 * @brief 4���� ������ ũ�� ���� ���� ����մϴ�.
	 *
	 * @param v ũ�� ������ ����� �����Դϴ�.
	 *
	 * @return ���� ũ�� ���� ���� ��ȯ�մϴ�.
	 */
	static inline float LengthSq(const Vec4f& v)
	{
		return v.x * v.x + v.y * v.y + v.z * v.z + v.w * v.w;
	}


	/**
	 * @brief 4���� ������ ũ�⸦ ����ϴ�.
	 *
	 * @param v ũ�⸦ ����� �����Դϴ�.
	 *
	 * @return ���� ũ�� ���� ��ȯ�մϴ�.
	 */
	static inline float Length(const Vec4f& v)
	{
		float lengthSq = LengthSq(v);
		return Sqrt(lengthSq);
	}


	/**
	 * @brief 4���� ���͸� ����ȭ�մϴ�.
	 *
	 * @param v ����ȭ �� �����Դϴ�.
	 *
	 * @return ����ȭ�� ���͸� ��ȯ�մϴ�.
	 */
	static inline Vec4f Normalize(const Vec4f& v)
	{
		float length = Length(v);

		if (NearZero(length))
		{
			return v;
		}

		float invLength = 1.0f / length;
		return Vec4f(v.x * invLength, v.y * invLength, v.z * invLength, v.w * invLength);
	}


	/**
	 * @brief �� 4���� ���� ������ ���� ����մϴ�.
	 *
	 * @param lhs ���� ������ ���� ����� ���� �ǿ����� �����Դϴ�.
	 * @param rhs ���� ������ ���� ����� ������ �ǿ����� �����Դϴ�.
	 *
	 * @return �� 4���� ���� ������ ���� ������ ��ȯ�մϴ�.
	 */
	static inline float Radian(const Vec4f& lhs, const Vec4f& rhs)
	{
		float lengthL = Length(lhs);
		float lengthR = Length(rhs);
		float dot = Dot(lhs, rhs);

		return ACos(dot / (lengthL * lengthR));
	}


	/**
	 * @brief �� 4���� ���� ������ ���� ����մϴ�.
	 *
	 * @param lhs ���� ������ ���� ����� ���� �ǿ����� �����Դϴ�.
	 * @param rhs ���� ������ ���� ����� ������ �ǿ����� �����Դϴ�.
	 *
	 * @return �� 4���� ���� ������ ���ʺй� ������ ��ȯ�մϴ�.
	 */
	static inline float Degree(const Vec4f& lhs, const Vec4f& rhs)
	{
		float radian = Radian(lhs, rhs);
		return ToDegree(radian);
	}


	/**
	 * @brief Base 4���� ���Ϳ� Target 4���� ���͸� �����մϴ�.
	 *
	 * @param target ���� ��� ������ �����Դϴ�.
	 * @param base ���� ����� �Ǵ� �����Դϴ�.
	 *
	 * @return base�� ������ target ���͸� ��ȯ�մϴ�.
	 */
	static inline Vec4f Project(const Vec4f& target, const Vec4f& base)
	{
		float dot = Dot(target, base);
		float lengthSq = LengthSq(base);
		float scale = dot / lengthSq;

		return Vec4f(base.x * scale, base.y * scale, base.z * scale, base.w * scale);
	}


	/**
	 * @brief Base 4���� ���Ϳ� Target 4���� ���͸� ������ ���Ϳ� ������ ���͸� ����մϴ�.
	 *
	 * @param target ���� ��� ������ �����Դϴ�.
	 * @param base ���� ����� �Ǵ� �����Դϴ�.
	 *
	 * @return ������ ������ ������ ���͸� ��ȯ�մϴ�.
	 */
	static inline Vec4f Reject(const Vec4f& target, const Vec4f& base)
	{
		Vec4f project = Project(target, base);
		return target - project;
	}


	/**
	 * @brief �� ���͸� ���� ������ ���͸� ����մϴ�.
	 *
	 * @param s ������ ���� �����Դϴ�.
	 * @param e ������ �� �����Դϴ�.
	 * @param t �� ������ ���� �����Դϴ�.
	 *
	 * @return ������ ���͸� ��ȯ�մϴ�.
	 */
	static inline Vec4f Lerp(const Vec4f& s, const Vec4f& e, const float& t)
	{
		return s * (1.0f - t) + e * t;
	}


	/**
	 * @brief �� ���͸� ���� ���� ������ ���͸� ����մϴ�.
	 *
	 * @param s ������ ���� �����Դϴ�.
	 * @param e ������ �� �����Դϴ�.
	 * @param t �� ������ ���� �����Դϴ�.
	 *
	 * @return ������ ���͸� ��ȯ�մϴ�.
	 */
	static inline Vec4f Slerp(const Vec4f& s, const Vec4f& e, const float& t)
	{
		Vec4f start = Normalize(s);
		Vec4f end = Normalize(e);

		float theta = Radian(start, end);
		float sinTheta = Sin(theta);

		float a = Sin((1.0f - t) * theta) / sinTheta;
		float b = Sin(t * theta) / sinTheta;

		return s * a + e * b;
	}


	/**
	 * @brief 4���� ������ �پ��� ���� �����Դϴ�.
	 */
	union
	{
		struct
		{
			float x;
			float y;
			float z;
			float w;
		};
		float data[4];
	};
};

}