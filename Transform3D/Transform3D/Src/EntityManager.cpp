#include "EntityManager.h"

/**
 * @brief 평가식을 검사합니다.
 *
 * @param Expression 검사할 호출값입니다.
 *
 * @note
 * - Debug 모드와 Release 모드에서는 평가식을 검사하지만 Shipping 모드에서는 평가식을 검사하지 않습니다.
 * - 디버거가 존재하면 브레이크 포인트가 걸립니다.
 */
#if defined(DEBUG_MODE) || defined(RELEASE_MODE) || defined(DEVELOPMENT_MODE)
#ifndef CHECK
#define CHECK(Expression)\
{\
	if (!(bool)(Expression))                                                                                              \
	{                                                                                                                     \
		__debugbreak();                                                                                                   \
	}                                                                                                                     \
}
#endif
#else // defined(SHIPPING_MODE)
#ifndef CHECK
#define CHECK(Expression, ...) ((void)(Expression))
#endif
#endif

EntityManager& EntityManager::Get()
{
	static EntityManager instance;
	return instance;
}

void EntityManager::Startup()
{
	CHECK(!bIsStartup_);

	bIsStartup_ = true;
}

void EntityManager::Shutdown()
{
	CHECK(bIsStartup_);

	for (auto& cache : cache_)
	{
		if (cache)
		{
			if (cache->IsInitialized())
			{
				cache->Release();
			}

			cache.reset();
		}
	}

	bIsStartup_ = false;
}

void EntityManager::Destroy(const EntityID& entityID)
{
	CHECK(0 <= entityID && entityID < cacheSize_);

	if (cache_[entityID])
	{
		if (cache_[entityID]->IsInitialized())
		{
			cache_[entityID]->Release();
		}

		cache_[entityID].reset();
	}
}

void EntityManager::Destroy(const IEntity* entity)
{
	EntityID entityID = -1;
	for (uint32_t index = 0; index < cacheSize_; ++index)
	{
		IEntity* cacheEntity = cache_[index].get();
		if (entity == cacheEntity)
		{
			entityID = static_cast<EntityID>(index);
			break;
		}
	}

	if (entityID != -1 && cache_[entityID])
	{
		if (cache_[entityID]->IsInitialized())
		{
			cache_[entityID]->Release();
		}

		cache_[entityID].reset();
	}
}