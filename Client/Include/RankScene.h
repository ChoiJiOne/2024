#pragma once

#include "IScene.h"
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
	 * @brief ���� ���� �̺�Ʈ�Դϴ�.
	 */
	std::function<void()> loopQuitEvent_ = nullptr;
};