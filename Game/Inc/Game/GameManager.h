#pragma once

#include <map>

#include "Utils/Macro.h"

/** Ŭ���� ���� �����Դϴ�. */
class GamePlayRecorder;

/** ���� �÷��� ����Դϴ�. */
struct GamePlayRecord
{
	float   playTime           = 0.0f; // �÷��� Ÿ���Դϴ�.
	float   healHp             = 0.0f; // ȸ���� ü���Դϴ�.
	float   lostHp             = 0.0f; // ���� ü���Դϴ�.
	float   healMp             = 0.0f; // ȸ���� �����Դϴ�.
	float   lostMp             = 0.0f; // ���� �����Դϴ�.
	int32_t getCoin            = 0; // ȹ���� ���� ���Դϴ�.
	int32_t useSkill           = 0; // ����� ��ų ���Դϴ�.
	int32_t genFire            = 0; // ������ �� ��ƼƼ�� ���Դϴ�.
	int32_t genCoin            = 0; // ������ ������ ���Դϴ�.
	int32_t genRedPotion       = 0; // ������ ����(HP ȸ��) ���� ��ƼƼ�� ���Դϴ�.
	int32_t genBluePotion      = 0; // ������ �Ķ�(MP ȸ��) ���� ��ƼƼ�� ���Դϴ�.
	int32_t genPowerRedPotion  = 0; // ������ ����(HP ��ü ȸ��) �Ŀ� ���� ��ƼƼ�� ���Դϴ�.
	int32_t genPowerBluePotion = 0; // ������ �Ķ�(MP ��ü ȸ��) �Ŀ� ���� ��ƼƼ�� ���Դϴ�.

	static const uint32_t MAX_TIME_LENGTH = 21;
	char startPlayTime[MAX_TIME_LENGTH]; // ���� ���� �ð��Դϴ�.
	char endPlayTime[MAX_TIME_LENGTH];   // ���� ���� �ð��Դϴ�.
};

/** 
 * ��ü���� ������ �Ӽ��� �����ϴ� ��ƼƼ�Դϴ�. 
 * �̶�, �� �Ŵ��� Ŭ������ �̱����Դϴ�.
 */
class GameManager
{
public:
	DISALLOW_COPY_AND_ASSIGN(GameManager);

	/** ���� �Ŵ����� �̱��� ��ü �����ڸ� ����ϴ�. */
	static GameManager& GetRef();

	/** ���� �Ŵ����� �̱��� ��ü �����͸� ����ϴ�. */
	static GameManager* GetPtr();

	/** �̸��� �����ϴ� ���� ���� ����ϴ�. */
	float GetConfigValue(const std::string& name);

	/** ���� �÷��� ����� �߰��մϴ�. */
	void AddGamePlayRecord(const GamePlayRecorder* gamePlayRecorder);

	/** �ֱ� ���� �÷��� ����� ����ϴ�. */
	const GamePlayRecord* GetRecentGamePlayRecord() const;

	/** ���� ���� �÷��� ��Ͽ� ���� Getter �Դϴ�. */
	float GetTotalPlayTime() const { return totalPlayTime_; }
	float GetTotalCoin() const { return totalCoin_; };
	int32_t GetTotalUseSkill() const { return totalUseSkill_; }
	float GetTotalHealHp() const { return totalHealHp_; }
	float GetTotalLostHp() const { return totalLostHp_; }
	float GetTotalHealMp() const { return totalHealMp_; }
	float GetTotalLostMp() const { return totalLostMp_; }

private:
	/** IApp���� ���� �Ŵ����� ���ο� ������ �� �ֵ��� ����. */
	friend class IApp;

	/**
	 * ���� �Ŵ����� �⺻ �����ڿ� �� ���� �Ҹ����Դϴ�.
	 * �̱������� �����ϱ� ���� private���� ������ϴ�.
	 */
	GameManager() = default;
	virtual ~GameManager() {}

	/** ���� �Ŵ����� �ʱ�ȭ/������ IApp ���ο����� ����˴ϴ�. */
	void Startup();
	void Shutdown();

	/** ���� ���� �ε��մϴ�. */
	void LoadConfigs(const std::string& path);

	/** ���� �÷��� ��� ���� �ε��մϴ�. */
	void LoadRecords(const std::string& path);

private:
	/** ���� �Ŵ����� �̱��� ��ü�Դϴ�. */
	static GameManager singleton_;

	/** ���� ���� ����Դϴ�. */
	std::string configPath_;

	/** ���� �÷��� ��� ���� ����Դϴ�. */
	std::string recordPath_;

	/** �̸��� �����ϴ� ���� ���Դϴ�. */
	std::map<std::string, float> configValues_;

	/** ���� �÷��� ����Դϴ�. */
	std::vector<GamePlayRecord> gamePlayRecords_;

	/** �÷��̾ �÷����� ��ü �ð��Դϴ�. */
	float totalPlayTime_ = 0.0f;

	/** �÷��̾ ȹ���� ��ü ���� �� �Դϴ�. */
	int32_t totalCoin_ = 0;

	/** �÷��̾ ������ ��ü ��ų �� �Դϴ�. */
	int32_t totalUseSkill_ = 0;

	/** �÷��̾ ȸ���� ��ü HP�Դϴ�. */
	float totalHealHp_ = 0.0f;

	/** �÷��̾ ���� ��ü HP�Դϴ�. */
	float totalLostHp_ = 0.0f;

	/** �÷��̾ ȸ���� ��ü MP�Դϴ�. */
	float totalHealMp_ = 0.0f;

	/** �÷��̾ ���� ��ü MP�Դϴ�. */
	float totalLostMp_ = 0.0f;
};
