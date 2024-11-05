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
		return; // �ش� ��ƼƼ�� �̹� �Ҵ� ���� �Ǿ��ų�, ��ƼƼ �Ŵ����� ���� 
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
