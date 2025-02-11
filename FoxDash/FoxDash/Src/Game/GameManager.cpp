#include <json/json.h>

#include "Entity/GamePlayRecorder.h"
#include "Game/GameManager.h"
#include "Utils/Assertion.h"
#include "Utils/Utils.h"

GameManager GameManager::singleton_;

GameManager& GameManager::GetRef()
{
	return singleton_;
}

GameManager* GameManager::GetPtr()
{
	return &singleton_;
}

template <>
float GameManager::GetConfigValue(const std::string& name)
{
	auto it = floatConfigValues_.find(name);
	ASSERTION(it != floatConfigValues_.end(), "Can't find %s in game config file.", name.c_str());

	return it->second;
}

template <>
int32_t GameManager::GetConfigValue(const std::string& name)
{
	auto it = integerConfigValues_.find(name);
	ASSERTION(it != integerConfigValues_.end(), "Can't find %s in game config file.", name.c_str());

	return it->second;
}

void GameManager::AddGamePlayRecord(const GamePlayRecorder* gamePlayRecorder)
{
	GamePlayRecord gamePlayRecord;

	gamePlayRecord.playTime = gamePlayRecorder->GetRecord<float>(GamePlayRecorder::ERecordType::PLAY_TIME);
	gamePlayRecord.healHp = gamePlayRecorder->GetRecord<float>(GamePlayRecorder::ERecordType::HEAL_HP);
	gamePlayRecord.lostHp = gamePlayRecorder->GetRecord<float>(GamePlayRecorder::ERecordType::LOST_HP);
	gamePlayRecord.healMp = gamePlayRecorder->GetRecord<float>(GamePlayRecorder::ERecordType::HEAL_MP);
	gamePlayRecord.lostMp = gamePlayRecorder->GetRecord<float>(GamePlayRecorder::ERecordType::LOST_MP);
	gamePlayRecord.getCoin = gamePlayRecorder->GetRecord<int32_t>(GamePlayRecorder::ERecordType::GET_COIN);
	gamePlayRecord.useSkill = gamePlayRecorder->GetRecord<int32_t>(GamePlayRecorder::ERecordType::USE_SKILL);
	gamePlayRecord.genFire = gamePlayRecorder->GetRecord<int32_t>(GamePlayRecorder::ERecordType::GEN_FIRE);
	gamePlayRecord.genCoin = gamePlayRecorder->GetRecord<int32_t>(GamePlayRecorder::ERecordType::GEN_COIN);
	gamePlayRecord.genRedPotion = gamePlayRecorder->GetRecord<int32_t>(GamePlayRecorder::ERecordType::GEN_RED_POTION);
	gamePlayRecord.genBluePotion = gamePlayRecorder->GetRecord<int32_t>(GamePlayRecorder::ERecordType::GEN_BLUE_POTION);
	gamePlayRecord.genPowerRedPotion = gamePlayRecorder->GetRecord<int32_t>(GamePlayRecorder::ERecordType::GEN_POWER_RED_POTION);
	gamePlayRecord.genPowerBluePotion = gamePlayRecorder->GetRecord<int32_t>(GamePlayRecorder::ERecordType::GEN_POWER_BLUE_POTION);

	totalPlayTime_ += gamePlayRecord.playTime;
	totalCoin_ += gamePlayRecord.getCoin;
	totalUseSkill_ += gamePlayRecord.useSkill;
	totalHealHp_ += gamePlayRecord.healHp;
	totalLostHp_ += gamePlayRecord.lostHp;
	totalHealMp_ += gamePlayRecord.healMp;
	totalLostMp_ += gamePlayRecord.lostMp;

	const std::string& startPlayTime = gamePlayRecorder->GetStartSystemTime();
	std::copy(startPlayTime.begin(), startPlayTime.end(), gamePlayRecord.startPlayTime);

	std::string endPlayTime = GetCurrentSystemTimeAsString();
	std::copy(endPlayTime.begin(), endPlayTime.end(), gamePlayRecord.endPlayTime);

	gamePlayRecords_.push_back(gamePlayRecord);
}

const GamePlayRecord* GameManager::GetRecentGamePlayRecord() const
{
	if (gamePlayRecords_.empty())
	{
		return nullptr;
	}
	
	return &gamePlayRecords_.back();
}

void GameManager::Startup()
{
	configPath_ = "Resource\\Game\\GameConfig.json";
	recordPath_ = "Cache\\GameRecord.bin";

	LoadConfigs(configPath_);
	LoadRecords(recordPath_);

	for (const auto& gamePlayRecord : gamePlayRecords_)
	{
		totalPlayTime_ += gamePlayRecord.playTime;
		totalCoin_ += gamePlayRecord.getCoin;
		totalUseSkill_ += gamePlayRecord.useSkill;
		totalHealHp_ += gamePlayRecord.healHp;
		totalLostHp_ += gamePlayRecord.lostHp;
		totalHealMp_ += gamePlayRecord.healMp;
		totalLostMp_ += gamePlayRecord.lostMp;
	}
}

void GameManager::Shutdown()
{
	uint32_t recordByteSize = sizeof(GamePlayRecord);
	uint32_t byteSize = recordByteSize * static_cast<uint32_t>(gamePlayRecords_.size());

	std::vector<uint8_t> buffer(byteSize);
	std::memcpy(buffer.data(), gamePlayRecords_.data(), byteSize);

	std::string basePath = GetBasePath(recordPath_);
	std::string errMsg;
	if (!IsValidPath(basePath))
	{
		ASSERTION(MakeDirectory(basePath, errMsg), "Failed to create folder '%s'", errMsg.c_str());
	}

	ASSERTION(WriteFile(recordPath_, buffer, errMsg), "%s", errMsg.c_str());
}

void GameManager::LoadConfigs(const std::string& path)
{
	std::vector<uint8_t> buffer;
	std::string errMsg;
	ASSERTION(ReadFile(path, buffer, errMsg), "%s", errMsg.c_str());

	std::string jsonString(buffer.begin(), buffer.end());
	Json::Value root;
	Json::Reader reader;
	ASSERTION(reader.parse(jsonString, root), "Failed to parse '%s' file.", path.c_str());

	Json::Value::Members members = root.getMemberNames();
	for (uint32_t index = 0; index < members.size(); ++index)
	{
		const std::string& name = members[index];
		const Json::Value& object = root[name];

		if (!object["type"].isNull() && object["type"].isString())
		{
			const std::string& type = object["type"].asString();
			if (object["value"].isNull())
			{
				continue;
			}

			if (type == "int")
			{
				int32_t value = object["value"].asInt();
				integerConfigValues_.insert({ name, value });
			}
			else if (type == "float")
			{
				float value = object["value"].asFloat();
				floatConfigValues_.insert({ name, value });
			}
		}
	}
}

void GameManager::LoadRecords(const std::string& path)
{
	std::string basePath = GetBasePath(path);
	std::string errMsg;
	if (!IsValidPath(basePath))
	{
		ASSERTION(MakeDirectory(basePath, errMsg), "Failed to create folder '%s'", errMsg.c_str());
	}

	if (!IsValidPath(path))
	{
		return;
	}

	std::vector<uint8_t> buffer;
	ASSERTION(ReadFile(path, buffer, errMsg), "%s", errMsg.c_str());

	uint32_t bufferByteSize = static_cast<uint32_t>(buffer.size());
	uint32_t recordByteSize = sizeof(GamePlayRecord);
	uint32_t count = bufferByteSize / recordByteSize;

	GamePlayRecord* gamePlayRecordPtr = reinterpret_cast<GamePlayRecord*>(buffer.data());
	for (uint32_t index = 0; index < count; ++index)
	{
		gamePlayRecords_.push_back(gamePlayRecordPtr[index]);
	}
}
