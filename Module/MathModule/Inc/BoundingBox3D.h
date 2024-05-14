#pragma once

#include "IBoundingVolume.h"
#include "Vec3.h"


/**
 * @brief ��� ���� ���ĵ� ����(Box)�Դϴ�.
 */
class BoundingBox3D : public IBoundingVolume
{
public:
	/**
	 * @brief ��� ���� ���ĵ� ������ �⺻ �������Դϴ�.
	 */
	BoundingBox3D() = default;


	/**
	 * @brief ��� ���� ���ĵ� ������ �������Դϴ�.
	 *
	 * @param center ��� ���� ���ĵ� ������ �߽� ��ǥ�Դϴ�.
	 * @param extents ��� ���� ���ĵ� ������ X/Y/Z �� ���������� ũ���Դϴ�.
	 */
	BoundingBox3D(const Vec3f& center, const Vec3f& extents)
		: center_(center)
		, extents_(extents) {}


	/**
	 * @brief ��� ���� ���ĵ� ������ ���� �������Դϴ�.
	 *
	 * @param instance ���� ������Ƽ�� ������ �ν��Ͻ��Դϴ�.
	 */
	BoundingBox3D(BoundingBox3D&& instance) noexcept
		: center_(instance.center_)
		, extents_(instance.extents_) {}


	/**
	 * @brief ��� ���� ���ĵ� ������ ���� �������Դϴ�.
	 *
	 * @param instance ���� ������Ƽ�� ������ �ν��Ͻ��Դϴ�.
	 */
	BoundingBox3D(const BoundingBox3D& instance) noexcept
		: center_(instance.center_)
		, extents_(instance.extents_) {}


	/**
	 * @brief ��� ���� ���ĵ� ������ ���� �Ҹ����Դϴ�.
	 */
	virtual ~BoundingBox3D() {}


	/**
	 * @brief ��� ���� ���ĵ� ������ ���� �������Դϴ�.
	 *
	 * @param instance ���� ������Ƽ�� ������ �ν��Ͻ��Դϴ�.
	 *
	 * @return ������ ��ü�� �����ڸ� ��ȯ�մϴ�.
	 */
	BoundingBox3D& operator=(BoundingBox3D&& instance) noexcept
	{
		if (this == &instance) return *this;

		center_ = instance.center_;
		extents_ = instance.extents_;

		return *this;
	}


	/**
	 * @brief ��� ���� ���ĵ� ������ ���� �������Դϴ�.
	 *
	 * @param instance ���� ������Ƽ�� ������ �ν��Ͻ��Դϴ�.
	 *
	 * @return ������ ��ü�� �����ڸ� ��ȯ�մϴ�.
	 */
	BoundingBox3D& operator=(const BoundingBox3D& instance) noexcept
	{
		if (this == &instance) return *this;

		center_ = instance.center_;
		extents_ = instance.extents_;

		return *this;
	}


	/**
	 * @brief ��� ���� ���ĵ� ������ �߽� ��ǥ�� ����ϴ�.
	 *
	 * @return ��� ���� ���ĵ� ������ �߽� ��ǥ�� ��ȯ�մϴ�.
	 */
	const Vec3f& GetCenter() const { return center_; }


	/**
	 * @brief ��� ���� ���ĵ� ������ X/Y/Z �� ���������� ũ�⸦ ����ϴ�.
	 *
	 * @return ��� ���� ���ĵ� ������ X/Y/Z �� ���������� ũ�⸦ ��ȯ�մϴ�.
	 */
	const Vec3f& GetExtents() const { return extents_; }


	/**
	 * @brief ��� ������ �ּҰ��� ����ϴ�.
	 *
	 * @return ��� ������ �ּҰ��� ��ȯ�մϴ�.
	 */
	Vec3f GetMinPosition() const { return center_ - extents_ * 0.5f; }


	/**
	 * @brief ��� ������ �ִ��� ����ϴ�.
	 *
	 * @return ��� ������ �ִ��� ��ȯ�մϴ�.
	 */
	Vec3f GetMaxPosition() const { return center_ + extents_ * 0.5f; }


	/**
	 * @brief ��� ���� ���ĵ� ������ �߽� ��ǥ�� �����մϴ�.
	 *
	 * @param center ������ ��� ���� ���ĵ� ������ �߽���ǥ�Դϴ�.
	 */
	void SetCenter(const Vec3f& center) { center_ = center; }


	/**
	 * @brief ��� ���� ���ĵ� ������ ũ�⸦ �����մϴ�.
	 *
	 * @param extents ������ ��� ���� ���ĵ� ������ ũ���Դϴ�.
	 */
	void SetExtents(const Vec3f& extents) { extents_ = extents; }


	/**
	 * @brief ��� ���� ���ĵ� ������ ���� ������ ���� ����ϴ�.
	 *
	 * @return ��� ���� ���ĵ� ������ ���� ������ ���� ��ȯ�մϴ�.
	 */
	virtual EType GetType() const override { return EType::BOX; }


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
	 * @brief ��� ���� ���ĵ� ������ �߽� ��ǥ�Դϴ�.
	 */
	Vec3f center_;


	/**
	 * @brief ��� ���� ���ĵ� ������ ũ���Դϴ�.
	 */
	Vec3f extents_;
};