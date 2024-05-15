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
	 * @brief ��� �� ���� ������ �߽� ��ǥ�Դϴ�.
	 */
	Vec3f center;


	/**
	 * @brief ��� �� ���� ������ ũ���Դϴ�.
	 */
	Vec3f extents;
};