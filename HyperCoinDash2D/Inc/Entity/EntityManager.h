#pragma once

#include <array>
#include <cstdint>
#include <map>
#include <memory>
#include <string>

#include "Entity/IEntity.h"
#include "Macro.h"

/**
 * Entity�� ����/����/������ �����ϴ� �Ŵ����Դϴ�.
 * �̶�, �� �Ŵ��� Ŭ������ �̱����Դϴ�.
 */
class EntityManager
{
public:
	DISALLOW_COPY_AND_ASSIGN(EntityManager);

	/** ��ƼƼ �Ŵ����� �̱��� ��ü �����ڸ� ����ϴ�. */
	static EntityManager& GetRef();

	/** ��ƼƼ �Ŵ����� �̱��� �����͸� ����ϴ�. */
	static EntityManager* GetPtr();

	/** ��ƼƼ�� �����մϴ�. */
	template <typename TEntity, typename... Args>
	TEntity* Create(Args&&... args)
	{
		if (!(0 <= entitySize_ && entitySize_ < MAX_ENTITY_SIZE))
		{
			return nullptr;
		}

		int32_t entityID = -1;
		for (uint32_t index = 0; index < entitySize_; ++index)
		{
			if (!entities_[index] && !usages_[index])
			{
				entityID = static_cast<int32_t>(index);
				break;
			}
		}

		if (entityID == -1)
		{
			entityID = entitySize_++;
		}

		usages_[entityID] = true;
		entities_[entityID] = std::make_unique<TEntity>(args...);

		return reinterpret_cast<TEntity*>(entities_[entityID].get());
	}

	/** ������ ��ƼƼ�� �ı��մϴ�. */
	void Destroy(const IEntity* entity);

	/** ��ƼƼ�� ��ƼƼ �Ŵ����� ����մϴ�. */
	void Register(const std::string& name, IEntity* entity);

	/** ��ƼƼ �̸��� ��� �Ǿ����� Ȯ���մϴ�. */
	bool IsRegistration(const std::string& name);

	/** ��ƼƼ �Ŵ����� ����� �����մϴ�. */
	void Unregister(const std::string& name);

	/** �̸��� �����ϴ� ��ƼƼ�� ����ϴ�. */
	template <typename TEntity>
	TEntity* GetByName(const std::string& name)
	{
		auto it = namedEntities_.find(name);
		if (it == namedEntities_.end())
		{
			return nullptr;
		}

		return reinterpret_cast<TEntity*>(it->second);
	}

private:
	/** GameApp���� EntityManager�� ���ο� ������ �� �ֵ��� ���� */
	friend class GameApp;

	/**
	 * ��ƼƼ �Ŵ����� �⺻ �����ڿ� ���� �Ҹ����Դϴ�.
	 * �̱������� �����ϱ� ���� private���� ������ϴ�.
	 */
	EntityManager() = default;
	virtual ~EntityManager() {}

	/** ��ƼƼ �Ŵ����� ����� GameApp ���ο����� ����˴ϴ�. */
	void Shutdown();

private:
	/** ��ƼƼ �Ŵ����� �̱��� ��ü�Դϴ�. */
	static EntityManager singleton_;

	/** ��ƼƼ �Ŵ������� �����ϴ� ��ƼƼ�� �ִ� �����Դϴ�. */
	static const uint32_t MAX_ENTITY_SIZE = 300;

	/** ��ƼƼ �Ŵ����� ��ƼƼ ũ���Դϴ�. �ִ� MAX_ENTITY_SIZE�� ���� �����մϴ�. */
	uint32_t entitySize_ = 0;

	/** ��ƼƼ�� �ش� ��ƼƼ�� ��� �����Դϴ�. */
	std::array<std::unique_ptr<IEntity>, MAX_ENTITY_SIZE> entities_;
	std::array<bool, MAX_ENTITY_SIZE> usages_;

	/** �̸��� ���� ��ƼƼ�Դϴ�. */
	std::map<std::string, IEntity*> namedEntities_;
};