#pragma once

#include "Mat4x4.h"
#include "MathModule.h"
#include "Vec3.h"


/**
 * @brief ���ʹϾ��Դϴ�.
 * 
 * @see 
 * - https://gabormakesgames.com/quaternions.html
 * - https://en.wikipedia.org/wiki/Quaternion
 * - https://github.com/mmp/pbrt-v3/blob/master/src/core/quaternion.h
 */
struct Quat
{
	/**
	 * @brief ���ʹϾ��� �⺻ �������Դϴ�.
	 *
	 * @note ��� ������ ���� 0���� �ʱ�ȭ�մϴ�.
	 */
	Quat() noexcept : x(0.0f), y(0.0f), z(0.0f), w(1.0f) {}


	/**
	 * @brief ���ʹϾ��� �������Դϴ�.
	 *
	 * @param xx ���ʹϾ��� x �����Դϴ�.
	 * @param yy ���ʹϾ��� y �����Դϴ�.
	 * @param zz ���ʹϾ��� z �����Դϴ�.
	 * @param ww ���ʹϾ��� w �����Դϴ�.
	 */
	Quat(float&& xx, float&& yy, float&& zz, float&& ww) noexcept : x(xx), y(yy), z(zz), w(ww) {}


	/**
	 * @brief ���ʹϾ��� �������Դϴ�.
	 *
	 * @param xx ���ʹϾ��� x �����Դϴ�.
	 * @param yy ���ʹϾ��� y �����Դϴ�.
	 * @param zz ���ʹϾ��� z �����Դϴ�.
	 * @param ww ���ʹϾ��� w �����Դϴ�.
	 */
	Quat(const float& xx, const float& yy, const float& zz, const float& ww) noexcept : x(xx), y(yy), z(zz), w(ww) {}


	/**
	 * @brief ���ʹϾ��� �������Դϴ�.
	 *
	 * @param vv i,j,k ���� ���� ����Դϴ�.
	 * @param ww ȸ���� �������� �����ϴ� w �����Դϴ�.
	 */
	Quat(Vec3f&& vv, float&& ww) noexcept : v(vv), w(ww) {}


	/**
	 * @brief ���ʹϾ��� �������Դϴ�.
	 *
	 * @param vv i,j,k ���� ���� ����Դϴ�.
	 * @param ww ȸ���� �������� �����ϴ� w �����Դϴ�.
	 */
	Quat(const Vec3f& vv, const float& ww) noexcept : v(vv), w(ww) {}


	/**
	 * @brief ���ʹϾ��� �������Դϴ�.
	 * 
	 * @param axis ȸ�� ���Դϴ�.
	 * @param radian ���� ������ ȸ�� �����Դϴ�. 
	 */
	Quat(const Vec3f& axis, float radian)
	{
		float s = MathModule::Sin(radian * 0.5f);
		float c = MathModule::Cos(radian * 0.5f);
		Vec3f norm = Vec3f::Normalize(axis);

		v = norm * s;
		w = c;
	}


	/**
	 * @brief ���ʹϾ��� ���� �������Դϴ�.
	 *
	 * @param q ���Ҹ� ������ ���ʹϾ� ����ü�� �ν��Ͻ��Դϴ�.
	 */
	Quat(Quat&& q) noexcept : x(q.x), y(q.y), z(q.z), w(q.w) {}


	/**
	 * @brief ���ʹϾ��� ���� �������Դϴ�.
	 *
	 * @param q ���Ҹ� ������ ���ʹϾ� ����ü�� �ν��Ͻ��Դϴ�.
	 */
	Quat(const Quat& q) noexcept : x(q.x), y(q.y), z(q.z), w(q.w) {}


	/**
	 * @brief ���ʹϾ��� ���� �������Դϴ�.
	 *
	 * @param q ���Ҹ� ������ ���ʹϾ� ����ü�� �ν��Ͻ��Դϴ�.
	 *
	 * @return ������ ���ʹϾ��� �����ڸ� ��ȯ�մϴ�.
	 */
	Quat& operator=(Quat&& q) noexcept
	{
		if (this == &q) return *this;

		x = q.x;
		y = q.y;
		z = q.z;
		w = q.w;

		return *this;
	}


	/**
	 * @brief ���ʹϾ��� ���� �������Դϴ�.
	 *
	 * @param q ���Ҹ� ������ ���ʹϾ� ����ü�� �ν��Ͻ��Դϴ�.
	 *
	 * @return ������ ���ʹϾ��� �����ڸ� ��ȯ�մϴ�.
	 */
	Quat& operator=(const Quat& q) noexcept
	{
		if (this == &q) return *this;

		x = q.x;
		y = q.y;
		z = q.z;
		w = q.w;

		return *this;
	}


	/**
	 * @brief ���ʹϾ� -��ȣ�� ���մϴ�.
	 *
	 * @return ���ʹϾ� -��ȣ�� ���� ���ο� ���͸� ��ȯ�մϴ�.
	 */
	Quat operator-() const
	{
		return Quat(-x, -y, -z, -w);
	}


	/**
	 * @brief �� ���ʹϾ� �����ϴ� ���Ҹ� ���մϴ�.
	 *
	 * @param q ���ʹϾ��� ������ ������ �ǿ������Դϴ�.
	 *
	 * @return �� ���ʹϾ� �����ϴ� ���Ҹ� ���� ����� ��ȯ�մϴ�.
	 */
	Quat operator+(Quat&& q) const
	{
		return Quat(x + q.x, y + q.y, z + q.z, w + q.w);
	}


	/**
	 * @brief �� ���ʹϾ� �����ϴ� ���Ҹ� ���մϴ�.
	 *
	 * @param q ���ʹϾ��� ������ ������ �ǿ������Դϴ�.
	 *
	 * @return �� ���ʹϾ� �����ϴ� ���Ҹ� ���� ����� ��ȯ�մϴ�.
	 */
	Quat operator+(const Quat& q) const
	{
		return Quat(x + q.x, y + q.y, z + q.z, w + q.w);
	}


	/**
	 * @brief �� ���ʹϾ� �����ϴ� ���Ҹ� ���ϴ�.
	 *
	 * @param q ���ʹϾ��� ������ ������ �ǿ������Դϴ�.
	 *
	 * @return �� ���ʹϾ� �����ϴ� ���Ҹ� �� ����� ��ȯ�մϴ�.
	 */
	Quat operator-(Quat&& q) const
	{
		return Quat(x - q.x, y - q.y, z - q.z, w - q.w);
	}


	/**
	 * @brief �� ���ʹϾ� �����ϴ� ���Ҹ� ���ϴ�.
	 *
	 * @param q ���ʹϾ��� ������ ������ �ǿ������Դϴ�.
	 *
	 * @return �� ���ʹϾ� �����ϴ� ���Ҹ� �� ����� ��ȯ�մϴ�.
	 */
	Quat operator-(const Quat& q) const
	{
		return Quat(x - q.x, y - q.y, z - q.z, w - q.w);
	}


	/**
	 * @brief ���ʹϾ��� ������ ������ �����մϴ�.
	 *
	 * @param s ������ ������ ������ ���Դϴ�.
	 *
	 * @return ������ ������ ������ ����� ��ȯ�մϴ�.
	 */
	Quat operator*(float s) const
	{
		return Quat(x * s, y * s, z * s, w * s);
	}


	/**
	 * @brief ���ʹϾ� ���� ������ �����մϴ�.
	 *
	 * @param q ���� ������ ������ ���ʹϾ� ���Դϴ�.
	 *
	 * @return ���� ������ ������ ����� ��ȯ�մϴ�.
	 */
	Quat operator*(Quat&& q) const
	{
		return Quat(
			+x * q.w + y * q.z - z * q.y + w * q.x,
			-x * q.z + y * q.w + z * q.x + w * q.y,
			+x * q.y - y * q.x + z * q.w + w * q.z,
			-x * q.x - y * q.y - z * q.z + w * q.w
		);
	}

	/**
	 * @brief ���ʹϾ� ���� ������ �����մϴ�.
	 *
	 * @param q ���� ������ ������ ���ʹϾ� ���Դϴ�.
	 *
	 * @return ���� ������ ������ ����� ��ȯ�մϴ�.
	 */
	Quat operator*(const Quat& q) const
	{
		return Quat(
			+x * q.w + y * q.z - z * q.y + w * q.x,
			-x * q.z + y * q.w + z * q.x + w * q.y,
			+x * q.y - y * q.x + z * q.w + w * q.z,
			-x * q.x - y * q.y - z * q.z + w * q.w
		);
	}


	/**
	 * @brief ���ʹϾ�� ������ ���� ������ �����մϴ�.
	 *
	 * @param vec ���� ������ ������ ���� ���Դϴ�.
	 *
	 * @return ���� ������ ������ ����� ��ȯ�մϴ�.
	 */
	Vec3f operator*(Vec3f&& vec) const
	{
		return v * 2.0f * Vec3f::Dot(v, vec) + vec * (w * w - Vec3f::Dot(v, v)) + Vec3f::Cross(v, vec) * 2.0f * w;
	}


	/**
	 * @brief ���ʹϾ�� ������ ���� ������ �����մϴ�.
	 *
	 * @param vec ���� ������ ������ ���� ���Դϴ�.
	 *
	 * @return ���� ������ ������ ����� ��ȯ�մϴ�.
	 */
	Vec3f operator*(const Vec3f& vec) const
	{
		return v * 2.0f * Vec3f::Dot(v, vec) + vec * (w * w - Vec3f::Dot(v, v)) + Vec3f::Cross(v, vec) * 2.0f * w;
	}
	

	/**
	 * @brief �� ���ʹϾ� �����ϴ� ���Ҹ� ���մϴ�.
	 *
	 * @param q ���ʹϾ��� ������ ������ �ǿ������Դϴ�.
	 *
	 * @return ������ ������ ���ʹϾ��� �����ڸ� ��ȯ�մϴ�.
	 */
	Quat& operator+=(Quat&& q) noexcept
	{
		x += q.x;
		y += q.y;
		z += q.z;
		w += q.w;

		return *this;
	}


	/**
	 * @brief �� ���ʹϾ� �����ϴ� ���Ҹ� ���մϴ�.
	 *
	 * @param q ���ʹϾ��� ������ ������ �ǿ������Դϴ�.
	 *
	 * @return ������ ������ ���ʹϾ��� �����ڸ� ��ȯ�մϴ�.
	 */
	Quat& operator+=(const Quat& q) noexcept
	{
		x += q.x;
		y += q.y;
		z += q.z;
		w += q.w;

		return *this;
	}


	/**
	 * @brief �� ���ʹϾ� �����ϴ� ���Ҹ� ���ϴ�.
	 *
	 * @param q ���ʹϾ��� ������ ������ �ǿ������Դϴ�.
	 *
	 * @return ������ ������ ���ʹϾ��� �����ڸ� ��ȯ�մϴ�.
	 */
	Quat& operator-=(Quat&& q) noexcept
	{
		x -= q.x;
		y -= q.y;
		z -= q.z;
		w -= q.w;

		return *this;
	}


	/**
	 * @brief �� ���ʹϾ� �����ϴ� ���Ҹ� ���ϴ�.
	 *
	 * @param q ���ʹϾ��� ������ ������ �ǿ������Դϴ�.
	 *
	 * @return ������ ������ ���ʹϾ��� �����ڸ� ��ȯ�մϴ�.
	 */
	Quat& operator-=(const Quat& q) noexcept
	{
		x -= q.x;
		y -= q.y;
		z -= q.z;
		w -= q.w;

		return *this;
	}


	/**
	 * @brief ���ʹϾ��� ������ ������ �����մϴ�.
	 *
	 * @param s ������ ������ ������ ���Դϴ�.
	 *
	 * @return ������ ������ ���ʹϾ��� �����ڸ� ��ȯ�մϴ�.
	 */
	Quat& operator*=(float s) noexcept
	{
		x *= s;
		y *= s;
		z *= s;
		w *= s;

		return *this;
	}


	/**
	 * @brief �� ���ʹϾ� �������� �˻��մϴ�.
	 *
	 * @param  q �˻縦 ������ �ǿ������Դϴ�.
	 *
	 * @return �� ���ʹϾ��� �����ϴٸ� true, �׷��� ������ false�� ��ȯ�մϴ�.
	 */
	bool operator==(Quat&& q) const
	{
		return MathModule::Abs(x - q.x) <= Epsilon && MathModule::Abs(y - q.y) <= Epsilon && MathModule::Abs(z - q.z) <= Epsilon && MathModule::Abs(w - q.w) <= Epsilon;
	}


	/**
	 * @brief �� ���ʹϾ� �������� �˻��մϴ�.
	 *
	 * @param q �˻縦 ������ �ǿ������Դϴ�.
	 *
	 * @return �� ���ʹϾ��� �����ϴٸ� true, �׷��� ������ false�� ��ȯ�մϴ�.
	 */
	bool operator==(const Quat& q) const
	{
		return MathModule::Abs(x - q.x) <= Epsilon && MathModule::Abs(y - q.y) <= Epsilon && MathModule::Abs(z - q.z) <= Epsilon && MathModule::Abs(w - q.w) <= Epsilon;
	}


	/**
	 * @brief �� ���ʹϾ� �������� ������ �˻��մϴ�.
	 *
	 * @param q �˻縦 ������ �ǿ������Դϴ�.
	 *
	 * @return �� ���ʹϾ��� �������� �ʴٸ� true, �׷��ٸ� false�� ��ȯ�մϴ�.
	 */
	bool operator!=(Quat&& q) const
	{
		return MathModule::Abs(x - q.x) > Epsilon || MathModule::Abs(y - q.y) > Epsilon || MathModule::Abs(z - q.z) > Epsilon || MathModule::Abs(w - q.w) > Epsilon;
	}


	/**
	 * @brief �� ���ʹϾ� �������� ������ �˻��մϴ�.
	 *
	 * @param q �˻縦 ������ �ǿ������Դϴ�.
	 *
	 * @return �� ���ʹϾ��� �������� �ʴٸ� true, �׷��ٸ� false�� ��ȯ�մϴ�.
	 */
	bool operator!=(const Quat& q) const
	{
		return MathModule::Abs(x - q.x) > Epsilon || MathModule::Abs(y - q.y) > Epsilon || MathModule::Abs(z - q.z) > Epsilon || MathModule::Abs(w - q.w) > Epsilon;
	}


	/**
	 * @brief ������ ���� �̿��ؼ� ���ʹϾ��� ����ϴ�.
	 *
	 * @parma axis �� �Դϴ�.
	 * @param radian ���� ������ �����Դϴ�.
	 */
	static inline Quat AxisRadian(const Vec3f& axis, float radian)
	{
		float s = MathModule::Sin(radian * 0.5f);
		float c = MathModule::Cos(radian * 0.5f);
		Vec3f norm = Vec3f::Normalize(axis);

		return Quat(norm.x * s, norm.y * s, norm.z * s, c);
	}


	/**
	 * @brief ������ ���� �̿��ؼ� ���ʹϾ��� ����ϴ�.
	 *
	 * @parma axis �� �Դϴ�.
	 * @param angle ���ʺй� ������ �����Դϴ�.
	 */
	static inline Quat AxisAngle(const Vec3f& axis, float angle)
	{
		float radian = MathModule::ToRadian(angle);

		float s = MathModule::Sin(radian * 0.5f);
		float c = MathModule::Cos(radian * 0.5f);
		Vec3f norm = Vec3f::Normalize(axis);

		return Quat(norm.x * s, norm.y * s, norm.z * s, c);
	}


	/**
	 * @brief ���ʹϾ��� ���� ����ϴ�.
	 *
	 * @param q ���� ���� ���ʹϾ��Դϴ�.
	 *
	 * @return ���ʹϾ��� ���� ��ȯ�մϴ�.
	 */
	static inline Vec3f Axis(const Quat& q)
	{
		return Vec3f::Normalize(Vec3f(q.x, q.y, q.z));
	}


	/**
	 * @brief ���ʹϾ��� ���� ���� ����ϴ�.
	 *
	 * @param q ���� ������ ���� ���ʹϾ��Դϴ�.
	 *
	 * @return ���ʹϾ��� ���� ���� ��ȯ�մϴ�.
	 */
	static inline float Radian(const Quat& q)
	{
		return 2.0f * MathModule::ACos(q.w);
	}


	/**
	 * @brief ���ʹϾ��� ���ʺй� ���� ����ϴ�.
	 *
	 * @param q ���ʺй� ������ ���� ���ʹϾ��Դϴ�.
	 *
	 * @return ���ʹϾ��� ���ʺй� ���� ��ȯ�մϴ�.
	 */
	static inline float Angle(const Quat& q)
	{
		return MathModule::ToDegree(2.0f * MathModule::ACos(q.w));
	}


	/**
	 * @brief �� ���ʹϾ��� ���� ������ �����մϴ�.
	 *
	 * @param lhs ���ʹϾ��� ���� ������ ������ ���� �ǿ������Դϴ�.
	 * @param rhs ���ʹϾ��� ���� ������ ������ ���� �ǿ������Դϴ�.
	 *
	 * @return ���� ���� ����� ��ȯ�մϴ�.
	 */
	static inline float Dot(const Quat& lhs, const Quat& rhs)
	{
		return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z + lhs.w * rhs.w;
	}


	/**
	 * @brief ���ʹϾ��� ũ�� ���� ���� ����մϴ�.
	 *
	 * @param q ũ�� ������ ����� ���ʹϾ��Դϴ�.
	 *
	 * @return ���� ũ�� ���� ���� ��ȯ�մϴ�.
	 */
	static inline float LengthSq(const Quat& q)
	{
		return q.x * q.x + q.y * q.y + q.z * q.z + q.w * q.w;
	}


	/**
	 * @brief ���ʹϾ��� ũ�⸦ ����ϴ�.
	 *
	 * @param q ũ�⸦ ����� �����Դϴ�.
	 *
	 * @return ���� ũ�� ���� ��ȯ�մϴ�.
	 */
	static inline float Length(const Quat& q)
	{
		float lengthSq = Quat::LengthSq(q);
		return MathModule::Sqrt(lengthSq);
	}


	/**
	 * @brief ���ʹϾ��� ����ȭ�մϴ�.
	 *
	 * @param q ����ȭ �� ���ʹϾ��Դϴ�.
	 *
	 * @return ����ȭ�� ���ʹϾ��� ��ȯ�մϴ�.
	 */
	static inline Quat Normalize(const Quat& q)
	{
		float invLength = 1.0f / Quat::Length(q);
		return Quat(q.x * invLength, q.y * invLength, q.z * invLength, q.w * invLength);
	}


	/**
	 * @brief �ӷ� ���ʹϾ��� ����ϴ�.
	 *
	 * @param q �ӷ� ���� ����� ���ʹϾ��Դϴ�.
	 *
	 * @return �ӷ� ���ʹϾ��� ��ȯ�մϴ�.
	 */
	static inline Quat Conjugate(const Quat& q)
	{
		return Quat(-q.x, -q.y, -q.z, q.w);
	}


	/**
	 * @brief ���ʹϾ��� ���� ������ ����ϴ�.
	 *
	 * @param ���� ������ ����� ���ʹϾ��Դϴ�.
	 *
	 * @return ���ʹϾ��� ���� ������ ��ȯ�մϴ�.
	 */
	static inline Quat Inverse(const Quat& q)
	{
		float invLengthSq = 1.0f / Quat::LengthSq(q);
		return Quat(-q.x * invLengthSq, -q.y * invLengthSq, -q.z * invLengthSq, q.w * invLengthSq);
	}


	/**
	 * @brief ��� ���Ұ� 0�� ���ʹϾ��� ����ϴ�.
	 *
	 * @return ��� ���Ұ� 0�� ���ʹϾ��� ��ȯ�մϴ�.
	 */
	static inline Quat Zero()
	{
		return Quat(0.0f, 0.0f, 0.0f, 0.0f);
	}


	/**
	 * @brief w�� ���� 1�� ���ʹϾ��� ����ϴ�.
	 *
	 * @return w�� ���� 1�� ���ʹϾ��� ����ϴ�.
	 */
	static inline Quat Identity()
	{
		return Quat(0.0f, 0.0f, 0.0f, 1.0f);
	}


	/**
	 * @brief ���ʹϾ��� �پ��� ���� �����Դϴ�.
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
		struct 
		{
			Vec3f v;
			float w;
		};
		float data[4];
	};
};