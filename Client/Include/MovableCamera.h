#pragma once

#include "Camera3D.h"


/**
 * @brief �÷��̾ ���� �����̴� ī�޶��Դϴ�.
 */
class MovableCamera : public Camera3D
{
public:
	/**
	 * @brief �÷��̾ ���� �����̴� ī�޶� ������Ʈ�� ����Ʈ �������Դϴ�.
	 *
	 * @note ������ �̿��� �޼��忡�� ������ �ʱ�ȭ�� �����ؾ� �մϴ�.
	 */
	MovableCamera() = default;


	/**
	 * @brief �÷��̾ ���� �����̴� ī�޶� ������Ʈ�� ���� �Ҹ����Դϴ�.
	 *
	 * @note �÷��̾ ���� �����̴� ī�޶� ������Ʈ�� ���� ���ҽ��� �Ҵ� �����ϱ� ���ؼ��� Release �޼��带 ȣ���ؾ� �մϴ�.
	 */
	virtual ~MovableCamera();


	/**
	 * @brief �÷��̾ ���� �����̴� ī�޶� ������Ʈ�� ���� ������ �� ���� �����ڸ� ��������� �����մϴ�.
	 */
	DISALLOW_COPY_AND_ASSIGN(MovableCamera);


	/**
	 * @brief �÷��̾ ���� �����̴� ī�޶� �ʱ�ȭ�մϴ�.
	 */
	void Initialize();


	/**
	 * @brief �÷��̾ ���� �����̴� ī�޶� ������Ʈ�� ������Ʈ�մϴ�.
	 *
	 * @param deltaSeconds ��Ÿ �ð� ���Դϴ�.
	 */
	virtual void Tick(float deltaSeconds) override;


	/**
	 * @brief �÷��̾ ���� �����̴� ī�޶� ������Ʈ ���� ���ҽ��� �Ҵ� �����մϴ�.
	 */
	virtual void Release() override;
};