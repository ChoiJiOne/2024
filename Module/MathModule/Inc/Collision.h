#pragma once

#include "Vec3.h"


/**
 * @brief ��� �� ���� ����(Axis aligned bounding box)�Դϴ�.
 */
struct AABB
{
	/**
	 * @brief ��� �� ���� ������ �⺻ �������Դϴ�.
	 */
	AABB() = default;


	/**
	 * @brief ��� �� ���� ������ �������Դϴ�.
	 *
	 * @param cc ��� �� ���� ������ �߽� ��ǥ�Դϴ�.
	 * @param ee ��� �� ���� ������ X/Y/Z �� ���������� ũ���Դϴ�.
	 */
	AABB(const Vec3f& cc, const Vec3f& ee)
		: center(cc)
		, extents(ee) {}


	/**
	 * @brief ��� �� ���� ������ ���� �������Դϴ�.
	 *
	 * @param instance ���� ������Ƽ�� ������ �ν��Ͻ��Դϴ�.
	 */
	AABB(AABB&& instance) noexcept
		: center(instance.center)
		, extents(instance.extents) {}


	/**
	 * @brief ��� �� ���� ������ ���� �������Դϴ�.
	 *
	 * @param instance ���� ������Ƽ�� ������ �ν��Ͻ��Դϴ�.
	 */
	AABB(const AABB& instance) noexcept
		: center(instance.center)
		, extents(instance.extents) {}


	/**
	 * @brief ��� �� ���� ������ ���� �������Դϴ�.
	 *
	 * @param instance ���� ������Ƽ�� ������ �ν��Ͻ��Դϴ�.
	 *
	 * @return ������ ��ü�� �����ڸ� ��ȯ�մϴ�.
	 */
	AABB& operator=(AABB&& instance) noexcept
	{
		if (this == &instance) return *this;

		center = instance.center;
		extents = instance.extents;

		return *this;
	}


	/**
	 * @brief ��� �� ���� ������ ���� �������Դϴ�.
	 *
	 * @param instance ���� ������Ƽ�� ������ �ν��Ͻ��Դϴ�.
	 *
	 * @return ������ ��ü�� �����ڸ� ��ȯ�մϴ�.
	 */
	AABB& operator=(const AABB& instance) noexcept
	{
		if (this == &instance) return *this;

		center = instance.center;
		extents = instance.extents;

		return *this;
	}


	/**
	 * @brief ��� ������ �ּҰ��� ����ϴ�.
	 * 
	 * @param instance ��� ������ �ּҰ��� ���� �ν��Ͻ��Դϴ�.
	 *
	 * @return ��� ������ �ּҰ��� ��ȯ�մϴ�.
	 */
	static Vec3f GetMin(const AABB& aabb) { return aabb.center - aabb.extents * 0.5f; }


	/**
	 * @brief ��� ������ �ִ��� ����ϴ�.
	 *
	 * @param instance ��� ������ �ּҰ��� ���� �ν��Ͻ��Դϴ�.
	 * 
	 * @return ��� ������ �ִ��� ��ȯ�մϴ�.
	 */
	static Vec3f GetMax(const AABB& aabb) { return aabb.center + aabb.extents * 0.5f; }


	/**
	 * @brief ��� ���� ���� ���� ����� ���� ã���ϴ�.
	 * 
	 * @param aabb ����� ���� ã�� ��� �����Դϴ�.
	 * @param position ����� ���Դϴ�.
	 * 
	 * @return ��� ���� ���� ���� ����� ���� ��ȯ�մϴ�.
	 */
	static Vec3f Closest(const AABB& aabb, const Vec3f& position)
	{
		Vec3f minPos = AABB::GetMin(aabb);
		Vec3f maxPos = AABB::GetMax(aabb);

		Vec3f closest = position;
		closest.x = (closest.x < minPos.x) ? minPos.x : closest.x;
		closest.y = (closest.y < minPos.y) ? minPos.y : closest.y;
		closest.z = (closest.z < minPos.z) ? minPos.z : closest.z;

		closest.x = (closest.x > maxPos.x) ? maxPos.x : closest.x;
		closest.y = (closest.y > maxPos.y) ? maxPos.y : closest.y;
		closest.z = (closest.z > maxPos.z) ? maxPos.z : closest.z;

		return closest;
	}


	/**
	 * @brief ��� �� ���� ������ �߽� ��ǥ�Դϴ�.
	 */
	Vec3f center;


	/**
	 * @brief ��� �� ���� ������ ũ���Դϴ�.
	 */
	Vec3f extents;
};


/**
 * @brief ��� ��(Sphere)�Դϴ�.
 */
struct Sphere
{
	/**
	 * @brief ��� ���� �⺻ �������Դϴ�.
	 */
	Sphere() = default;


	/**
	 * @brief ��� ���� �������Դϴ�.
	 *
	 * @param cc ��� ���� �߽� ��ǥ�Դϴ�.
	 * @param rr ��� ���� ������ �����Դϴ�.
	 */
	Sphere(const Vec3f & cc, float rr)
		: center(cc)
		, radius(rr) {}


	/**
	 * @brief ��� ���� ���� �������Դϴ�.
	 *
	 * @param instance ���� ������Ƽ�� ������ �ν��Ͻ��Դϴ�.
	 */
	Sphere(Sphere&& instance) noexcept
		: center(instance.center)
		, radius(instance.radius) {}


	/**
	 * @brief ��� ���� ���� �������Դϴ�.
	 *
	 * @param instance ���� ������Ƽ�� ������ �ν��Ͻ��Դϴ�.
	 */
	Sphere(const Sphere& instance) noexcept
		: center(instance.center)
		, radius(instance.radius) {}


	/**
	 * @brief ��� ���� ���� �������Դϴ�.
	 *
	 * @param instance ���� ������Ƽ�� ������ �ν��Ͻ��Դϴ�.
	 *
	 * @return ������ ��ü�� �����ڸ� ��ȯ�մϴ�.
	 */
	Sphere& operator=(Sphere&& instance) noexcept
	{
		if (this == &instance) return *this;

		center = instance.center;
		radius = instance.radius;

		return *this;
	}


	/**
	 * @brief ��� ���� ���� �������Դϴ�.
	 *
	 * @param instance ���� ������Ƽ�� ������ �ν��Ͻ��Դϴ�.
	 *
	 * @return ������ ��ü�� �����ڸ� ��ȯ�մϴ�.
	 */
	Sphere& operator=(const Sphere& instance) noexcept
	{
		if (this == &instance) return *this;

		center = instance.center;
		radius = instance.radius;

		return *this;
	}


	/**
	 * @brief ��� ���� �߽� ��ǥ�Դϴ�.
	 */
	Vec3f center;


	/**
	 * @brief ��� ���� ������ �����Դϴ�.
	 */
	float radius;
};


/**
 * @brief �浹 ó���� �����մϴ�.
 * 
 * @note �� Ŭ������ ��� ��� ������ �޼���� ����(static) Ÿ���Դϴ�.
 */
class Collision
{
public:
	/**
	 * @brief ��� ���� ��� �� ������ �浹 ���θ� �˻��մϴ�.
	 * 
	 * @param sphere0 �浿 ���θ� �˻��� ��� ���Դϴ�.
	 * @param sphere1 �浹 ó���� �˻��� �� �ٸ� ���Դϴ�.
	 * 
	 * @return ��� ���� ��� �� ������ �浹�� �����Ǹ� true, �׷��� ������ false�� ��ȯ�մϴ�.
	 */
	static bool SphereToSphere(const Sphere& sphere0, const Sphere& sphere1)
	{
		float lengthSq = Vec3f::LengthSq(sphere0.center - sphere1.center);
		float sumRadius = (sphere0.radius + sphere1.radius);

		return lengthSq <= (sumRadius * sumRadius);
	}
};