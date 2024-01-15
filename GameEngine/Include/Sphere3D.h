#pragma once

#include "Vector3.h"


/**
 * @brief ��� ��(Sphere)�Դϴ�.
 */
class Sphere3D
{
public:
	/**
	 * @brief ��� ���� �⺻ �������Դϴ�.
	 */
	Sphere3D() = default;


	/**
	 * @brief ��� ���� �������Դϴ�.
	 * 
	 * @param center ��� ���� �߽� ��ǥ�Դϴ�.
	 * @param radius ��� ���� ������ �����Դϴ�.
	 */
	Sphere3D(const Vector3f& center, float radius)
		: center_(center)
		, radius_(radius) {}


	/**
	 * @brief ��� ���� ���� �������Դϴ�.
	 * 
	 * @param instance ���� ������Ƽ�� ������ �ν��Ͻ��Դϴ�.
	 */
	Sphere3D(Sphere3D&& instance) noexcept
		: center_(instance.center_)
		, radius_(instance.radius_) {}


	/**
	 * @brief ��� ���� ���� �������Դϴ�.
	 *
	 * @param instance ���� ������Ƽ�� ������ �ν��Ͻ��Դϴ�.
	 */
	Sphere3D(const Sphere3D& instance) noexcept
		: center_(instance.center_)
		, radius_(instance.radius_) {}


	/**
	 * @brief ��� ���� ���� �Ҹ����Դϴ�.
	 */
	virtual ~Sphere3D() {}


	/**
	 * @brief ��� ���� ���� �������Դϴ�.
	 * 
	 * @param instance ���� ������Ƽ�� ������ �ν��Ͻ��Դϴ�.
	 * 
	 * @return ������ ��ü�� �����ڸ� ��ȯ�մϴ�.
	 */
	Sphere3D& operator=(Sphere3D&& instance) noexcept
	{
		if (this == &instance) return *this;

		center_ = instance.center_;
		radius_ = instance.radius_;

		return *this;
	}


	/**
	 * @brief ��� ���� ���� �������Դϴ�.
	 *
	 * @param instance ���� ������Ƽ�� ������ �ν��Ͻ��Դϴ�.
	 *
	 * @return ������ ��ü�� �����ڸ� ��ȯ�մϴ�.
	 */
	Sphere3D& operator=(const Sphere3D& instance) noexcept
	{
		if (this == &instance) return *this;

		center_ = instance.center_;
		radius_ = instance.radius_;

		return *this;
	}


	/**
	 * @brief ��� ���� �߽� ��ǥ�� ����ϴ�.
	 *
	 * @return ��� ���� �߽� ��ǥ�� ��ȯ�մϴ�.
	 */
	Vector3f GetCenter() { return center_; }


	/**
	 * @brief ��� ���� �߽� ��ǥ�� ����ϴ�.
	 *
	 * @return ��� ���� �߽� ��ǥ�� ��ȯ�մϴ�.
	 */
	const Vector3f& GetCenter() const { return center_; }


	/**
	 * @brief ��� ���� ������ ���̸� ����ϴ�.
	 * 
	 * @return ��� ���� ������ ���̸� ��ȯ�մϴ�.
	 */
	float GetRadius() { return radius_; }


	/**
	 * @brief ��� ���� ������ ���̸� ����ϴ�.
	 * 
	 * @return ��� ���� ������ ���̸� ��ȯ�մϴ�.
	 */
	const float& GetRadius() const { return radius_; }


	/**
	 * @brief ��� ���� �߽� ��ǥ�� �����մϴ�.
	 *
	 * @param center ������ ��� ���� �߽���ǥ�Դϴ�.
	 */
	void SetCenter(const Vector3f& center) { center_ = center; }


	/**
	 * @brief ��� ���� ������ ���̸� �����մϴ�.
	 *
	 * @param radius ������ ��� ���� ������ �����Դϴ�.
	 */
	void SetRadius(const float& radius) { radius_ = radius; }


	/**
	 * @brief �ٸ� ��� ���� �浹�ϴ��� Ȯ���մϴ�.
	 * 
	 * @param sphere �浹�ϴ��� Ȯ���� ��ü�Դϴ�.
	 * 
	 * @return �ٸ� ��ü�� �浹�Ѵٸ� true, �׷��� ������ false�� ��ȯ�մϴ�.
	 */
	bool Intersect(const Sphere3D& sphere) const;


private:
	/**
	 * @brief ��� ���� �߽� ��ǥ�Դϴ�.
	 */
	Vector3f center_;


	/**
	 * @brief ��� ���� ������ �����Դϴ�.
	 */
	float radius_;
};