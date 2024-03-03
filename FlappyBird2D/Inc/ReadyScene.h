#pragma once

#include <vector>

#include "IEntity.h"
#include "IScene.h"


/**
 * @brief �غ�(Ready) ���Դϴ�.
 */
class ReadyScene : public IScene
{
public:
	/**
	 * @brief �غ�(Ready) ���� ����Ʈ �������Դϴ�.
	 */
	ReadyScene() = default;


	/**
	 * @brief �غ�(Ready) ���� ���� �Ҹ����Դϴ�.
	 */
	virtual ~ReadyScene() {}


	/**
	 * @brief �غ�(Ready) ���� ���� ������ �� ���� �����ڸ� ��������� �����մϴ�.
	 */
	DISALLOW_COPY_AND_ASSIGN(ReadyScene);


	/**
	 * @brief �غ�(Ready) ���� �� �������� �����մϴ�.
	 *
	 * @param deltaSeconds �� ���� ��Ÿ �ð����Դϴ�.
	 */
	virtual void Tick(float deltaSeconds) override;


	/**
	 * @brief �غ�(Ready) ���� �����մϴ�.
	 */
	virtual void Enter() override;


	/**
	 * @brief �غ�(Ready) ������ �����ϴ�.
	 */
	virtual void Exit() override;


	/**
	 * @brief ���� ���� �����մϴ�.
	 *
	 * @param startScene ������ ���� ���� �������Դϴ�.
	 */
	void SetPlayScene(IScene* playScene) { playScene_ = playScene; }


private:
	/**
	 * @brief ���� �÷��� �� �Դϴ�.
	 */
	IScene* playScene_ = nullptr;


	/**
	 * @brief ��׶��� ��ũ�� �ӵ��Դϴ�.
	 */
	const float backgroundScrollSpeed_ = 50.0f;


	/**
	 * @brief ���� ���̵��� ���� �ӵ��Դϴ�.
	 */
	float gameSpeed_ = 0.0f;


	/**
	 * @brief ��׶��� ��ƼƼ�� ID ���Դϴ�.
	 */
	EUID backgroundID_ = -1;


	/**
	 * @brief �ٴ� ��ƼƼ�� ID ���Դϴ�.
	 */
	EUID landID_ = -1;


	/**
	 * @brief �� ��ƼƼ�� ID ���Դϴ�.
	 */
	EUID birdID_ = -1;


	/**
	 * @brief �غ�(Ready) ���¸� ǥ���ϴ� ��ƼƼ�� ID ���Դϴ�.
	 */
	EUID readyViewer_ = -1;


	/**
	 * @brief �غ�(Ready) ���� ��ƼƼ ����Դϴ�.
	 */
	std::vector<EUID> entityIDs_;
};