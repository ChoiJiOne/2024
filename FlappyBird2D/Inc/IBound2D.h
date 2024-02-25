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
	 * @brief ��� ������ �����Դϴ�.
	 */
	EType type_ = EType::None;
};