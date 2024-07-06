#pragma once

#include "GameMath.h"


namespace GameMaker
{
/**
 * @brief 2D ������Ʈ�� �浹 ���� �������̽��Դϴ�.
 */
struct ICollision2D
{
	/**
	 * @brief 2D �浹 ó�� ������ �����Դϴ�.
	 */
	enum class EType
	{
		NONE          = 0x00,
		POINT         = 0x01,
		LINE          = 0x02,
		CIRCLE        = 0x03,
		RECT          = 0x04, // AABB
		ORIENTED_RECT = 0x05, // OBB
	};


	/**
	 * @brief 2D ������Ʈ�� �浹 ���� �������̽��� ����Ʈ �������Դϴ�.
	 */
	ICollision2D() = default;


	/**
	 * @brief 2D ������Ʈ�� �浹 ���� �������̽��� ���� �Ҹ����Դϴ�.
	 */
	virtual ~ICollision2D() {}


	/**
	 * @brief 2D ������Ʈ�� �浹 ���� ������ ����ϴ�.
	 * 
	 * @return 2D ������Ʈ�� �浹 ���� ������ ��ȯ�մϴ�.
	 */
	virtual EType GetType() const = 0;


	/**
	 * @brief �ٸ� 2D ������Ʈ���� �浹 ���θ� Ȯ���մϴ�.
	 * 
	 * @param target �浹 ���θ� �˻��� Ÿ���Դϴ�.
	 * 
	 * @return �浹�� ����Ǹ� true, �׷��� ������ false�� ��ȯ�մϴ�.
	 */
	virtual bool Intersect(const ICollision2D* target) const = 0;
};


/**
 * @brief 2D �� �Դϴ�.
 */
struct Line2D : public ICollision2D
{
	/**
	 * @brief 2D ���� ����Ʈ �������Դϴ�.
	 */
	Line2D() = default;


	/**
	 * @brief 2D ���� �������Դϴ�.
	 * 
	 * @param s 2D ���� �������Դϴ�.
	 * @param e 2D ���� �����Դϴ�.
	 */
	Line2D(const Vec2f& s, const Vec2f& e) : start(s), end(e) {}


	/**
	 * @brief 2D ���� ���� �������Դϴ�.
	 * 
	 * @param instance ���Ҹ� ������ 2D �� �ν��Ͻ��Դϴ�.
	 */
	Line2D(Line2D&& instance) noexcept : start(instance.start), end(instance.end) {}


	/**
	 * @brief 2D ���� ���� �������Դϴ�.
	 *
	 * @param instance ���Ҹ� ������ 2D �� �ν��Ͻ��Դϴ�.
	 */
	Line2D(const Line2D& instance) noexcept : start(instance.start), end(instance.end) {}


	/**
	 * @brief 2D ���� �� ���� �Ҹ����Դϴ�.
	 */
	virtual ~Line2D() {}


	/**
	 * @brief 2D ���� ���� �������Դϴ�.
	 * 
	 * @param instance ���� ������ ������ 2D �� �ν��Ͻ��Դϴ�.
	 * 
	 * @return ���� ������ ������ ��ü�� �����ڸ� ��ȯ�մϴ�.
	 */
	Line2D& operator=(Line2D&& instance) noexcept
	{
		if (this == &instance) return *this;

		start = instance.start;
		end = instance.end;

		return *this;
	}


	/**
	 * @brief 2D ���� ���� �������Դϴ�.
	 *
	 * @param instance ���� ������ ������ 2D �� �ν��Ͻ��Դϴ�.
	 *
	 * @return ���� ������ ������ ��ü�� �����ڸ� ��ȯ�մϴ�.
	 */
	Line2D& operator=(const Line2D& instance) noexcept
	{
		if (this == &instance) return *this;

		start = instance.start;
		end = instance.end;

		return *this;
	}

	virtual EType GetType() const override { return EType::LINE; }


	/**
	 * @brief �ٸ� 2D ������Ʈ���� �浹 ���θ� Ȯ���մϴ�.
	 *
	 * @param target �浹 ���θ� �˻��� Ÿ���Դϴ�.
	 *
	 * @return �浹�� ����Ǹ� true, �׷��� ������ false�� ��ȯ�մϴ�.
	 */
	virtual bool Intersect(const ICollision2D* target) const override;


	/**
	 * @brief ���� �������Դϴ�.
	 */
	Vec2f start;


	/**
	 * @brief ���� �����Դϴ�.
	 */
	Vec2f end;
};

}