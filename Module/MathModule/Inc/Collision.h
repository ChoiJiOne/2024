#pragma once

#include "Vec3.h"


/**
 * @brief 경계 축 정렬 상자(Axis aligned bounding box)입니다.
 */
struct AABB
{
	/**
	 * @brief 경계 축 정렬 상자의 기본 생성자입니다.
	 */
	AABB() = default;


	/**
	 * @brief 경계 축 정렬 상자의 생성자입니다.
	 *
	 * @param cc 경계 축 정렬 상자의 중심 좌표입니다.
	 * @param ee 경계 축 정렬 상자의 X/Y/Z 축 방향으로의 크기입니다.
	 */
	AABB(const Vec3f& cc, const Vec3f& ee)
		: center(cc)
		, extents(ee) {}


	/**
	 * @brief 경계 축 정렬 상자의 복사 생성자입니다.
	 *
	 * @param instance 내부 프로퍼티를 복사할 인스턴스입니다.
	 */
	AABB(AABB&& instance) noexcept
		: center(instance.center)
		, extents(instance.extents) {}


	/**
	 * @brief 경계 축 정렬 상자의 복사 생성자입니다.
	 *
	 * @param instance 내부 프로퍼티를 복사할 인스턴스입니다.
	 */
	AABB(const AABB& instance) noexcept
		: center(instance.center)
		, extents(instance.extents) {}


	/**
	 * @brief 경계 축 정렬 상자의 대입 연산자입니다.
	 *
	 * @param instance 내부 프로퍼티를 복사할 인스턴스입니다.
	 *
	 * @return 대입한 객체의 참조자를 반환합니다.
	 */
	AABB& operator=(AABB&& instance) noexcept
	{
		if (this == &instance) return *this;

		center = instance.center;
		extents = instance.extents;

		return *this;
	}


	/**
	 * @brief 경계 축 정렬 상자의 대입 연산자입니다.
	 *
	 * @param instance 내부 프로퍼티를 복사할 인스턴스입니다.
	 *
	 * @return 대입한 객체의 참조자를 반환합니다.
	 */
	AABB& operator=(const AABB& instance) noexcept
	{
		if (this == &instance) return *this;

		center = instance.center;
		extents = instance.extents;

		return *this;
	}


	/**
	 * @brief 경계 영역의 최소값을 얻습니다.
	 * 
	 * @param instance 경계 영역의 최소값을 얻을 인스턴스입니다.
	 *
	 * @return 경계 영역의 최소값을 반환합니다.
	 */
	static Vec3f GetMin(const AABB& aabb) { return aabb.center - aabb.extents * 0.5f; }


	/**
	 * @brief 경계 영역의 최댓값을 얻습니다.
	 *
	 * @param instance 경계 영역의 최소값을 얻을 인스턴스입니다.
	 * 
	 * @return 경계 영역의 최댓값을 반환합니다.
	 */
	static Vec3f GetMax(const AABB& aabb) { return aabb.center + aabb.extents * 0.5f; }


	/**
	 * @brief 경계 영역 내의 가장 가까운 점을 찾습니다.
	 * 
	 * @param aabb 가까운 점을 찾을 경계 영역입니다.
	 * @param position 가까운 점입니다.
	 * 
	 * @return 경계 영역 내의 가장 가까운 점을 반환합니다.
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
	 * @brief 경계 축 정렬 상자의 중심 좌표입니다.
	 */
	Vec3f center;


	/**
	 * @brief 경계 축 정렬 상자의 크기입니다.
	 */
	Vec3f extents;
};


/**
 * @brief 경계 구(Sphere)입니다.
 */
struct Sphere
{
	/**
	 * @brief 경계 구의 기본 생성자입니다.
	 */
	Sphere() = default;


	/**
	 * @brief 경계 구의 생성자입니다.
	 *
	 * @param cc 경계 구의 중심 좌표입니다.
	 * @param rr 경계 구의 반지름 길이입니다.
	 */
	Sphere(const Vec3f & cc, float rr)
		: center(cc)
		, radius(rr) {}


	/**
	 * @brief 경계 구의 복사 생성자입니다.
	 *
	 * @param instance 내부 프로퍼티를 복사할 인스턴스입니다.
	 */
	Sphere(Sphere&& instance) noexcept
		: center(instance.center)
		, radius(instance.radius) {}


	/**
	 * @brief 경계 구의 복사 생성자입니다.
	 *
	 * @param instance 내부 프로퍼티를 복사할 인스턴스입니다.
	 */
	Sphere(const Sphere& instance) noexcept
		: center(instance.center)
		, radius(instance.radius) {}


	/**
	 * @brief 경계 구의 대입 연산자입니다.
	 *
	 * @param instance 내부 프로퍼티를 복사할 인스턴스입니다.
	 *
	 * @return 대입한 객체의 참조자를 반환합니다.
	 */
	Sphere& operator=(Sphere&& instance) noexcept
	{
		if (this == &instance) return *this;

		center = instance.center;
		radius = instance.radius;

		return *this;
	}


	/**
	 * @brief 경계 구의 대입 연산자입니다.
	 *
	 * @param instance 내부 프로퍼티를 복사할 인스턴스입니다.
	 *
	 * @return 대입한 객체의 참조자를 반환합니다.
	 */
	Sphere& operator=(const Sphere& instance) noexcept
	{
		if (this == &instance) return *this;

		center = instance.center;
		radius = instance.radius;

		return *this;
	}


	/**
	 * @brief 경계 구의 중심 좌표입니다.
	 */
	Vec3f center;


	/**
	 * @brief 경계 구의 반지름 길이입니다.
	 */
	float radius;
};


/**
 * @brief 충돌 처리를 수행합니다.
 * 
 * @note 이 클래스의 모든 멤버 변수와 메서드는 정적(static) 타입입니다.
 */
class Collision
{
public:
	/**
	 * @brief 경계 구와 경계 구 사이의 충돌 여부를 검사합니다.
	 * 
	 * @param sphere0 충동 여부를 검사할 경계 구입니다.
	 * @param sphere1 충돌 처리를 검사할 또 다른 구입니다.
	 * 
	 * @return 경계 구와 경계 구 사이의 충돌이 감지되면 true, 그렇지 않으면 false를 반환합니다.
	 */
	static bool SphereToSphere(const Sphere& sphere0, const Sphere& sphere1)
	{
		float lengthSq = Vec3f::LengthSq(sphere0.center - sphere1.center);
		float sumRadius = (sphere0.radius + sphere1.radius);

		return lengthSq <= (sumRadius * sumRadius);
	}
};