#pragma once

#include "Vec2.h"

#include "IBound2D.h"


/**
 * @brief 2D �� ���� ��� �����Դϴ�.
 */
class BoundBox2D : public IBound2D
{
public:
	/**
	 * @brief 2D �� ���� ��� ������ �⺻ �������Դϴ�.
	 */
	explicit BoundBox2D() : IBound2D(EType::Box) {}


	/**
	 * @brief 2D �� ���� ��� ������ �������Դϴ�.
	 * 
	 * @param minPosition �� ���� ��� ������ �ּҰ��Դϴ�.
	 * @param maxPosition �� ���� ��� ������ �ִ��Դϴ�.
	 */
	explicit BoundBox2D(const Vec2f& minPosition, const Vec2f& maxPosition);


	/**
	 * @brief 2D �� ���� ��� ������ �������Դϴ�.
	 * 
	 * @param center �� ���� ��� ������ �߽���ǥ�Դϴ�.
	 * @param width �� ���� ��� ������ ���� ũ���Դϴ�.
	 * @param height �� ���� ��� ������ ���� ũ���Դϴ�.
	 */
	explicit BoundBox2D(const Vec2f& center, const float& width, const float& height);


	/**
	 * @brief 2D �� ���� ��� ������ ���� �������Դϴ�.
	 * 
	 * @param instance ���縦 ������ �ν��Ͻ��Դϴ�.
	 */
	explicit BoundBox2D(BoundBox2D&& instance) noexcept
		: IBound2D(instance)
		, center_(instance.center_)
		, width_(instance.width_)
		, height_(instance.height_)
		, minPosition_(instance.minPosition_)
		, maxPosition_(instance.maxPosition_) {}


	/**
	 * @brief 2D �� ���� ��� ������ ���� �������Դϴ�.
	 *
	 * @param instance ���縦 ������ �ν��Ͻ��Դϴ�.
	 */
	explicit BoundBox2D(const BoundBox2D& instance) noexcept
		: IBound2D(instance)
		, center_(instance.center_)
		, width_(instance.width_)
		, height_(instance.height_)
		, minPosition_(instance.minPosition_)
		, maxPosition_(instance.maxPosition_) {}


	/**
	 * @brief 2D �� ���� ��� ������ ���� �Ҹ����Դϴ�.
	 */
	virtual ~BoundBox2D() {}


	/**
	 * @brief 2D �� ���� ��� ������ ���� �������Դϴ�.
	 * 
	 * @param instance ���� ������ ������ �ν��Ͻ��Դϴ�.
	 * 
	 * @return ������ ������ ��ü�� �����ڸ� ��ȯ�մϴ�.
	 */
	BoundBox2D& operator=(BoundBox2D&& instance) noexcept
	{
		if (this == &instance) return *this;

		IBound2D::operator=(instance);

		center_ = instance.center_;
		width_ = instance.width_;
		height_ = instance.height_;
		minPosition_ = instance.minPosition_;
		maxPosition_ = instance.maxPosition_;

		return *this;
	}


	/**
	 * @brief 2D �� ���� ��� ������ ���� �������Դϴ�.
	 *
	 * @param instance ���� ������ ������ �ν��Ͻ��Դϴ�.
	 *
	 * @return ������ ������ ��ü�� �����ڸ� ��ȯ�մϴ�.
	 */
	BoundBox2D& operator=(const BoundBox2D& instance) noexcept
	{
		if (this == &instance) return *this;

		IBound2D::operator=(instance);

		center_ = instance.center_;
		width_ = instance.width_;
		height_ = instance.height_;
		minPosition_ = instance.minPosition_;
		maxPosition_ = instance.maxPosition_;

		return *this;
	}


	/**
	 * @brief 2D ��� ���� ������ ������Ƽ�� �����մϴ�.
	 *
	 * @param minPosition �� ���� ��� ������ �ּ� ��ǥ�Դϴ�.
	 * @param maxPosition �� ���� ��� ������ �ִ� ��ǥ�Դϴ�.
	 */
	void SetProperty(const Vec2f& minPosition, const Vec2f& maxPosition);


	/**
	 * @brief 2D ��� ���� ������ ������Ƽ�� �����մϴ�.
	 *
	 * @param center �� ���� ��� ������ �߽� ��ǥ�Դϴ�.
	 * @param width �� ���� ��� ������ ���� ũ���Դϴ�.
	 * @param height �� ���� ��� ������ ���� ũ���Դϴ�.
	 */
	void SetProperty(const Vec2f& center, const float& width, const float& height);


	/**
	 * @brief 2D ��� ���� ������ �߽��� �����մϴ�.
	 * 
	 * @param center �� ���� ��� ������ �߽��Դϴ�.
	 */
	void SetCenter(const Vec2f& center);


	/**
	 * @brief 2D ��� ���� ������ �߽��� ����ϴ�.
	 * 
	 * @return 2D ��� ���� ������ �߽��� ��ȯ�մϴ�.
	 */
	Vec2f GetCenter() { return center_; }


	/**
	 * @brief 2D ��� ���� ������ �߽��� ����ϴ�.
	 *
	 * @return 2D ��� ���� ������ �߽��� ��ȯ�մϴ�.
	 */
	const Vec2f& GetCenter() const { return center_; }
	

	/**
	 * @brief 2D ��� ���� ������ ���� ũ�⸦ ����ϴ�.
	 * 
	 * @return 2D ��� ���� ������ ���� ũ�⸦ ��ȯ�մϴ�.
	 */
	float GetWidth() { return width_; }


	/**
	 * @brief 2D ��� ���� ������ ���� ũ�⸦ ����ϴ�.
	 *
	 * @return 2D ��� ���� ������ ���� ũ�⸦ ��ȯ�մϴ�.
	 */
	const float& GetWidth() const { return width_; }


	/**
	 * @brief 2D ��� ���� ������ ���� ũ�⸦ ����ϴ�.
	 *
	 * @return 2D ��� ���� ������ ���� ũ�⸦ ��ȯ�մϴ�.
	 */
	float GetHeight() { return height_; }


	/**
	 * @brief 2D ��� ���� ������ ���� ũ�⸦ ����ϴ�.
	 *
	 * @return 2D ��� ���� ������ ���� ũ�⸦ ��ȯ�մϴ�.
	 */
	const float& GetHeight() const { return height_; }


	/**
	 * @brief 2D ��� ������ �ּҰ��� ����ϴ�.
	 * 
	 * @return 2D ��� ������ �ּҰ��� ��ȯ�մϴ�.
	 */
	Vec2f GetMinPosition() { return minPosition_; }


	/**
	 * @brief 2D ��� ������ �ּҰ��� ����ϴ�.
	 *
	 * @return 2D ��� ������ �ּҰ��� ��ȯ�մϴ�.
	 */
	const Vec2f& GetMinPosition() const { return minPosition_; }


	/**
	 * @brief 2D ��� ������ �ִ밪�� ����ϴ�.
	 *
	 * @return 2D ��� ������ �ִ밪�� ��ȯ�մϴ�.
	 */
	Vec2f GetMaxPosition() { return maxPosition_; }


	/**
	 * @brief 2D ��� ������ �ִ밪�� ����ϴ�.
	 *
	 * @return 2D ��� ������ �ִ밪�� ��ȯ�մϴ�.
	 */
	const Vec2f& GetMaxPosition() const { return maxPosition_; }


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
	 * @brief ��� ������ �߽� ��ǥ�� ����/���� ũ��κ��� �ִ�/�ּҰ��� ����մϴ�.
	 * 
	 * @param center ��� ������ �߽���ǥ�Դϴ�.
	 * @param width ��� ������ ���� ũ���Դϴ�.
	 * @param height ��� ������ ���� ũ���Դϴ�.
	 * @param outMinPosition ��� ������ �ּҰ��Դϴ�.
	 * @param outMaxPosition ��� ������ �ִ밪�Դϴ�.
	 */
	void ComputeBoundBoxProperties(const Vec2f& center, const float& width, const float& height, Vec2f& outMinPosition, Vec2f& outMaxPosition) const;
	

	/**
	 * @brief ��� ������ �ִ�/�ּҰ����κ��� �߽� ��ǥ�� ����/���� ũ�⸦ ����մϴ�.
	 * 
	 * @param minPosition ��� ������ �ּҰ��Դϴ�.
	 * @param maxPosition ��� ������ �ִ밪�Դϴ�.
	 * @param outCenter ��� ������ �߽���ǥ�Դϴ�.
	 * @param outWidth ��� ������ ���� ũ���Դϴ�.
	 * @param outHeight ��� ������ ���� ũ���Դϴ�.
	 */
	void ComputeBoundBoxProperties(const Vec2f& minPosition, const Vec2f& maxPosition, Vec2f& outCenter, float& outWidth, float& outHeight) const;


private:
	/**
	 * @brief ��� ������ �߽� ��ǥ�Դϴ�.
	 */
	Vec2f center_;


	/**
	 * @brief ��� ������ ���� ũ���Դϴ�.
	 */
	float width_ = 0.0f;


	/**
	 * @brief ��� ������ ���� ũ���Դϴ�.
	 */
	float height_ = 0.0f;


	/**
	 * @brief ��� ������ �ּҰ��Դϴ�.
	 */
	Vec2f minPosition_;


	/**
	 * @brief ��� ������ �ִ��Դϴ�.
	 */
	Vec2f maxPosition_;
};