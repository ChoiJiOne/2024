#pragma once

#include <map>
#include <string>

#include "IEntity.h"

/** ���� �÷��� ����� �����ϴ� ��ƼƼ�Դϴ�. */
class GamePlayRecorder : public IEntity
{
public:
	/** ������ ����� �����Դϴ�. */
	enum class ERecordType
	{
		PLAY_TIME = 0x00, // �÷��� Ÿ���Դϴ�.
		HEAL_HP = 0x01, // ȸ���� ü���Դϴ�.
		LOST_HP = 0x02, // ���� ü���Դϴ�.
		HEAL_MP = 0x03, // ȸ���� �����Դϴ�.
		LOST_MP = 0x04, // ���� �����Դϴ�.
		GET_COIN = 0x06, // ȹ���� ���� ���Դϴ�.
		USE_SKILL = 0x07, // ����� ��ų ���Դϴ�.
		GEN_FIRE = 0x08, // ������ �� ��ƼƼ�� ���Դϴ�.
		GEN_COIN = 0x09, // ������ ������ ���Դϴ�.
		GEN_RED_POTION = 0x0A, // ������ ����(HP ȸ��) ���� ��ƼƼ�� ���Դϴ�.
		GEN_BLUE_POTION = 0x0B, // ������ �Ķ�(MP ȸ��) ���� ��ƼƼ�� ���Դϴ�.
		GEN_POWER_RED_POTION = 0x0C, // ������ ����(HP ��ü ȸ��) �Ŀ� ���� ��ƼƼ�� ���Դϴ�.
		GEN_POWER_BLUE_POTION = 0x0D, // ������ �Ķ�(MP ��ü ȸ��) �Ŀ� ���� ��ƼƼ�� ���Դϴ�.
	};

public:
	GamePlayRecorder();
	virtual ~GamePlayRecorder();

	DISALLOW_COPY_AND_ASSIGN(GamePlayRecorder);

	virtual void Tick(float deltaSeconds) override;
	virtual void Release() override;

	/** Ÿ�Կ� �����ϴ� ��� ���� value ���� ���մϴ�. */
	template <typename T>
	void AddRecord(const ERecordType& type, const T& value);

	/** Ÿ�Կ� �����ϴ� ��� ���� value ���� ���ϴ�. */
	template <typename T>
	void SubRecord(const ERecordType& type, const T& value);

	template <typename T>
	T GetRecord(const ERecordType& type) const;

	template <typename T>
	void SetRecord(const ERecordType& type, const T& value);

	/** ���� �÷��� ���� �ð��� ����ϴ�. */
	const std::string& GetStartSystemTime() const { return startSystemTime_; }

private:
	/** ���� Ÿ���� ��� ���Դϴ�. */
	std::map<ERecordType, int32_t> integerRecords_;

	/** �ε� �Ҽ��� Ÿ���� ��� ���Դϴ�. */
	std::map<ERecordType, float> floatRecords_;

	/** ���� �÷��� ���� �ð��Դϴ�. */
	std::string startSystemTime_;
};