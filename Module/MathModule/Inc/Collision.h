#pragma once

#include "MathModule.h"
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
	 * @brief ��� ���� ���� ���� ����� ���� ã���ϴ�.
	 *
	 * @param sphere ����� ���� ã�� ��� �����Դϴ�.
	 * @param position ����� ���Դϴ�.
	 *
	 * @return ��� ���� ���� ���� ����� ���� ��ȯ�մϴ�.
	 */
	static Vec3f Closest(const Sphere& sphere, const Vec3f& position)
	{
		Vec3f direction = Vec3f::Normalize(position - sphere.center);
		return sphere.center + direction * sphere.radius;
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
 * @brief ����(Ray)�Դϴ�.
 */
struct Ray
{
	/**
	 * @brief ������ �⺻ �������Դϴ�.
	 */
	Ray() = default;


	/**
	 * @brief ������ �������Դϴ�.
	 *
	 * @param o ������ ��ġ�Դϴ�.
	 * @param d ������ �����Դϴ�.
	 */
	Ray(const Vec3f& o, const Vec3f& d)
		: origin(o)
		, direction(Vec3f::Normalize(d)) {}


	/**
	 * @brief ������ ���� �������Դϴ�.
	 *
	 * @param instance ���� ������Ƽ�� ������ �ν��Ͻ��Դϴ�.
	 */
	Ray(Ray&& instance) noexcept
		: origin(instance.origin)
		, direction(instance.direction) {}


	/**
	 * @brief ������ ���� �������Դϴ�.
	 *
	 * @param instance ���� ������Ƽ�� ������ �ν��Ͻ��Դϴ�.
	 */
	Ray(const Ray& instance) noexcept
		: origin(instance.origin)
		, direction(instance.direction) {}



	/**
	 * @brief ������ ���� �������Դϴ�.
	 *
	 * @param instance ���� ������Ƽ�� ������ �ν��Ͻ��Դϴ�.
	 *
	 * @return ������ ��ü�� �����ڸ� ��ȯ�մϴ�.
	 */
	Ray& operator=(Ray&& instance) noexcept
	{
		if (this == &instance) return *this;

		origin = instance.origin;
		direction = instance.direction;

		return *this;
	}


	/**
	 * @brief ������ ���� �������Դϴ�.
	 *
	 * @param instance ���� ������Ƽ�� ������ �ν��Ͻ��Դϴ�.
	 *
	 * @return ������ ��ü�� �����ڸ� ��ȯ�մϴ�.
	 */
	Ray& operator=(const Ray& instance) noexcept
	{
		if (this == &instance) return *this;

		origin = instance.origin;
		direction = instance.direction;

		return *this;
	}


	/**
	 * @brief ������ ��ġ�Դϴ�.
	 */
	Vec3f origin;


	/**
	 * @brief ������ �����Դϴ�.
	 */
	Vec3f direction;
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
	 * @param sphere0 �浹 ���θ� �˻��� ��� ���Դϴ�.
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


	/**
	 * @brief ��� ���� AABB ������ �浹 ���θ� �˻��մϴ�.
	 * 
	 * @param sphere �浹 ���θ� �˻��� ��� ���Դϴ�.
	 * @param aabb �浹 ���θ� �˻��� AABB�Դϴ�.
	 * 
	 * @return ��� ���� AABB ������ �浹�� �����Ǹ� true, �׷��� ������ false�� ��ȯ�մϴ�.
	 */
	static bool SphereToAABB(const Sphere& sphere, const AABB& aabb)
	{
		Vec3f closest = AABB::Closest(aabb, sphere.center);
		float distSq = Vec3f::LengthSq(sphere.center - closest);
		float radiusSq = sphere.radius * sphere.radius;

		return distSq <= radiusSq;
	}


	/**
	 * @brief AABB�� AABB ������ �浹 ���θ� �˻��մϴ�.
	 * 
	 * @param aabb0 �浹 ���θ� �˻��� AABB�Դϴ�.
	 * @param aabb1 �浹 ���θ� �˻��� �� �ٸ� AABB�Դϴ�.
	 */
	static bool AABBToAABB(const AABB& aabb0, const AABB& aabb1)
	{
		Vec3f minPos0 = AABB::GetMin(aabb0);
		Vec3f maxPos0 = AABB::GetMax(aabb0);

		Vec3f minPos1 = AABB::GetMin(aabb1);
		Vec3f maxPos1 = AABB::GetMax(aabb1);

		if (minPos0.x > maxPos1.x || maxPos0.x < minPos1.x)
		{
			return false;
		}

		if (minPos0.y > maxPos1.y || maxPos0.y < minPos1.y)
		{
			return false;
		}

		if (minPos0.z > maxPos1.z || maxPos0.z < minPos1.z)
		{
			return false;
		}

		return true;
	}


	/**
	 * @brief ��� ���� ������ �浹�ϴ��� Ȯ���մϴ�.
	 * 
	 * @param ray ��� ���� �浹�ϴ��� Ȯ���� �����Դϴ�.
	 * @param sphere ������ �浹�ϴ��� Ȯ���� ��� ���Դϴ�.
	 * 
	 * @return ��� ���� ������ �浹�Ѵٸ� true, �׷��� ������ false�� ��ȯ�մϴ�.
	 */
	static bool Raycast(const Ray& ray, const Sphere& sphere)
	{
		Vec3f e = sphere.center - ray.origin;
		
		float r2 = sphere.radius * sphere.radius;
		float e2 = Vec3f::Dot(e, e);
		float a = Vec3f::Dot(e, ray.direction);
		float a2 = a * a;
		float b2 = e2 - a2;
		float f = MathModule::Sqrt(MathModule::Abs(r2) - b2);
		float t = a - f;

		return r2 - (e2 - a2) >= 0.0f;
	}


	/**
	 * @brief AABB�� ������ �浹�ϴ��� Ȯ���մϴ�.
	 * 
	 * @param ray AABB�� �浹�ϴ��� Ȯ���� �����Դϴ�.
	 * @param aabb ������ �浹�ϴ��� Ȯ���� AABB�Դϴ�.
	 *
	 * @return AABB�� ������ �浹�Ѵٸ� true, �׷��� ������ false�� ��ȯ�մϴ�.
	 */
	static bool Raycast(const Ray& ray, const AABB& aabb)
	{
		Vec3f minPos = AABB::GetMin(aabb);
		Vec3f maxPos = AABB::GetMax(aabb);

		Vec3f direction = ray.direction;
		direction.x = MathModule::NearZero(direction.x) ? 0.00001f : direction.x;
		direction.y = MathModule::NearZero(direction.y) ? 0.00001f : direction.y;
		direction.z = MathModule::NearZero(direction.z) ? 0.00001f : direction.z;

		float t1 = (minPos.x - ray.origin.x) / direction.x;
		float t2 = (maxPos.x - ray.origin.x) / direction.x;
		float t3 = (minPos.y - ray.origin.y) / direction.y;
		float t4 = (maxPos.y - ray.origin.y) / direction.y;
		float t5 = (minPos.z - ray.origin.z) / direction.z;
		float t6 = (maxPos.z - ray.origin.z) / direction.z;

		float tmin = MathModule::Max(MathModule::Max(MathModule::Min(t1, t2), MathModule::Min(t3, t4)), MathModule::Min(t5, t6));
		float tmax = MathModule::Min(MathModule::Min(MathModule::Max(t1, t2), MathModule::Max(t3, t4)), MathModule::Max(t5, t6));

		return !((tmax < 0.0f || tmin > tmax));
	}
};