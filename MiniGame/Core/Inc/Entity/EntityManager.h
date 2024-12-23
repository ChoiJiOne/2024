#pragma once

#include <cstdint>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include "Entity/IEntity.h"
#include "Utils/Macro.h"

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
		int32_t entityID = -1;
		for (uint32_t index = 0; index < entities_.size(); ++index)
		{
			if (!entities_[index].first && !entities_[index].second)
			{
				entityID = static_cast<int32_t>(index);
				break;
			}
		}

		if (entityID == -1)
		{
			entityID = entities_.size();
			entities_.push_back({ nullptr, true });
			entities_[entityID].first = std::make_unique<TEntity>(args...);
		}
		else
		{
			entities_[entityID].second = true;
			entities_[entityID].first = std::make_unique<TEntity>(args...);
		}

		return reinterpret_cast<TEntity*>(entities_[entityID].first.get());
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
	/** IApp���� ��ƼƼ �Ŵ����� ���ο� ������ �� �ֵ��� ���� */
	friend class IApp;

	/**
	 * ��ƼƼ �Ŵ����� �⺻ �����ڿ� ���� �Ҹ����Դϴ�.
	 * �̱������� �����ϱ� ���� private���� ������ϴ�.
	 */
	EntityManager() = default;
	virtual ~EntityManager() {}

	/** ��ƼƼ �Ŵ����� ����� IApp ���ο����� ����˴ϴ�. */
	void Shutdown();

private:
	/** ��ƼƼ �Ŵ����� �̱��� ��ü�Դϴ�. */
	static EntityManager singleton_;
	
	/** ��ƼƼ�� �ش� ��ƼƼ�� ��� �����Դϴ�. */
	std::vector<std::pair<std::unique_ptr<IEntity>, bool>> entities_;

	/** �̸��� ���� ��ƼƼ�Դϴ�. */
	std::map<std::string, IEntity*> namedEntities_;
};