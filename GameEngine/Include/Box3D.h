#pragma once

#include "IShape3D.h"
#include "Vector3.h"


/**
 * @brief ��� ���� ���ĵ� ����(Box)�Դϴ�.
 */
class Box3D : public IShape3D
{
public:
	/**
	 * @brief ��� ���� ���ĵ� ������ �⺻ �������Դϴ�.
	 */
	Box3D() = default;


	/**
	 * @brief ��� ���� ���ĵ� ������ �������Դϴ�.
	 * 
	 * @param center ��� ���� ���ĵ� ������ �߽� ��ǥ�Դϴ�.
	 * @param extents ��� ���� ���ĵ� ������ X/Y/Z �� ���������� ũ���Դϴ�.
	 */
	Box3D(const Vector3f& center, const Vector3f& extents)
		: center_(center)
		, extents_(extents) {}


	/**
	 * @brief ��� ���� ���ĵ� ������ ���� �������Դϴ�.
	 * 
	 * @param instance ���� ������Ƽ�� ������ �ν��Ͻ��Դϴ�.
	 */
	Box3D(Box3D&& instance) noexcept
		: center_(instance.center_)
		, extents_(instance.extents_) {}


	/**
	 * @brief ��� ���� ���ĵ� ������ ���� �������Դϴ�.
	 *
	 * @param instance ���� ������Ƽ�� ������ �ν��Ͻ��Դϴ�.
	 */
	Box3D(const Box3D& instance) noexcept
		: center_(instance.center_)
		, extents_(instance.extents_) {}

	
	/**
	 * @brief ��� ���� ���ĵ� ������ ���� �Ҹ����Դϴ�.
	 */
	virtual ~Box3D() {}


	/**
	 * @brief ��� ���� ���ĵ� ������ ���� �������Դϴ�.
	 * 
	 * @param instance ���� ������Ƽ�� ������ �ν��Ͻ��Դϴ�.
	 * 
	 * @return ������ ��ü�� �����ڸ� ��ȯ�մϴ�.
	 */
	Box3D& operator=(Box3D&& instance) noexcept
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
	Box3D& operator=(const Box3D& instance) noexcept
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
	Vector3f GetCenter() { return center_; }


	/**
	 * @brief ��� ���� ���ĵ� ������ �߽� ��ǥ�� ����ϴ�.
	 *
	 * @return ��� ���� ���ĵ� ������ �߽� ��ǥ�� ��ȯ�մϴ�.
	 */
	const Vector3f& GetCenter() const { return center_; }


	/**
	 * @brief ��� ���� ���ĵ� ������ X/Y/Z �� ���������� ũ�⸦ ����ϴ�.
	 * 
	 * @return ��� ���� ���ĵ� ������ X/Y/Z �� ���������� ũ�⸦ ��ȯ�մϴ�.
	 */
	Vector3f GetExtents() { return extents_; }


	/**
	 * @brief ��� ���� ���ĵ� ������ X/Y/Z �� ���������� ũ�⸦ ����ϴ�.
	 *
	 * @return ��� ���� ���ĵ� ������ X/Y/Z �� ���������� ũ�⸦ ��ȯ�մϴ�.
	 */
	const Vector3f& GetExtents() const { return extents_; }


	/**
	 * @brief ��� ������ �ּҰ��� ����ϴ�.
	 * 
	 * @return ��� ������ �ּҰ��� ��ȯ�մϴ�.
	 */
	Vector3f GetMinPosition() const { return center_ - extents_; }


	/**
	 * @brief ��� ������ �ִ��� ����ϴ�.
	 * 
	 * @return ��� ������ �ִ��� ��ȯ�մϴ�.
	 */
	Vector3f GetMaxPosition() const { return center_ + extents_; }


	/**
	 * @brief ��� ���� ���ĵ� ������ �߽� ��ǥ�� �����մϴ�.
	 * 
	 * @param center ������ ��� ���� ���ĵ� ������ �߽���ǥ�Դϴ�.
	 */
	void SetCenter(const Vector3f& center) { center_ = center; }


	/**
	 * @brief ��� ���� ���ĵ� ������ ũ�⸦ �����մϴ�.
	 * 
	 * @param extents ������ ��� ���� ���ĵ� ������ ũ���Դϴ�.
	 */
	void SetExtents(const Vector3f& extents) { extents_ = extents; }


	/**
	 * @brief ��� ���� ���ĵ� ������ ���� ������ ���� ����ϴ�.
	 * 
	 * @return ��� ���� ���ĵ� ������ ���� ������ ���� ��ȯ�մϴ�.
	 */
	virtual EType GetType() const override { return EType::Box; }


	/**
	 * @brief �ٸ� 3D ���°� ����Ǵ��� Ȯ���մϴ�.
	 *
	 * @param shape ������ Ȯ���� 3D ���� �ν��Ͻ��Դϴ�.
	 *
	 * @return �ٸ� 3D ���°� ����ȴٸ� true, �׷��� ������ false�� ��ȯ�մϴ�.
	 */
	virtual bool Intersect(const IShape3D* shape) const override;

	
private:
	/**
	 * @brief �ٸ� ��� �� ���� ���ڿ� �浹�ϴ��� Ȯ���մϴ�.
	 * 
	 * @param shape ������ Ȯ���� 3D ���� �ν��Ͻ��Դϴ�.
	 * 
	 * @return �ٸ� ��� �� ���� ���ڰ� ����ȴٸ� true, �׷��� ������ false�� ��ȯ�մϴ�.
	 */
	bool IntersectBox3D(const IShape3D* shape) const;


	/**
	 * @brief �ٸ� �� ������ �浹�ϴ��� Ȯ���մϴ�.
	 * 
	 * @param shape ������ Ȯ���� 3D ���� �ν��Ͻ��Դϴ�.
	 *
	 * @return �ٸ� �� ������ ����ȴٸ� true, �׷��� ������ false�� ��ȯ�մϴ�.
	 */
	bool IntersectSphere3D(const IShape3D* shape) const;


private:
	/**
	 * @brief ��� ���� ���ĵ� ������ �߽� ��ǥ�Դϴ�.
	 */
	Vector3f center_;


	/**
	 * @brief ��� ���� ���ĵ� ������ ũ���Դϴ�.
	 */
	Vector3f extents_;
};