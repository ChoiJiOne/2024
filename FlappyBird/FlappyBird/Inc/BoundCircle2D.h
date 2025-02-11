#pragma once

#include "Vec2.h"

#include "IBound2D.h"


/**
 * @brief 2D ��� ���Դϴ�.
 */
class BoundCircle2D : public IBound2D
{
public:
	/**
	 * @brief 2D ��� ���� �⺻ �������Դϴ�.
	 */
	explicit BoundCircle2D() : IBound2D(EType::Circle) {}


	/**
	 * @brief 2D ��� ���� �������Դϴ�.
	 * 
	 * @param center ��� ���� �߽���ǥ�Դϴ�.
	 * @param radius ��� ���� ������ �����Դϴ�.
	 */
	explicit BoundCircle2D(const Vec2f& center, const float& radius) noexcept
		: IBound2D(EType::Circle)
		, center_(center)
		, radius_(radius) {}


	/**
	 * @brief 2D ��� ���� ���� �������Դϴ�.
	 * 
	 * @param instance ���縦 ������ �ν��Ͻ��Դϴ�.
	 */
	explicit BoundCircle2D(BoundCircle2D&& instance) noexcept
		: IBound2D(instance)
		, center_(instance.center_)
		, radius_(instance.radius_) {}


	/**
	 * @brief 2D ��� ���� ���� �������Դϴ�.
	 *
	 * @param instance ���縦 ������ �ν��Ͻ��Դϴ�.
	 */
	explicit BoundCircle2D(const BoundCircle2D& instance) noexcept
		: IBound2D(instance)
		, center_(instance.center_)
		, radius_(instance.radius_) {}


	/**
	 * @brief 2D ��� ���� ���� �Ҹ����Դϴ�.
	 */
	virtual ~BoundCircle2D() {}


	/**
	 * @brief 2D ��� ���� ���� �������Դϴ�.
	 * 
	 * @param instance ���� �����ڸ� ������ �ν��Ͻ��Դϴ�.
	 * 
	 * @return ������ ������ ��ü�� �����ڸ� ��ȯ�մϴ�.
	 */
	BoundCircle2D& operator=(BoundCircle2D&& instance) noexcept
	{
		if (this == &instance) return *this;

		IBound2D::operator=(instance);

		center_ = instance.center_;
		radius_ = instance.radius_;

		return *this;
	}


	/**
	 * @brief 2D ��� ���� ���� �������Դϴ�.
	 *
	 * @param instance ���� �����ڸ� ������ �ν��Ͻ��Դϴ�.
	 *
	 * @return ������ ������ ��ü�� �����ڸ� ��ȯ�մϴ�.
	 */
	BoundCircle2D& operator=(const BoundCircle2D& instance) noexcept
	{
		if (this == &instance) return *this;

		IBound2D::operator=(instance);

		center_ = instance.center_;
		radius_ = instance.radius_;

		return *this;
	}
	

	/**
	 * @brief ��� ���� �߽��� �����մϴ�.
	 * 
	 * @param center ������ ��� ���� �߽��Դϴ�.
	 */
	void SetCenter(const Vec2f& center) { center_ = center; }


	/**
	 * @brief ��� ���� ������ ���̸� �����մϴ�.
	 * 
	 * @param radius ������ ��� ���� ������ �����Դϴ�.
	 */
	void SetRadius(const float& radius) { radius_ = radius; }


	/**
	 * @brief ��� ���� �߽� ��ǥ�� ����ϴ�.
	 * 
	 * @return ��� ���� �߽� ��ǥ�� ��ȯ�մϴ�.
	 */
	Vec2f GetCenter() { return center_; }


	/**
	 * @brief ��� ���� �߽� ��ǥ�� ����ϴ�.
	 *
	 * @return ��� ���� �߽� ��ǥ�� ��ȯ�մϴ�.
	 */
	const Vec2f& GetCenter() const { return center_; }


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
	 * @brief �ٸ� 2D ������ �浹�ϴ��� �˻��մϴ�.
	 *
	 * @param bound �浹 ���θ� �˻��� ��� �����Դϴ�.
	 *
	 * @return �ٸ� ��� ������ �浹�Ѵٸ� true, �׷��� ������ false�� ��ȯ�մϴ�.
	 */
	virtual bool Intersect(const IBound2D* bound) const override;


private:
	/**
	 * @brief ��� ���� �߽���ǥ�Դϴ�.
	 */
	Vec2f center_;


	/**
	 * @brief ��� ���� ������ ���Դϴ�.
	 */
	float radius_ = 0.0f;
};