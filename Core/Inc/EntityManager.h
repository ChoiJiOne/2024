#pragma once

#include <array>
#include <memory>

#include "IEntity.h"

/** ��ƼƼ �Ŵ����� �̱����Դϴ�. */
class EntityManager
{
public:
	DISALLOW_COPY_AND_ASSIGN(EntityManager);

	static EntityManager& Get();

	template <typename TEntity, typename... Args>
	TEntity* Create(Args&&... args)
	{
		if (!(0 <= cacheSize_ && cacheSize_ < MAX_ENTITY_SIZE))
		{
			return nullptr;
		}

		int32_t entityID = -1;
		for (uint32_t index = 0; index < cacheSize_; ++index)
		{
			if (!entities_[index] && !usage_[index])
			{
				entityID = static_cast<int32_t>(index);
				break;
			}
		}

		if (entityID == -1)
		{
			entityID = cacheSize_++;
		}

		usage_[entityID] = true;
		entities_[entityID] = std::make_unique<TEntity>(args...);

		return reinterpret_cast<TEntity*>(entities_[entityID].get());
	}

	void Destroy(const IEntity* entity);

private:
	friend class IApp;

	EntityManager() = default;
	virtual ~EntityManager() {}

	void Cleanup();

private:
	static const uint32_t MAX_ENTITY_SIZE = 200;

	uint32_t cacheSize_ = 0;
	std::array<std::unique_ptr<IEntity>, MAX_ENTITY_SIZE> entities_;
	std::array<bool, MAX_ENTITY_SIZE> usage_;
};