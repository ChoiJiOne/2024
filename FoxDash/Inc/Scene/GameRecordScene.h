#pragma once

#include <list>

#include "Scene/IGameScene.h"
#include "GL/RenderManager2D.h"

/** Ŭ���� ���� �����Դϴ�. */
class GameManager;
class ResultViewer;
class UICamera;

/** ���� ����� �����ִ� ���Դϴ�. */
class GameRecordScene : public IGameScene
{
public:
	GameRecordScene();
	virtual ~GameRecordScene();

	DISALLOW_COPY_AND_ASSIGN(GameRecordScene);

	virtual void Tick(float deltaSeconds) override;
	virtual void Render() override;
	virtual void Enter() override;
	virtual void Exit() override;

private:
	/** ���� ��� ���� �ʱ�ȭ�մϴ�. */
	void Initailize();

	/** ���� ��� ���� �ʱ�ȭ�� �����մϴ�. */
	void UnInitailize();

	/** ��ü ���� �÷��� ����� �����ִ� ��ƼƼ�� �ʱ�ȭ�մϴ�. */
	void InitTotalResultViewers();

	/** ��� ���� �÷��� ����� �����ִ� ��ƼƼ�� �ʱ�ȭ�մϴ�. */
	void InitAverageResultViewers();

	/** ��ü ���� �÷��� ����� �����ִ� ��ƼƼ�� ������Ʈ�մϴ�. */
	void UpdateTotalResultViewers();

	/** ��� ���� �÷��� ����� �����ִ� ��ƼƼ�� ������Ʈ�մϴ�. */
	void UpdateAverageResultViewers();

private:	
	/** ���� ��� ���� ��ũ�� ī�޶��Դϴ�. */
	UICamera* uiCamera_ = nullptr;

	/** ������Ʈ�� UI ��ƼƼ�Դϴ�. */
	std::list<IEntity*> updateUiEntities_;

	/** �������� UI ��ƼƼ�Դϴ�. */
	std::list<IEntity2D*> renderUiEntities_;

	/** ��ü ���� �÷��� ����� �����ִ� ��ƼƼ�Դϴ�. */
	ResultViewer* totalPlayTime_ = nullptr;
	ResultViewer* totalGetCoin_ = nullptr;
	ResultViewer* totalUseSkill_ = nullptr;
	ResultViewer* totalHealHp_ = nullptr;
	ResultViewer* totalLostHp_ = nullptr;
	ResultViewer* totalHealMp_ = nullptr;
	ResultViewer* totalLostMp_ = nullptr;

	/** ��� ���� �÷��� ����� �����ִ� ��ƼƼ�Դϴ�. */
	ResultViewer* avgPlayTime_ = nullptr;
	ResultViewer* avgGetCoin_ = nullptr;
	ResultViewer* avgUseSkill_ = nullptr;
	ResultViewer* avgHealHp_ = nullptr;
	ResultViewer* avgLostHp_ = nullptr;
	ResultViewer* avgHealMp_ = nullptr;
	ResultViewer* avgLostMp_ = nullptr;

	/** ���� �÷��� ����� ǥ���� �ð��Դϴ�. */
	float playRecordViewTime_ = 0.0f;

	/** ���� �Ŵ��� �������Դϴ�. */
	GameManager* gameManager_ = nullptr;
};