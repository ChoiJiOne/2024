#pragma once

#include <cstdint>


/**
 * @brief �浹 ������ 3D ��� ���� �������̽��Դϴ�.
 * 
 * @note �浹 ������ 3D ��� ������ �� �������̽��� �ݵ�� ��� �޾ƾ� �մϴ�.
 */
class IBoundingVolume
{
public:
	/**
	 * @brief 3D ��� ������ �����Դϴ�.
	 */
	enum class EType : int32_t
	{
		NONE   = 0x00,
		BOX    = 0x01,
		SPHERE = 0x02,
	};


public:
	/**
	 * @brief �浹 ������ 3D ��� ���� �������̽��� �⺻ �������Դϴ�.
	 */
	IBoundingVolume() = default;


	/**
	 * @brief �浹 ������ 3D ��� ���� �������̽��� ���� �Ҹ����Դϴ�.
	 */
	virtual ~IBoundingVolume() {}


	/**
	 * @brief 3D ��� ������ ������ ����ϴ�.
	 *
	 * @return  3D ��� ������ ������ ��ȯ�մϴ�.
	 */
	virtual EType GetType() const = 0;


	/**
	 * @brief �ٸ� 3D ��� ������ �浹�ϴ��� Ȯ���մϴ�.
	 *
	 * @param boundingVolume ������ Ȯ���� 3D ��� �����Դϴ�.
	 *
	 * @return �ٸ� 3D ���� �浹�Ѵٸ� true, �׷��� ������ false�� ��ȯ�մϴ�.
	 */
	virtual bool Intersect(const IBoundingVolume* boundVolume) const = 0;
};