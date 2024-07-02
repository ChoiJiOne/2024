#pragma once

#include <array>
#include <memory>

#include "IEntity.h"
#include "IManager.h"


namespace GameMaker
{
/**
 * @brief ���� ���� ��ƼƼ�� �����ϴ� �Ŵ����Դϴ�.
 * 
 * @note �� Ŭ������ �̱����Դϴ�.
 */
class EntityManager : public IManager
{
public:
	/**
	 * @brief ��ƼƼ �Ŵ����� ���� �����ڿ� ���� �����ڸ� ��������� �����մϴ�.
	 */
	DISALLOW_COPY_AND_ASSIGN(EntityManager);


	/**
	 * @brief ��ƼƼ �Ŵ����� �����ڸ� ����ϴ�.
	 *
	 * @return ��ƼƼ �Ŵ����� �����ڸ� ��ȯ�մϴ�.
	 */
	static EntityManager& Get();


	/**
	 * @brief ��ƼƼ �Ŵ����� ����� �����մϴ�.
	 *
	 * @note �� �޼���� �� ���� ȣ��Ǿ�� �մϴ�.
	 */
	virtual void Startup() override;


	/**
	 * @brief ��ƼƼ �Ŵ����� ����� �����մϴ�.
	 *
	 * @note
	 * - ���ø����̼� ���� ���� �� �޼��带 �ݵ�� ȣ���Ͽ� ���� ��ƼƼ�� �����ؾ� �մϴ�.
	 * - �� �޼���� �ݵ�� �� ���� ȣ��Ǿ�� �մϴ�.
	 */
	virtual void Shutdown() override;


	/**
	 * @brief ��ƼƼ�� �����մϴ�.
	 *
	 * @param args ��ƼƼ�� �����ڿ� ������ ���ڵ��Դϴ�.
	 *
	 * @return ������ ��ƼƼ�� �����͸� ��ȯ�մϴ�. ��ƼƼ ������ �����ϸ� nullptr�� ��ȯ�մϴ�.
	 */
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
			if (!cache_[index] && !usage_[index])
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
		cache_[entityID] = std::make_unique<TEntity>(args...);

		return reinterpret_cast<TEntity*>(cache_[entityID].get());
	}


	/**
	 * @brief ��ƼƼ �Ŵ����� �����ϴ� ��ƼƼ�� �����մϴ�.
	 *
	 * @param entity ������ ��ƼƼ �������Դϴ�.
	 */
	void Destroy(const IEntity* entity)
	{
		int32_t entityID = -1;
		for (uint32_t index = 0; index < cacheSize_; ++index)
		{
			IEntity* cache = cache_[index].get();
			if (entity == cache)
			{
				entityID = static_cast<int32_t>(index);
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
			usage_[entityID] = false;
		}
	}


private:
	/**
	 * @brief ��ƼƼ �Ŵ����� ����Ʈ �����ڿ� �� ���� �Ҹ��ڸ� �����մϴ�.
	 */
	DEFAULT_CONSTRUCTOR_AND_VIRTUAL_DESTRUCTOR(EntityManager);


private:
	/**
	 * @brief ������ �� �ִ� �ִ� ��ƼƼ ���Դϴ�.
	 */
	static const uint32_t MAX_ENTITY_SIZE = 200;


	/**
	 * @brief ĳ�� ũ���Դϴ�.
	 */
	uint32_t cacheSize_ = 0;


	/**
	 * @brief ��ƼƼ�� ĳ���Դϴ�.
	 */
	std::array<std::unique_ptr<IEntity>, MAX_ENTITY_SIZE> cache_;


	/**
	 * @brief ��ƼƼ�� ��� �����Դϴ�.
	 */
	std::array<bool, MAX_ENTITY_SIZE> usage_;
};

}