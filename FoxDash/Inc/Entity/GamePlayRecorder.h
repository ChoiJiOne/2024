#pragma once

#include <map>
#include <string>

#include "IEntity.h"

/** 게임 플레이 기록을 저장하는 엔티티입니다. */
class GamePlayRecorder : public IEntity
{
public:
	/** 저장할 기록의 종류입니다. */
	enum class ERecordType
	{
		PLAY_TIME = 0x00, // 플레이 타임입니다.
		HEAL_HP = 0x01, // 회복한 체력입니다.
		LOST_HP = 0x02, // 잃은 체력입니다.
		HEAL_MP = 0x03, // 회복한 마나입니다.
		LOST_MP = 0x04, // 잃은 마나입니다.
		GET_COIN = 0x06, // 획득한 코인 수입니다.
		USE_SKILL = 0x07, // 사용한 스킬 수입니다.
		GEN_FIRE = 0x08, // 생성된 불 엔티티의 수입니다.
		GEN_COIN = 0x09, // 생성된 코인의 수입니다.
		GEN_RED_POTION = 0x0A, // 생성된 빨간(HP 회복) 포션 엔티티의 수입니다.
		GEN_BLUE_POTION = 0x0B, // 생성된 파란(MP 회복) 포션 엔티티의 수입니다.
		GEN_POWER_RED_POTION = 0x0C, // 생성된 빨간(HP 전체 회복) 파워 포션 엔티티의 수입니다.
		GEN_POWER_BLUE_POTION = 0x0D, // 생성된 파란(MP 전체 회복) 파워 포션 엔티티의 수입니다.
	};

public:
	GamePlayRecorder();
	virtual ~GamePlayRecorder();

	DISALLOW_COPY_AND_ASSIGN(GamePlayRecorder);

	virtual void Tick(float deltaSeconds) override;
	virtual void Release() override;

	/** 타입에 대응하는 기록 값에 value 값을 더합니다. */
	template <typename T>
	void AddRecord(const ERecordType& type, const T& value);

	/** 타입에 대응하는 기록 값에 value 값을 뺍니다. */
	template <typename T>
	void SubRecord(const ERecordType& type, const T& value);

	template <typename T>
	T GetRecord(const ERecordType& type) const;

	template <typename T>
	void SetRecord(const ERecordType& type, const T& value);

	/** 게임 플레이 시작 시간을 얻습니다. */
	const std::string& GetStartSystemTime() const { return startSystemTime_; }

private:
	/** 정수 타입의 기록 값입니다. */
	std::map<ERecordType, int32_t> integerRecords_;

	/** 부동 소수점 타입의 기록 값입니다. */
	std::map<ERecordType, float> floatRecords_;

	/** 게임 플레이 시작 시간입니다. */
	std::string startSystemTime_;
};