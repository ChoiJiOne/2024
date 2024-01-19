#pragma once

#include "GameObject.h"
#include "Sphere3D.h"


/**
 * @brief �÷��̾ ���� ������ ������Ʈ�Դϴ�.
 */
class Player : public GameObject
{
public:
	/**
	 * @brief �÷��̾ ���� ������ ������Ʈ�� �⺻ �������Դϴ�.
	 *
	 * @note ������ �̿��� �޼��忡�� ������ �ʱ�ȭ�� �����ؾ� �մϴ�.
	 */
	Player() = default;


	/**
	 * @brief �÷��̾ ���� ������ ������Ʈ�� ���� �Ҹ����Դϴ�.
	 */
	virtual ~Player();


	/**
	 * @brief �÷��̾ ���� ������ ������Ʈ�� ���� �����ڿ� ���� �����ڸ� ��������� �����մϴ�.
	 */
	DISALLOW_COPY_AND_ASSIGN(Player);


	/**
	 * @brief �÷��̾ ���� ������ ������Ʈ�� �ʱ�ȭ�մϴ�.
	 */
	void Initialize();


	/**
	 * @brief �÷��̾ ���� ������ ������Ʈ�� ������Ʈ�մϴ�.
	 * 
	 * @param deltaSeconds ��Ÿ �ð� ���Դϴ�.
	 */
	virtual void Tick(float deltaSeconds) override;


	/**
	 * @brief �÷��̾ ���� ������ ������Ʈ ���� ���ҽ��� �Ҵ� �����մϴ�.
	 */
	virtual void Release() override;


	/**
	 * @brief �÷��̾ ���� ������ ������Ʈ�� ��� ������ ����ϴ�.
	 *
	 * @return �÷��̾ ���� ������ ������Ʈ�� ��� ������ ��ȯ�մϴ�.
	 */
	virtual const IShape3D* GetBoundingVolume() const override { return &boundingVolume_; }


	/**
	 * @brief �÷��̾��� �������� ����ϴ�.
	 * 
	 * @return �÷��̾��� �������� ��ȯ�մϴ�.
	 */
	uint32_t GetLife() const { return life_; }


	/**
	 * @brief �÷��̾��� �÷��� �ð��� ����ϴ�.
	 * 
	 * @return �÷��̾��� �÷��� �ð��� ��ȯ�մϴ�.
	 */
	float GetPlayTime() const { return playTime_; }


	/**
	 * @brief �÷��̾��� �������� �����մϴ�.
	 *
	 * @param life ������ �÷��̾��� �������Դϴ�.
	 */
	void SetLife(uint32_t life) { life_ = life; }
	

private:
	/**
	 * @brief ���� �浹�ϴ��� Ȯ���մϴ�.
	 *
	 * @return ���� �浹�Ѵٸ� true, �׷��� ������ false�� ��ȯ�մϴ�.
	 */
	bool CheckCollisionToWall();


private:
	/**
	 * @brief �÷��̾ ���� ������ ������Ʈ�� ��� �����Դϴ�.
	 */
	Sphere3D boundingVolume_;


	/**
	 * @brief �÷��̾��� �������Դϴ�.
	 */
	uint32_t life_ = 0;


	/**
	 * @brief �÷��� Ÿ���Դϴ�.
	 */
	float playTime_ = 0.0f;
};