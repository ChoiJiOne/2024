#include "Scene/IGameScene.h"
#include "Utils/Assertion.h"

void IGameScene::AddUpdateEntity(const std::string& name, IEntity* updateEntity)
{
	auto it = updateEntites_.find(name);
	ASSERTION(it == updateEntites_.end(), "Already exist %s update entity in game scene.");

	updateEntites_.insert({ name, updateEntity });
}

void IGameScene::RemoveUpdateEntity(const std::string& name)
{
	auto it = updateEntites_.find(name);
	ASSERTION(it != updateEntites_.end(), "Can't find %s update entity in game scene.");

	updateEntites_.erase(it);
}
