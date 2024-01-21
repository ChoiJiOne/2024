#pragma once

#include "IScene.h"
#include "UIMouseButton.h"

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
	 * @brief ���� ���� ���� ������Ʈ�� �ε��մϴ�.
	 */
	void LoadObjects();


private:
	/**
	 * @brief ���� Ÿ��Ʋ UI ������Ʈ�Դϴ�.
	 */
	UIMainTitle* mainTitle_ = nullptr;


	/**
	 * @brief ���� ��ư�Դϴ�.
	 */
	UIMouseButton* startButton_ = nullptr;


	/**
	 * @brief ���� ��ư�Դϴ�.
	 */
	UIMouseButton* quitButton_ = nullptr;
};