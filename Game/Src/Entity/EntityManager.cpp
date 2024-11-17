#include "Entity/EntityManager.h"
#include "Utils/Assertion.h"

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
	for (uint32_t index = 0; index < entities_.size(); ++index)
	{
		IEntity* entityPtr = entities_[index].first.get();
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

	if (entities_[entityID].first)
	{
		if (entities_[entityID].first->IsInitialized())
		{
			entities_[entityID].first->Release();
		}

		entities_[entityID].first.reset();
		entities_[entityID].second = false;
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
	for (std::size_t index = 0; index < entities_.size(); ++index)
	{
		if (entities_[index].first)
		{
			if (entities_[index].first->IsInitialized())
			{
				entities_[index].first->Release();
			}

			entities_[index].first.reset();
			entities_[index].second = false;
		}
	}
}
