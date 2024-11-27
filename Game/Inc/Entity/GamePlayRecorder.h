#pragma once

#include "IEntity.h"

/** ���� �÷��� ����� �����ϴ� ��ƼƼ�Դϴ�. */
class GamePlayRecorder : public IEntity
{
public:
	GamePlayRecorder();
	virtual ~GamePlayRecorder();

	DISALLOW_COPY_AND_ASSIGN(GamePlayRecorder);

	virtual void Tick(float deltaSeconds) override;
	virtual void Release() override;

private:
	/** �÷��� �ð��Դϴ�. */
	float playTime_ = 0.0f;

	/** ȹ���� ���� ���Դϴ�. */
	int32_t countCoin_ = 0;

	/** ȸ���� ü���Դϴ�. */
	float healHp_ = 0.0f;

	/** ������ ü���Դϴ�. */
	float lostHp_ = 0.0f;

	/** ȸ���� �����Դϴ�. */
	float healMp_ = 0.0f;

	/** ����� �����Դϴ�. */
	float useMp_ = 0.0f;

	/** �÷����ϴ� ���� ���� �������Դϴ�. */
	float damageReceived_ = 0.0f;

	/** ��ų�� ����� Ƚ���Դϴ�. */
	int32_t countUseSkill_ = 0;
};