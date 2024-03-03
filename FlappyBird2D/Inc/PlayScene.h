#pragma once

#include <functional>
#include <vector>

#include "Bird.h"
#include "IEntity.h"
#include "IScene.h"


/**
 * @brief �÷��� ���Դϴ�.
 */
class PlayScene : public IScene
{
public:
	/**
	 * @brief �÷��� ���� ����Ʈ �������Դϴ�.
	 */
	PlayScene() = default;


	/**
	 * @brief �÷��� ���� ���� �Ҹ����Դϴ�.
	 */
	virtual ~PlayScene() {}


	/**
	 * @brief �÷��� ���� ���� ������ �� ���� �����ڸ� ��������� �����մϴ�.
	 */
	DISALLOW_COPY_AND_ASSIGN(PlayScene);


	/**
	 * @brief �÷��� ���� �� �������� �����մϴ�.
	 *
	 * @param deltaSeconds �� ���� ��Ÿ �ð����Դϴ�.
	 */
	virtual void Tick(float deltaSeconds) override;


	/**
	 * @brief �÷��� ���� �����մϴ�.
	 */
	virtual void Enter() override;


	/**
	 * @brief �÷��� ������ �����ϴ�.
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
	 * @brief �÷��� �� �Դϴ�.
	 */
	IScene* startScene_ = nullptr;


	/**
	 * @brief ��ƼƼ ����Դϴ�.
	 */
	std::vector<EUID> entityIDs_;


	/**
	 * @brief �÷��̾ �����ϴ� �� ��ƼƼ�Դϴ�.
	 */
	Bird* bird_ = nullptr;
};