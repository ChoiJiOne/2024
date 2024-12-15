#pragma once

#include <functional>
#include <vector>

#include "IEntity.h"
#include "IScene.h"


/**
 * @brief ��ŷ ���Դϴ�.
 */
class RankScene : public IScene
{
public:
	/**
	 * @brief ��ŷ ���� ����Ʈ �������Դϴ�.
	 */
	RankScene() = default;


	/**
	 * @brief ��ŷ ���� ���� �Ҹ����Դϴ�.
	 */
	virtual ~RankScene() {}


	/**
	 * @brief ��ŷ ���� ���� ������ �� ���� �����ڸ� ��������� �����մϴ�.
	 */
	DISALLOW_COPY_AND_ASSIGN(RankScene);


	/**
	 * @brief ��ŷ ���� �� �������� �����մϴ�.
	 *
	 * @param deltaSeconds �� ���� ��Ÿ �ð����Դϴ�.
	 */
	virtual void Tick(float deltaSeconds) override;


	/**
	 * @brief ��ŷ ���� �����մϴ�.
	 */
	virtual void Enter() override;


	/**
	 * @brief ��ŷ ������ �����ϴ�.
	 */
	virtual void Exit() override;


	/**
	 * @brief ��׶��� ��ƼƼ�� ID ���� �����մϴ�.
	 *
	 * @param id ������ ��׶��� ��ƼƼ�� ID ���Դϴ�.
	 */
	void SetBackgroundID(const EUID& id) { backgroundID_ = id; }


	/**
	 * @brief �ٴ� ��ƼƼ�� ID ���� �����մϴ�.
	 *
	 * @param id ������ �ٴ� ��ƼƼ�� ID ���Դϴ�.
	 */
	void SetLandID(const EUID& id) { landID_ = id; }


	/**
	 * @brief ������ ��Ʈ�ѷ� ��ƼƼ�� ID ���� �����մϴ�.
	 * 
	 * @param id ������ ������ ��Ʈ�ѷ� ��ƼƼ�� ID ���Դϴ�.
	 */
	void SetPipeController(const EUID& id) { pipeController_ = id; }


	/**
	 * @brief ���� ���� �����մϴ�.
	 *
	 * @param startScene ������ ���� ���� �������Դϴ�.
	 */
	void SetStartScene(IScene* startScene) { startScene_ = startScene; }


	/**
	 * @brief ���� ���� �̺�Ʈ�� �����մϴ�.
	 *
	 * @param quitLoopEvent ������ ���� ���� �̺�Ʈ�Դϴ�.
	 */
	void SetQuitLoopEvent(const std::function<void()>& quitLoopEvent) { quitLoopEvent_ = quitLoopEvent; }


private:
	/**
	 * @brief ���� ���� �̺�Ʈ�Դϴ�.
	 */
	std::function<void()> quitLoopEvent_;
	

	/**
	 * @brief ���� �� �Դϴ�.
	 */
	IScene* startScene_ = nullptr;


	/**
	 * @brief ��׶��� ��ƼƼ�� ID ���Դϴ�.
	 */
	EUID backgroundID_ = -1;


	/**
	 * @brief �ٴ� ��ƼƼ�� ID ���Դϴ�.
	 */
	EUID landID_ = -1;


	/**
	 * @brief ������ ��Ʈ�ѷ� ��ƼƼ�� ID ���Դϴ�.
	 */
	EUID pipeController_ = -1;


	/**
	 * @brief ��ƼƼ ����Դϴ�.
	 */
	std::vector<EUID> entityIDs_;
};