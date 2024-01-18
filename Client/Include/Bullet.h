#pragma once

#include "GameObject.h"
#include "Sphere3D.h"
#include "Vector3.h"


/**
 * @brief �÷��̾ ���ؾ� �� �Ѿ� ������Ʈ�Դϴ�.
 */
class Bullet : public GameObject
{
public:
	/**
	 * @brief �÷��̾ ���ؾ� �� �Ѿ� ������Ʈ�� �⺻ �������Դϴ�.
	 *
	 * @note ������ �̿��� �޼��忡�� ������ �ʱ�ȭ�� �����ؾ� �մϴ�.
	 */
	Bullet() = default;


	/**
	 * @brief �÷��̾ ���ؾ� �� �Ѿ� ������Ʈ�� ���� �Ҹ����Դϴ�.
	 */
	virtual ~Bullet();

	
	/**
	 * @brief �÷��̾ ���ؾ� �� �Ѿ� ������Ʈ�� ���� �����ڿ� ���� �����ڸ� ��������� �����մϴ�.
	 */
	DISALLOW_COPY_AND_ASSIGN(Bullet);


	/**
	 * @brief �÷��̾ ���ؾ� �� �Ѿ� ������Ʈ�� �ʱ�ȭ�մϴ�.
	 *
	 * @param location �Ѿ� ������Ʈ�� ���� �� ��ġ�Դϴ�.
	 * @param direction �Ѿ��� �����Դϴ�.
	 * @param speed �Ѿ��� �ӷ��Դϴ�.
	 * @param boundRadius �Ѿ��� ��� �� ������ �����Դϴ�.
	 */
	void Initialize(const Vector3f& location, const Vector3f& direction, float speed, float boundRadius);


	/**
	 * @brief �÷��̾ ���ؾ� �� �Ѿ� ������Ʈ�� ������Ʈ�մϴ�.
	 *
	 * @param deltaSeconds ��Ÿ �ð� ���Դϴ�.
	 */
	virtual void Tick(float deltaSeconds) override;


	/**
	 * @brief �÷��̾ ���ؾ� �� �Ѿ� ������Ʈ ���� ���ҽ��� �Ҵ� �����մϴ�.
	 */
	virtual void Release() override;


	/**
	 * @brief �Ѿ� ������Ʈ�� ��� ������ ����ϴ�.
	 * 
	 * @return �Ѿ� ������Ʈ�� ��� ������ ��ȯ�մϴ�.
	 */
	virtual const IShape3D* GetBoundingVolume() const override { return &boundingVolume_; }


private:
	/**
	 * @brief �Ѿ��� �����Դϴ�.
	 */
	Vector3f direction_;


	/**
	 * @brief �Ѿ��� �ӷ��Դϴ�.
	 */
	float speed_;


	/**
	 * @brief �Ѿ��� ��� �����Դϴ�.
	 */
	Sphere3D boundingVolume_;
};