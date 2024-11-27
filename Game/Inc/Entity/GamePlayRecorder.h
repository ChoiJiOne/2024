#pragma once

#include "IEntity.h"

/** 게임 플레이 기록을 저장하는 엔티티입니다. */
class GamePlayRecorder : public IEntity
{
public:
	GamePlayRecorder();
	virtual ~GamePlayRecorder();

	DISALLOW_COPY_AND_ASSIGN(GamePlayRecorder);

	virtual void Tick(float deltaSeconds) override;
	virtual void Release() override;

private:
	/** 플레이 시간입니다. */
	float playTime_ = 0.0f;

	/** 획득한 코인 수입니다. */
	int32_t countCoin_ = 0;

	/** 회복한 체력입니다. */
	float healHp_ = 0.0f;

	/** 감소한 체력입니다. */
	float lostHp_ = 0.0f;

	/** 회복한 마나입니다. */
	float healMp_ = 0.0f;

	/** 사용한 마나입니다. */
	float useMp_ = 0.0f;

	/** 플레이하는 동안 받은 데미지입니다. */
	float damageReceived_ = 0.0f;

	/** 스킬을 사용한 횟수입니다. */
	int32_t countUseSkill_ = 0;
};