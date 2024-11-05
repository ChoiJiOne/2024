#include "Entity/EntityManager.h"
#include "Assertion.h"

EntityManager EntityManager::singleton_;

EntityManager& EntityManager::GetRef()
{
	return singleton_;
}

EntityManager* EntityManager::GetPtr()
{
	return &singleton_;
}

void EntityManager::Destroy(const IEntity* entity)
{
	int32_t entityID = -1;
	for (uint32_t index = 0; index < entitySize_; ++index)
	{
		IEntity* entityPtr = entities_[index].get();
		if (entity == entityPtr)
		{
			entityID = static_cast<int32_t>(index);
			break;
		}
	}

	if (entityID == -1)
	{
		return; // 해당 엔티티는 이미 할당 해제 되었거나, 엔티티 매니저에 의해 할당 해제된 엔티티입니다.
	}

	if (entities_[entityID])
	{
		if (entities_[entityID]->IsInitialized())
		{
			entities_[entityID]->Release();
		}

		entities_[entityID].reset();
		usages_[entityID] = false;
	}
}

void EntityManager::Register(const std::string& name, IEntity* entity)
{
	auto it = namedEntities_.find(name);
	ASSERTION(it == namedEntities_.end(), "Already register '%s'", name.c_str());

	namedEntities_.insert({ name, entity });
}

bool EntityManager::IsRegistration(const std::string& name)
{
	return namedEntities_.find(name) != namedEntities_.end();
}

void EntityManager::Unregister(const std::string& name)
{
	auto it = namedEntities_.find(name);
	ASSERTION(it != namedEntities_.end(), "Can't find '%s' in EntityManager.", name.c_str());

	namedEntities_.erase(it);
}

void EntityManager::Shutdown()
{
	for (std::size_t index = 0; index < entitySize_; ++index)
	{
		if (entities_[index])
		{
			if (entities_[index]->IsInitialized())
			{
				entities_[index]->Release();
			}

			entities_[index].reset();
			usages_[index] = false;
		}
	}

	entitySize_ = 0;
}
