#pragma once

#include <map>

#include "Utils/Macro.h"

/** 클래스 전방 선언입니다. */
class GamePlayRecorder;

/** 게임 플레이 기록입니다. */
struct GamePlayRecord
{
	float   playTime           = 0.0f; // 플레이 타임입니다.
	float   healHp             = 0.0f; // 회복한 체력입니다.
	float   lostHp             = 0.0f; // 잃은 체력입니다.
	float   healMp             = 0.0f; // 회복한 마나입니다.
	float   lostMp             = 0.0f; // 잃은 마나입니다.
	int32_t getCoin            = 0; // 획득한 코인 수입니다.
	int32_t useSkill           = 0; // 사용한 스킬 수입니다.
	int32_t genFire            = 0; // 생성된 불 엔티티의 수입니다.
	int32_t genCoin            = 0; // 생성된 코인의 수입니다.
	int32_t genRedPotion       = 0; // 생성된 빨간(HP 회복) 포션 엔티티의 수입니다.
	int32_t genBluePotion      = 0; // 생성된 파란(MP 회복) 포션 엔티티의 수입니다.
	int32_t genPowerRedPotion  = 0; // 생성된 빨간(HP 전체 회복) 파워 포션 엔티티의 수입니다.
	int32_t genPowerBluePotion = 0; // 생성된 파란(MP 전체 회복) 파워 포션 엔티티의 수입니다.

	static const uint32_t MAX_TIME_LENGTH = 21;
	char startPlayTime[MAX_TIME_LENGTH]; // 게임 시작 시간입니다.
	char endPlayTime[MAX_TIME_LENGTH];   // 게임 종료 시간입니다.
};

/** 
 * 전체적인 게임의 속성을 관리하는 엔티티입니다. 
 * 이때, 이 매니저 클래스는 싱글턴입니다.
 */
class GameManager
{
public:
	DISALLOW_COPY_AND_ASSIGN(GameManager);

	/** 게임 매니저의 싱글턴 객체 참조자를 얻습니다. */
	static GameManager& GetRef();

	/** 게임 매니저의 싱글턴 객체 포인터를 얻습니다. */
	static GameManager* GetPtr();

	/** 이름에 대응하는 설정 값을 얻습니다. */
	float GetConfigValue(const std::string& name);

	/** 게임 플레이 기록을 추가합니다. */
	void AddGamePlayRecord(const GamePlayRecorder* gamePlayRecorder);

private:
	/** IApp에서 게임 매니저의 내부에 접근할 수 있도록 설정. */
	friend class IApp;

	/**
	 * 게임 매니저의 기본 생성자와 빈 가상 소멸자입니다.
	 * 싱글턴으로 구현하기 위해 private으로 숨겼습니다.
	 */
	GameManager() = default;
	virtual ~GameManager() {}

	/** 게임 매니저의 초기화/해제는 IApp 내부에서만 수행됩니다. */
	void Startup();
	void Shutdown();

	/** 설정 값을 로딩합니다. */
	void LoadConfigs(const std::string& path);

	/** 게임 플레이 기록 값을 로딩합니다. */
	void LoadRecords(const std::string& path);

private:
	/** 게임 매니저의 싱글턴 객체입니다. */
	static GameManager singleton_;

	/** 설정 파일 경로입니다. */
	std::string configPath_;

	/** 게임 플레이 기록 파일 경로입니다. */
	std::string recordPath_;

	/** 이름에 대응하는 설정 값입니다. */
	std::map<std::string, float> configValues_;

	/** 게임 플레이 기록입니다. */
	std::vector<GamePlayRecord> gamePlayRecords_;
};
