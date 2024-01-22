#pragma once

#include "PlayLogger.h"

#include "IScene.h"
#include "Sound.h"
#include "TTFont.h"
#include "UIMouseButton.h"
#include "UIPanel.h"


/**
 * @brief �÷��̾��� ����� �����ִ� ���Դϴ�.
 */
class RankScene : public IScene
{
public:
	/**
	 * @brief �÷��̾��� ����� �����ִ� ���� �������Դϴ�.
	 */
	RankScene();


	/**
	 * @brief �÷��̾��� ����� �����ִ� ���� ���� �Ҹ����Դϴ�.
	 */
	virtual ~RankScene();


	/**
	 * @brief �÷��̾��� ����� �����ִ� ���� ���� �����ڿ� ���� �����ڸ� ��������� �����մϴ�.
	 */
	DISALLOW_COPY_AND_ASSIGN(RankScene);


	/**
	 * @brief �÷��̾��� ����� �����ִ� ���� �� �������� �����մϴ�.
	 *
	 * @param deltaSeconds ��Ÿ �ð����Դϴ�.
	 */
	virtual void Tick(float deltaSeconds) override;


	/**
	 * @brief �÷��̾��� ����� �����ִ� ���� �����մϴ�.
	 */
	virtual void EnterScene() override;


	/**
	 * @brief �÷��̾��� ����� �����ִ� ������ �����ϴ�.
	 */
	virtual void ExitScene() override;


	/**
	 * @brief ������ ���� ���� �̺�Ʈ�� �����մϴ�.
	 *
	 * @param loopQuitEvent ������ ���� ���� ���� �̺�Ʈ�Դϴ�.
	 */
	void SetLoopQuitEvent(const std::function<void()>& loopQuitEvent) { loopQuitEvent_ = loopQuitEvent; }


private:
	/**
	 * @brief �÷��̾��� ����� �����ִ� ���� ���ҽ��� �ε��մϴ�.
	 */
	void LoadResources();


	/**
	 * @brief �÷��̾��� ����� �����ִ� ���� ������Ʈ�� �ε��մϴ�.
	 */
	void LoadObjects();


private:
	/**
	 * @brief ���� ���� �̺�Ʈ�Դϴ�.
	 */
	std::function<void()> loopQuitEvent_ = nullptr;


	/**
	 * @brief ũ�Ⱑ 32�� ��Ʈ ���ҽ��Դϴ�.
	 */
	TTFont* font32_ = nullptr;


	/**
	 * @brief ���� ���� ��ư�Դϴ�.
	 */
	UIMouseButton* resetButton_ = nullptr;


	/**
	 * @brief ���� ���� ��ư�Դϴ�.
	 */
	UIMouseButton* quitButton_ = nullptr;


	/**
	 * @brief �÷��̾��� ����� �����ϴ� ������Ʈ�Դϴ�.
	 */
	PlayLogger* playLogger_ = nullptr;


	/**
	 * @brief ��ư Ŭ�� �����Դϴ�.
	 */
	Sound* buttonClick_ = nullptr;
};