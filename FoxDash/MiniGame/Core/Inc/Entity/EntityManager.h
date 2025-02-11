#pragma once

#include <cstdint>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include "Entity/IEntity.h"
#include "Utils/Macro.h"

/**
 * Entity를 생성/질의/삭제를 수행하는 매니저입니다.
 * 이때, 이 매니저 클래스는 싱글턴입니다.
 */
class EntityManager
{
public:
	DISALLOW_COPY_AND_ASSIGN(EntityManager);

	/** 엔티티 매니저의 싱글턴 객체 참조자를 얻습니다. */
	static EntityManager& GetRef();

	/** 엔티티 매니저의 싱글턴 포인터를 얻습니다. */
	static EntityManager* GetPtr();

	/** 엔티티를 생성합니다. */
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

	/** 생성한 엔티티를 파괴합니다. */
	void Destroy(const IEntity* entity);

	/** 엔티티를 엔티티 매니저에 등록합니다. */
	void Register(const std::string& name, IEntity* entity);

	/** 엔티티 이름이 등록 되었는지 확인합니다. */
	bool IsRegistration(const std::string& name);

	/** 엔티티 매니저에 등록을 해제합니다. */
	void Unregister(const std::string& name);

	/** 이름에 대응하는 엔티티를 얻습니다. */
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
	/** IApp에서 엔티티 매니저의 내부에 접근할 수 있도록 설정 */
	friend class IApp;

	/**
	 * 엔티티 매니저의 기본 생성자와 가상 소멸자입니다.
	 * 싱글턴으로 구현하기 위해 private으로 숨겼습니다.
	 */
	EntityManager() = default;
	virtual ~EntityManager() {}

	/** 엔티티 매니저의 종료는 IApp 내부에서만 수행됩니다. */
	void Shutdown();

private:
	/** 엔티티 매니저의 싱글턴 객체입니다. */
	static EntityManager singleton_;
	
	/** 엔티티와 해당 엔티티의 사용 여부입니다. */
	std::vector<std::pair<std::unique_ptr<IEntity>, bool>> entities_;

	/** 이름을 가진 엔티티입니다. */
	std::map<std::string, IEntity*> namedEntities_;
};