#pragma once

#include "UIObject.h"


/**
 * @brief ���� Ÿ��Ʋ UI�Դϴ�.
 */
class UIMainTitle : public UIObject
{
public:
	/**
	 * @brief ���� Ÿ��Ʋ UI ������Ʈ�� ����Ʈ �������Դϴ�.
	 */
	UIMainTitle() = default;


	/**
	 * @brief ���� Ÿ��Ʋ UI ������Ʈ�� ���� �Ҹ����Դϴ�.
	 */
	virtual ~UIMainTitle();


	/**
	 * @brief ���� Ÿ��Ʋ UI ������Ʈ�� ���� �����ڿ� ���� �����ڸ� ��������� �����մϴ�.
	 */
	DISALLOW_COPY_AND_ASSIGN(UIMainTitle);


	/**
	 * @brief ���� Ÿ��Ʋ UI ������Ʈ�� �ʱ�ȭ�մϴ�.
	 */
	void Initialize();


	/**
	 * @brief ���� Ÿ��Ʋ UI ������Ʈ�� ������Ʈ�մϴ�.
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