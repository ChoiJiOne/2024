#pragma once

#include "IScene.h"
#include "UIButton.h"

#include "UIMainTitle.h"


/**
 * @brief ���� ���� ���Դϴ�.
 */
class StartScene : public IScene
{
public:
	/**
	 * @brief ���� ���� ���� �������Դϴ�.
	 */
	StartScene();


	/**
	 * @brief ���� ���� ���� ���� �Ҹ����Դϴ�.
	 */
	virtual ~StartScene();


	/**
	 * @brief ���� ���� ���� ���� �����ڿ� ���� �����ڸ� ��������� �����մϴ�.
	 */
	DISALLOW_COPY_AND_ASSIGN(StartScene);


	/**
	 * @brief ���� ���� ���� �� �������� �����մϴ�.
	 *
	 * @param deltaSeconds ��Ÿ �ð����Դϴ�.
	 */
	virtual void Tick(float deltaSeconds) override;


private:
	/**
	 * @brief ���� Ÿ��Ʋ UI ������Ʈ�Դϴ�.
	 */
	UIMainTitle* mainTitle_ = nullptr;


	/**
	 * @brief UI ��ư�Դϴ�.
	 */
	UIButton* button_ = nullptr;
};