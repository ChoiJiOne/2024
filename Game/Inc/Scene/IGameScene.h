#pragma once

#include <string>
#include <map>

#include "Entity/IEntity.h"
#include "Entity/IEntity2D.h"
#include "Utils/Macro.h"

/** 게임 씬 인터페이스입니다. */
class IGameScene
{
public:
	IGameScene() {}
	virtual ~IGameScene() {}

	DISALLOW_COPY_AND_ASSIGN(IGameScene);

	virtual void Tick(float deltaSeconds) = 0;
	virtual void Render() = 0;
	virtual void Enter() = 0;
	virtual void Exit() = 0;

	/** 현재 씬에 진입했는지 확인합니다. */
	bool IsEnter() { return bIsEnter_; }

	/** 씬 전환이 감지되었는지 확인합니다. */
	bool IsSceneSwitched() { return bIsSwitched_; }

	/** 전환할 씬의 포인터 값을 얻습니다. */
	IGameScene* GetSwitchScene() { return switchScene_; }

	/** 업데이트할 엔티티를 추가합니다. 이때, 이름은 고유해야 합니다. */
	void AddUpdateEntity(const std::string& name, IEntity* updateEntity);

	/** 업데이트할 엔티티를 얻습니다. */
	template <typename TEntity>
	TEntity* GetUpdateEntity(const std::string& name)
	{
		auto it = updateEntites_.find(name);
		if (it == updateEntites_.end())
		{
			return nullptr;
		}

		return reinterpret_cast<TEntity*>(it->second);
	}

	/** 업데이트할 엔티티를 삭제합니다. */
	void RemoveUpdateEntity(const std::string& name);

	/** 렌더링할 엔티티를 추가합니다. 이때, 이름은 고유해야 합니다. */
	void AddRenderEntity(const std::string& name, IEntity2D* renderEntity);

	/** 렌더링할 엔티티를 얻습니다. */
	template <typename TEntity2D>
	TEntity2D* GetRenderEntity(const std::string& name)
	{
		auto it = renderEntities_.find(name);
		if (it == renderEntities_.end())
		{
			return nullptr;
		}

		return reinterpret_cast<TEntity2D*>(it->second);
	}

	/** 렌더링할 엔티티를 삭제합니다. */
	void RemoveRenderEntity(const std::string& name);
	
protected:
	/** 업데이트할 엔티티의 우선순위 설정을 위한 구조체입니다. */
	struct UpdateEntityOrder 
	{
		bool operator()(const IEntity*& lhs, const IEntity*& rhs) const
		{
			return lhs->GetTickOrder() < rhs->GetTickOrder();
		}
	};

	/** 렌더링할 엔티티의 우선순위 설정을 위한 구조체입니다. */
	struct RenderEntityOrder
	{
		bool operator()(const IEntity2D*& lhs, const IEntity2D*& rhs) const
		{
			return lhs->GetRenderOrder() < rhs->GetRenderOrder();
		}
	};

protected:
	/** 현재 씬에 진입했는지 확인합니다. */
	bool bIsEnter_ = false;

	/** 씬 전환이 감지되었는지 확인합니다. */
	bool bIsSwitched_ = false;

	/** 전환할 씬의 포인터입니다. */
	IGameScene* switchScene_ = nullptr;

	/** 업데이트할 엔티티입니다. */
	std::map<std::string, IEntity*, UpdateEntityOrder> updateEntites_;

	/** 렌더링할 엔티티입니다. */
	std::map<std::string, IEntity2D*, RenderEntityOrder> renderEntities_;
};