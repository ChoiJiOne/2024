#include <json/json.h>

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

float GameManager::GetConfigValue(const std::string& name)
{
	auto it = configValues_.find(name);
	ASSERTION(it != configValues_.end(), "Can't find %s in game config file.", name.c_str());
	
	return it->second;
}

void GameManager::Startup()
{
	std::string gameConfigPath = "Resource\\Game\\GameConfig.json";

	std::vector<uint8_t> buffer;
	std::string errMsg;
	ASSERTION(ReadFile(gameConfigPath, buffer, errMsg), "%s", errMsg.c_str());

	std::string jsonString(buffer.begin(), buffer.end());
	Json::Value root;
	Json::Reader reader;
	ASSERTION(reader.parse(jsonString, root), "Failed to parse '%s' file.", gameConfigPath.c_str());

	Json::Value::Members members = root.getMemberNames();
	for (uint32_t index = 0; index < members.size(); ++index)
	{
		const std::string& name = members[index];
		if (root[name].isDouble() && !root[name].isNull())
		{
			float configValue = root[name].asFloat();
			configValues_.insert({ name , configValue });
		}
	}
}

void GameManager::Shutdown()
{
}
