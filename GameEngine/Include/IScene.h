#pragma once

#include "Macro.h"


/**
 * @brief �� �������̽��Դϴ�.
 * 
 * @note ���� ���� ���� ��� �� �������̽��� ��ӹ޾ƾ� �մϴ�.
 */
class IScene
{
public:
	/**
	 * @brief ���� ����Ʈ �������Դϴ�.
	 */
	IScene() = default;


	/**
	 * @brief ���� ���� �Ҹ����Դϴ�.
	 */
	virtual ~IScene() {}


	/**
	 * @brief ���� ���� �����ڿ� ���� �����ڸ� ��������� �����մϴ�.
	 */
	DISALLOW_COPY_AND_ASSIGN(IScene);


	/**
	 * @brief ���� �� �������� �����մϴ�.
	 *
	 * @param deltaSeconds ��Ÿ �ð����Դϴ�.
	 */
	virtual void Tick(float deltaSeconds) = 0;


	/**
	 * @brief ���� �����մϴ�.
	 */
	virtual void EnterScene() = 0;


	/**
	 * @brief ������ �����ϴ�.
	 */
	virtual void ExitScene() = 0;


	/**
	 * @brief �� ��ȯ�� �����Ǿ����� Ȯ���մϴ�.
	 *
	 * @return �� ��ȯ�� �����Ǿ��ٸ� true, �׷��� ������ false�� ��ȯ�մϴ�.
	 */
	bool DetectSwitchScene() { return bDetectSwitchScene_; }


	/**
	 * @brief ���� ���� ����� ���� ���� ����ϴ�.
	 * 
	 * @return ���� ���� ����� ���� ���� �����͸� ��ȯ�մϴ�.
	 */
	IScene* GetNextScene() { return nextScene_; }


	/**
	 * @brief ���� ���� ���� ���� �����մϴ�.
	 * 
	 * @param scene ���� ���� ������ ���� ���Դϴ�.
	 */
	void SetNextScene(IScene* nextScene) { nextScene_ = nextScene; }


protected:
	/**
	 * @brief ���� �����ߴ��� Ȯ���մϴ�
	 */
	bool bIsEnterScene_ = false;


	/**
	 * @brief �� ��ȯ�� �����Ǿ����� Ȯ���մϴ�.
	 */
	bool bDetectSwitchScene_ = false;


	/**
	 * @brief ���� ���� ���Դϴ�.
	 */
	IScene* nextScene_ = nullptr;
};