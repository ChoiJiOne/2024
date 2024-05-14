#pragma once

#include "IBoundingVolume.h"
#include "Vec3.h"


/**
 * @brief ��� ��(Sphere)�Դϴ�.
 */
class BoundingSphere3D : public IBoundingVolume
{
public:
	/**
	 * @brief ��� ���� �⺻ �������Դϴ�.
	 */
	BoundingSphere3D() = default;


	/**
	 * @brief ��� ���� �������Դϴ�.
	 *
	 * @param center ��� ���� �߽� ��ǥ�Դϴ�.
	 * @param radius ��� ���� ������ �����Դϴ�.
	 */
	BoundingSphere3D(const Vec3f& center, float radius)
		: center_(center)
		, radius_(radius) {}


	/**
	 * @brief ��� ���� ���� �������Դϴ�.
	 *
	 * @param instance ���� ������Ƽ�� ������ �ν��Ͻ��Դϴ�.
	 */
	BoundingSphere3D(BoundingSphere3D&& instance) noexcept
		: center_(instance.center_)
		, radius_(instance.radius_) {}


	/**
	 * @brief ��� ���� ���� �������Դϴ�.
	 *
	 * @param instance ���� ������Ƽ�� ������ �ν��Ͻ��Դϴ�.
	 */
	BoundingSphere3D(const BoundingSphere3D& instance) noexcept
		: center_(instance.center_)
		, radius_(instance.radius_) {}


	/**
	 * @brief ��� ���� ���� �Ҹ����Դϴ�.
	 */
	virtual ~BoundingSphere3D() {}


	/**
	 * @brief ��� ���� ���� �������Դϴ�.
	 *
	 * @param instance ���� ������Ƽ�� ������ �ν��Ͻ��Դϴ�.
	 *
	 * @return ������ ��ü�� �����ڸ� ��ȯ�մϴ�.
	 */
	BoundingSphere3D& operator=(BoundingSphere3D&& instance) noexcept
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
	BoundingSphere3D& operator=(const BoundingSphere3D& instance) noexcept
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
	const Vec3f& GetCenter() const { return center_; }


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
	void SetCenter(const Vec3f& center) { center_ = center; }


	/**
	 * @brief ��� ���� ������ ���̸� �����մϴ�.
	 *
	 * @param radius ������ ��� ���� ������ �����Դϴ�.
	 */
	void SetRadius(const float& radius) { radius_ = radius; }


	/**
	 * @brief ��� ���� ���� ������ ���� ����ϴ�.
	 *
	 * @return ��� ���� ���� ������ ���� ��ȯ�մϴ�.
	 */
	virtual EType GetType() const override { return EType::SPHERE; }


	/**
	 * @brief �ٸ� 3D ��� ������ �浹�ϴ��� Ȯ���մϴ�.
	 *
	 * @param boundingVolume ������ Ȯ���� 3D ��� �����Դϴ�.
	 *
	 * @return �ٸ� 3D ���� �浹�Ѵٸ� true, �׷��� ������ false�� ��ȯ�մϴ�.
	 */
	virtual bool Intersect(const IBoundingVolume* boundingVolume) const override;


private:
	/**
	 * @brief �ٸ� ��� �� ���� ���ڿ� �浹�ϴ��� Ȯ���մϴ�.
	 *
	 * @param boundingVolume ������ Ȯ���� 3D ��� �����Դϴ�.
	 *
	 * @return �ٸ� ��� �� ���� ���ڿ� �浹�Ѵٸ� true, �׷��� ������ false�� ��ȯ�մϴ�.
	 */
	bool IntersectBoundingBox3D(const IBoundingVolume* boundingVolume) const;


	/**
	 * @brief �ٸ� �� ������ �浹�ϴ��� Ȯ���մϴ�.
	 *
	 * @param boundingVolume ������ Ȯ���� 3D ��� �����Դϴ�.
	 *
	 * @return �ٸ� �� ������ �浹�Ѵٸ� true, �׷��� ������ false�� ��ȯ�մϴ�.
	 */
	bool IntersectBoundingSphere3D(const IBoundingVolume* boundingVolume) const;


private:
	/**
	 * @brief ��� ���� �߽� ��ǥ�Դϴ�.
	 */
	Vec3f center_;


	/**
	 * @brief ��� ���� ������ �����Դϴ�.
	 */
	float radius_;
};