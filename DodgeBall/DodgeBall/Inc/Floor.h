#pragma once

#include "GameObject.h"


/**
 * @brief �ٴ� ������Ʈ�Դϴ�.
 */
class Floor : public GameObject
{
public:
	/**
	 * @brief �ٴ� ������Ʈ�� �⺻ �������Դϴ�.
	 * 
	 * @note ������ �̿��� �޼��忡�� ������ �ʱ�ȭ�� �����ؾ� �մϴ�.
	 */
	Floor() = default;


	/**
	 * @brief �ٴ� ������Ʈ�� ���� �Ҹ����Դϴ�.
	 */
	virtual ~Floor();


	/**
	 * @brief �ٴ� ������Ʈ�� ���� �����ڿ� ���� �����ڸ� ��������� �����մϴ�.
	 */
	DISALLOW_COPY_AND_ASSIGN(Floor);


	/**
	 * @brief �ٴ� ������Ʈ�� �ʱ�ȭ�մϴ�.
	 */
	void Initialize();


	/**
	 * @brief �ٴ� ������Ʈ�� ������Ʈ�մϴ�.
	 * 
	 * @param deltaSeconds ��Ÿ �ð� ���Դϴ�.
	 */
	virtual void Tick(float deltaSeconds) override;


	/**
	 * @brief �ٴ� ������Ʈ ���� ���ҽ��� �Ҵ� �����մϴ�.
	 */
	virtual void Release() override;


	/**
	 * @brief ������Ʈ�� ��� ������ ����ϴ�.
	 *
	 * @return ������Ʈ�� ��� ������ ��ȯ�մϴ�.
	 */
	virtual const IShape3D* GetBoundingVolume() const override { return nullptr; }
};