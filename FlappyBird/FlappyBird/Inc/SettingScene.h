#pragma once

#include <functional>
#include <vector>

#include "IEntity.h"
#include "IScene.h"


/**
 * @brief ���� ���Դϴ�.
 */
class SettingScene : public IScene
{
public:
	/**
	 * @brief ���� ���� ����Ʈ �������Դϴ�.
	 */
	SettingScene() = default;


	/**
	 * @brief ���� ���� ���� �Ҹ����Դϴ�.
	 */
	virtual ~SettingScene() {}


	/**
	 * @brief ���� ���� ���� ������ �� ���� �����ڸ� ��������� �����մϴ�.
	 */
	DISALLOW_COPY_AND_ASSIGN(SettingScene);


	/**
	 * @brief ���� ���� �� �������� �����մϴ�.
	 *
	 * @param deltaSeconds �� ���� ��Ÿ �ð����Դϴ�.
	 */
	virtual void Tick(float deltaSeconds) override;


	/**
	 * @brief ���� ���� �����մϴ�.
	 */
	virtual void Enter() override;


	/**
	 * @brief ���� ������ �����ϴ�.
	 */
	virtual void Exit() override;


	/**
	 * @brief ���� ���� �����մϴ�.
	 *
	 * @param startScene ������ ���� ���� �������Դϴ�.
	 */
	void SetStartScene(IScene* startScene) { startScene_ = startScene; }


private:
	/**
	 * @brief ���� �� �Դϴ�.
	 */
	IScene* startScene_ = nullptr;

	
	/**
	 * @brief ��ƼƼ ����Դϴ�.
	 */
	std::vector<EUID> entities_;
};