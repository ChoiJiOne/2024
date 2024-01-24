#pragma once

#include "Light.h"


/**
 * @brief ���� ����Ʈ�Դϴ�.
 */
class StaticLight : public Light
{
public:
	/**
	 * @brief ���� ����Ʈ�� ����Ʈ �������Դϴ�.
	 *
	 * @note ������ �̿��� �޼��忡�� ������ �ʱ�ȭ�� �����ؾ� �մϴ�.
	 */
	StaticLight() = default;


	/**
	 * @brief ���� ����Ʈ�� ���� �Ҹ����Դϴ�.
	 *
	 * @note ���� ������Ʈ ���ο��� �Ҵ�� ���ҽ��� �����ϱ� ���ؼ��� Release �޼��带 ȣ���ؾ� �մϴ�.
	 */
	virtual ~StaticLight();


	/**
	 * @brief ���� ����Ʈ�� ���� �����ڿ� ���� �����ڸ� ��������� �����մϴ�.
	 */
	DISALLOW_COPY_AND_ASSIGN(StaticLight);


	/**
	 * @brief ���� ����Ʈ�� �ʱ�ȭ�մϴ�.
	 */
	void Initialize();


	/**
	 * @brief ���� ����Ʈ�� ������Ʈ�մϴ�.
	 *
	 * @param deltaSeconds ��Ÿ �ð� ���Դϴ�.
	 */
	virtual void Tick(float deltaSeconds) override;


	/**
	 * @brief ���� ����Ʈ ���� ���ҽ��� �Ҵ� �����մϴ�.
	 */
	virtual void Release() override;
};