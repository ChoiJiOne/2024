#pragma once

#include "GameObject.h"


/**
 * @brief �÷��̾ ���ؾ� �� �Ѿ��� �����ϴ� ������Ʈ�Դϴ�.
 */
class BulletSpawner : public GameObject
{
public:
	/**
	 * @brief �÷��̾ ���ؾ� �� �Ѿ��� �����ϴ� ������Ʈ�� �⺻ �������Դϴ�.
	 *
	 * @note ������ �̿��� �޼��忡�� ������ �ʱ�ȭ�� �����ؾ� �մϴ�.
	 */
	BulletSpawner() = default;


	/**
	 * @brief �÷��̾ ���ؾ� �� �Ѿ��� �����ϴ� ������Ʈ�� ���� �Ҹ����Դϴ�.
	 */
	virtual ~BulletSpawner();


	/**
	 * @brief �÷��̾ ���ؾ� �� �Ѿ��� �����ϴ� ������Ʈ�� ���� �����ڿ� ���� �����ڸ� ��������� �����մϴ�.
	 */
	DISALLOW_COPY_AND_ASSIGN(BulletSpawner);


	/**
	 * @brief �÷��̾ ���ؾ� �� �Ѿ��� �����ϴ� ������Ʈ�� �ʱ�ȭ�մϴ�.
	 * 
	 * @param location �÷��̾ ���ؾ� �� �Ѿ��� �����ϴ� ������Ʈ�� ���� �� ��ġ�Դϴ�. 
	 */
	void Initialize(const Vector3f& location);


	/**
	 * @brief �÷��̾ ���ؾ� �� �Ѿ��� �����ϴ� ������Ʈ�� ������Ʈ�մϴ�.
	 * 
	 * @param deltaSeconds ��Ÿ �ð� ���Դϴ�.
	 */
	virtual void Tick(float deltaSeconds) override;


	/**
	 * @brief �÷��̾ ���ؾ� �� �Ѿ��� �����ϴ� ������Ʈ ���� ���ҽ��� �Ҵ� �����մϴ�.
	 */
	virtual void Release() override;
};