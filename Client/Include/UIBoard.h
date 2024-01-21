#pragma once

#include "UIObject.h"

class Player; // �÷��̾� Ŭ������ ���� �����Դϴ�.


/**
 * @brief �÷��̾��� ������ ǥ���ϴ� ���� UI�Դϴ�.
 */
class UIBoard : public UIObject
{
public:
	/**
	 * @brief �÷��̾��� ������ ǥ���ϴ� ���� UI ������Ʈ�� ����Ʈ �������Դϴ�.
	 */
	UIBoard() = default;


	/**
	 * @brief �÷��̾��� ������ ǥ���ϴ� ���� UI ������Ʈ�� ���� �Ҹ����Դϴ�.
	 */
	virtual ~UIBoard();


	/**
	 * @brief �÷��̾��� ������ ǥ���ϴ� ���� UI ������Ʈ�� ���� �����ڿ� ���� �����ڸ� ��������� �����մϴ�.
	 */
	DISALLOW_COPY_AND_ASSIGN(UIBoard);


	/**
	 * @brief �÷��̾��� ������ ǥ���ϴ� ���� UI ������Ʈ�� �ʱ�ȭ�մϴ�.
	 */
	void Initialize();


	/**
	 * @brief �÷��̾��� ������ ǥ���ϴ� ���� UI ������Ʈ�� ������Ʈ�մϴ�.
	 *
	 * @param deltaSeconds ��Ÿ �ð� ���Դϴ�.
	 */
	virtual void Tick(float deltaSeconds) override;


private:
	/**
	 * @brief ������ ũ��� ���� UI�� �߽� ��ġ�� ����ϴ�.
	 * 
	 * @return ���� UI �߽� ��ġ�� ����ϴ�.
	 */
	Vector2f GetCenterFromWindow();
};