#pragma once

#include "IShape3D.h"
#include "Vector3.h"


/**
 * @brief ��� ��(Sphere)�Դϴ�.
 */
class Sphere3D : public IShape3D
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
	 * @brief ��� ���� ���� ������ ���� ����ϴ�.
	 * 
	 * @return ��� ���� ���� ������ ���� ��ȯ�մϴ�.
	 */
	virtual EType GetType() const override { return IShape3D::EType::Sphere; }


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
	 * @brief ��� ���� �߽� ��ǥ�Դϴ�.
	 */
	Vector3f center_;


	/**
	 * @brief ��� ���� ������ �����Դϴ�.
	 */
	float radius_;
};