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

void IGameScene::AddRenderEntity(const std::string& name, IEntity2D* renderEntity)
{
	auto it = renderEntities_.find(name);
	ASSERTION(it == renderEntities_.end(), "Already exist %s render entity in game scene.");

	renderEntities_.insert({ name, renderEntity });
}

void IGameScene::RemoveRenderEntity(const std::string& name)
{
	auto it = renderEntities_.find(name);
	ASSERTION(it != renderEntities_.end(), "Can't find %s render entity in game scene.");

	renderEntities_.erase(it);
}
