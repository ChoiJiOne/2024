#pragma once

#include "GameMath.h"


namespace GameMaker
{
/**
 * @brief 2D ������Ʈ�� �浹 ���� �������̽��Դϴ�.
 */
class ICollision2D
{
public:
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


public:
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
	virtual bool Intersect(const ICollision2D* target) = 0;
};


}