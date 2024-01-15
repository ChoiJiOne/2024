#pragma once

#include <cstdint>


/**
 * @brief �浹 ������ 3D ������ �������̽��Դϴ�.
 */
class IShape3D
{
public:
	/**
	 * @brief 3D ������ �����Դϴ�.
	 */
	enum class EType : int32_t
	{
		None = 0x00,
		AABB = 0x01,
		Sphere = 0x02,
	};


public:
	/**
	 * @brief �浹 ������ 3D ���� �������̽��� �⺻ �������Դϴ�.
	 */
	IShape3D() = default;


	/**
	 * @brief �浹 ������ 3D ���� �������̽��� ���� �Ҹ����Դϴ�.
	 */
	virtual ~IShape3D() {}


	/**
	 * @brief 3D ������ ������ ����ϴ�.
	 * 
	 * @return 3D ������ ������ ��ȯ�մϴ�.
	 * 
	 * @note ���� Ŭ�������� �ݵ�� �����ؾ� �ϴ� ���� ���� �Լ��Դϴ�.
	 */
	virtual EType GetType() const = 0;


	/**
	 * @brief �ٸ� 3D ���°� ����Ǵ��� Ȯ���մϴ�.
	 * 
	 * @param shape ������ Ȯ���� 3D ���� �ν��Ͻ��Դϴ�.
	 * 
	 * @return �ٸ� 3D ���°� ����ȴٸ� true, �׷��� ������ false�� ��ȯ�մϴ�.
	 */
	virtual bool Intersect(const IShape3D* shape) const = 0;
};