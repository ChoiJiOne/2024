#pragma once

#include <cstdint>


/**
 * @brief 2D ��� ���� �������̽��Դϴ�.
 */
class IBound2D
{
public:
	/**
	 * @brief 2D ��� ������ �����Դϴ�.
	 */
	enum class EType : int32_t
	{
		None   = 0x00,
		Box    = 0x01, // �� ���� ��� ���� (AABB)�Դϴ�.
		Circle = 0x02,
	};


public:
	/**
	 * @brief 2D ��� ������ �������Դϴ�.
	 *
	 * @param type 2D ��� ������ �����Դϴ�.
	 */
	explicit IBound2D(EType&& type) noexcept 
		: type_(type) {}
	
	
	/**
	 * @brief 2D ��� ������ �������Դϴ�.
	 * 
	 * @param type 2D ��� ������ �����Դϴ�.
	 */
	explicit IBound2D(const EType& type) noexcept 
		: type_(type) {}


	/**
	 * @brief 2D ��� ������ ���� �������Դϴ�.
	 * 
	 * @param instance ���縦 ������ �ν��Ͻ��Դϴ�.
	 */
	explicit IBound2D(IBound2D&& instance) noexcept 
		: type_(instance.type_) {}


	/**
	 * @brief 2D ��� ������ ���� �������Դϴ�.
	 *
	 * @param instance ���縦 ������ �ν��Ͻ��Դϴ�.
	 */
	explicit IBound2D(const IBound2D& instance) noexcept 
		: type_(instance.type_) {}


	/**
	 * @brief 2D ��� ������ ���� �Ҹ����Դϴ�.
	 */
	virtual ~IBound2D() {}


	/**
	 * @brief 2D ��� ������ ���� �������Դϴ�.
	 *
	 * @param instance ���� ������ ������ �ν��Ͻ��Դϴ�.
	 * 
	 * @return ������ ������ ��ü�� �����ڸ� ��ȯ�մϴ�.
	 */
	IBound2D& operator=(IBound2D&& instance) noexcept
	{
		if (this == &instance) return *this;

		type_ = instance.type_;

		return *this;
	}


	/**
	 * @brief 2D ��� ������ ���� �������Դϴ�.
	 * 
	 * @param instance ���� ������ ������ �ν��Ͻ��Դϴ�.
	 * 
	 * @return ������ ������ ��ü�� �����ڸ� ��ȯ�մϴ�.
	 */
	IBound2D& operator=(const IBound2D& instance) noexcept
	{
		if (this == &instance) return *this;

		type_ = instance.type_;

		return *this;
	}

	
	/**
	 * @brief 2D ��� ������ ������ ����ϴ�.
	 * 
	 * @return 2D ��� ������ ������ ��ȯ�մϴ�.
	 */
	EType GetType() { return type_; }


	/**
	 * @brief 2D ��� ������ ������ ����ϴ�.
	 *
	 * @return 2D ��� ������ ������ ��ȯ�մϴ�.
	 */
	const EType& GetType() const { return type_; }


	/**
	 * @brief �ٸ� 2D ������ �浹�ϴ��� �˻��մϴ�.
	 * 
	 * @param bound �浹 ���θ� �˻��� ��� �����Դϴ�.
	 * 
	 * @return �ٸ� ��� ������ �浹�Ѵٸ� true, �׷��� ������ false�� ��ȯ�մϴ�.
	 */
	virtual bool Intersect(const IBound2D* bound) const = 0;


protected:
	/**
	 * @brief ���� �ٸ� 2D ������ �浹�ϴ��� �˻��մϴ�.
	 * 
	 * @param bound0 �� 2D ������ �浹�ϴ��� �˻��� �����Դϴ�.
	 * @param bound1 �� 2D ������ �浹�ϴ��� �˻��� �� �ٸ� �����Դϴ�.
	 */
	bool IsIntersect(const IBound2D* bound0, const IBound2D* bound1) const;


private:
	/**
	 * @brief Box�� Box�� �浹�ϴ��� �˻��մϴ�.
	 * 
	 * @param bound0 �浹 ���θ� ������ Box �����Դϴ�.
	 * @param bound1 �浹 ���θ� ������ �� �ٸ� Box �����Դϴ�.
	 */
	bool IntersectBoxToBox(const IBound2D* bound0, const IBound2D* bound1) const;


	/**
	 * @brief Box�� Circle�� �浹�ϴ��� �˻��մϴ�.
	 *
	 * @param bound0 �浹 ���θ� ������ Box �����Դϴ�.
	 * @param bound1 �浹 ���θ� ������ �� �ٸ� Circle �����Դϴ�.
	 */
	bool IntersectBoxToCircle(const IBound2D* bound0, const IBound2D* bound1) const;


	/**
	 * @brief Circle�� Circle�� �浹�ϴ��� �˻��մϴ�.
	 *
	 * @param bound0 �浹 ���θ� ������ Circle �����Դϴ�.
	 * @param bound1 �浹 ���θ� ������ �� �ٸ� Circle �����Դϴ�.
	 */
	bool IntersectCircleToCircle(const IBound2D* bound0, const IBound2D* bound1) const;


protected:
	/**
	 * @brief ��� ������ �����Դϴ�.
	 */
	EType type_ = EType::None;
};