#include <algorithm>

#include "Scene/IGameScene.h"
#include "Utils/Assertion.h"

void IGameScene::Tick(float deltaSeconds)
{
	for (auto& updateEntity : updateEntites_)
	{
		updateEntity->Tick(deltaSeconds);
	}
}

void IGameScene::AddUpdateEntity(IEntity* entity)
{
	updateEntites_.push_back(entity);
	updateEntites_.sort(IGameScene::CompareUpdateOrder);
}

void IGameScene::RemoveUpdateEntity(IEntity* entity)
{
	updateEntites_.remove(entity);
}

void IGameScene::AddRenderEntity(IEntity2D* entity)
{
	renderEntities_.push_back(entity);
	renderEntities_.sort(IGameScene::CompareRenderOrder);
}

void IGameScene::RemoveRenderEntity(IEntity2D* entity)
{
	renderEntities_.remove(entity);
}