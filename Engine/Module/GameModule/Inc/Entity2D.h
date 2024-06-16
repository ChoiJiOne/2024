#pragma once

#include "IEntity.h"


/**
 * @brief 2D ��ƼƼ�� �������̽��Դϴ�.
 */
class Entity2D : public IEntity
{
public:
	/**
	 * @brief 2D ��ƼƼ �������̽��� ����Ʈ �������Դϴ�.
	 */
	Entity2D() = default;


	/**
	 * @brief 2D ��ƼƼ �������̽��� ���� �Ҹ����Դϴ�.
	 */
	virtual ~Entity2D() {}


	/**
	 * @brief 2D ��ƼƼ �������̽��� ���� �����ڿ� ���� �����ڸ� ��������� �����մϴ�.
	 */
	DISALLOW_COPY_AND_ASSIGN(Entity2D);


	/**
	 * @brief 2D ��ƼƼ�� ������Ʈ�մϴ�.
	 *
	 * @param deltaSeconds ��Ÿ �ð� ���Դϴ�.
	 *
	 * @note
	 * - 2D ��ƼƼ �������̽��� ��ӹ޴� ���� Ŭ�������� �ݵ�� �����ؾ� �մϴ�.
	 * - ��Ÿ �ð� ���� �ʴ����Դϴ�.
	 */
	virtual void Tick(float deltaSeconds) = 0;


	/**
	 * @brief 2D ��ƼƼ�� �������մϴ�.
	 * 
	 * @note 2D ��ƼƼ �������̽��� ��ӹ޴� ���� Ŭ�������� �ݵ�� �����ؾ� �մϴ�.
	 */
	virtual void Render() = 0;


	/**
	 * @brief 2D ��ƼƼ ���� ���ҽ��� �Ҵ� �����մϴ�.
	 *
	 * @note 2D ��ƼƼ �������̽��� ��ӹ޴� ���� Ŭ�������� �ݵ�� �����ؾ� �մϴ�.
	 */
	virtual void Release() = 0;
};