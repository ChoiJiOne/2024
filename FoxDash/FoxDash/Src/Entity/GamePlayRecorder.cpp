#include "Entity/GamePlayRecorder.h"
#include "Utils/Assertion.h"
#include "Utils/Utils.h"

GamePlayRecorder::GamePlayRecorder()
{
	integerRecords_ =
	{
		{ ERecordType::GET_COIN,              0 },
		{ ERecordType::USE_SKILL,             0 },
		{ ERecordType::GEN_FIRE,              0 },
		{ ERecordType::GEN_COIN,              0 },
		{ ERecordType::GEN_RED_POTION,        0 },
		{ ERecordType::GEN_BLUE_POTION,       0 },
		{ ERecordType::GEN_POWER_RED_POTION,  0 },
		{ ERecordType::GEN_POWER_BLUE_POTION, 0 },
	};

	floatRecords_ =
	{
		{ ERecordType::PLAY_TIME, 0.0f },
		{ ERecordType::HEAL_HP,   0.0f },
		{ ERecordType::LOST_HP,   0.0f },
		{ ERecordType::HEAL_MP,   0.0f },
		{ ERecordType::LOST_MP,   0.0f },
	};

	startSystemTime_ = GetCurrentSystemTimeAsString();

	bIsInitialized_ = true;
}

GamePlayRecorder::~GamePlayRecorder()
{
	if (bIsInitialized_)
	{
		Release();
	}
}

template <>
void GamePlayRecorder::AddRecord(const ERecordType& type, const int32_t& value)
{
	auto& it = integerRecords_.find(type);
	if (it != integerRecords_.end())
	{
		it->second += value;
	}
}

template <>
void GamePlayRecorder::AddRecord(const ERecordType& type, const float& value)
{
	auto& it = floatRecords_.find(type);
	if (it != floatRecords_.end())
	{
		it->second += value;
	}
}

template <>
void GamePlayRecorder::SubRecord(const ERecordType& type, const int32_t& value)
{
	auto& it = integerRecords_.find(type);
	if (it != integerRecords_.end())
	{
		it->second -= value;
	}
}

template <>
void GamePlayRecorder::SubRecord(const ERecordType& type, const float& value)
{
	auto& it = floatRecords_.find(type);
	if (it != floatRecords_.end())
	{
		it->second -= value;
	}
}

template <>
int32_t GamePlayRecorder::GetRecord(const ERecordType& type) const
{
	return integerRecords_.at(type);
}

template <>
float GamePlayRecorder::GetRecord(const ERecordType& type) const
{
	return floatRecords_.at(type);
}

template <>
void GamePlayRecorder::SetRecord(const ERecordType& type, const int32_t& value)
{
	int32_t& record = integerRecords_.at(type);
	record = value;
}

template <>
void GamePlayRecorder::SetRecord(const ERecordType& type, const float& value)
{
	float& record = floatRecords_.at(type);
	record = value;
}

void GamePlayRecorder::Tick(float deltaSeconds)
{
	floatRecords_.at(ERecordType::PLAY_TIME) += deltaSeconds;
}

void GamePlayRecorder::Release()
{
	CHECK(bIsInitialized_);

	bIsInitialized_ = false;
}