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
	 * @param position �÷��̾ ���ؾ� �� �Ѿ��� �����ϴ� ������Ʈ�� ���� �� ��ġ�Դϴ�. 
	 */
	void Initialize(const Vector3f& position);


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


	/**
	 * @brief ���忡 ������ �Ѿ��� �����ϴ� ������Ʈ ���� ����ϴ�.
	 * 
	 * @return ���忡 ������ �Ѿ��� �����ϴ� ������Ʈ ���� ��ȯ�մϴ�.
	 */
	static uint32_t GetCountOfBulletSpawner() { return countOfBulletSpawner_; }


private:
	/**
	 * @brief ���忡 ������ �Ѿ��� �����ϴ� ������Ʈ ���Դϴ�.
	 */
	static uint32_t countOfBulletSpawner_;

	
	/**
	 * @brief �Ѿ��� �ִ� �߻� �����Դϴ�. ������ �����Դϴ�.
	 */
	float maxShotAngle_ = 0.0f;


	/**
	 * @brief �Ѿ��� �ּ� �߻� �����Դϴ�. ������ �����Դϴ�.
	 */
	float minShotAngle_ = 0.0f;
};