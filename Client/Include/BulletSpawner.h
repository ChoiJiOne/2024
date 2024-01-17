#pragma once

#include "GameObject.h"

class Camera3D;


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
	 * @param respawnTime �Ѿ��� �����ϴ� �ð� �ֱ��Դϴ�.
	 */
	void Initialize(const Vector3f& location, float respawnTime);


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
	 * @brief �÷��̾ ���ؾ� �� �Ѿ��� �����ϴ� ������Ʈ�� ������ �ð��� �׸��ϴ�.
	 * 
	 * @param camera 3D ī�޶��Դϴ�.
	 */
	void RenderRespawnTime(const Camera3D* camera);


private:
	/**
	 * @brief �÷��̾ ���ؾ� �� �Ѿ��� �����ϴ� ������Ʈ�� ���� �ð��Դϴ�.
	 */
	float stepTime_ = 0.0f;


	/**
	 * @brief �Ѿ��� �����ϴ� �ð� �ֱ��Դϴ�.
	 */
	float respawnTime_ = 0.0f;


	/**
	 * @brief �Ѿ��� �����ϴ� ������ ���� ũ���Դϴ�.
	 */
	float width_ = 0.0f;


	/**
	 * @brief �Ѿ��� �����ϴ� ������ ���� ũ���Դϴ�.
	 */
	float height_ = 0.0f;


	/**
	 * @brief �Ѿ��� �����ϴ� ������ ���� �����Դϴ�.
	 */
	Vector4f mainColor_;


	/**
	 * @brief �Ѿ��� �����ϴ� ������ ���� �����Դϴ�.
	 */
	Vector4f subColor_;
};