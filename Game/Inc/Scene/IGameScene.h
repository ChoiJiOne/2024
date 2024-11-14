#pragma once

#include <string>
#include <list>

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

	virtual void Tick(float deltaSeconds);
	virtual void Render() = 0;
	virtual void Enter() = 0;
	virtual void Exit() = 0;

	/** 현재 씬에 진입했는지 확인합니다. */
	bool IsEnter() { return bIsEnter_; }

	/** 씬 전환이 감지되었는지 확인합니다. */
	bool IsSceneSwitched() { return bIsSwitched_; }

	/** 전환할 씬의 포인터 값을 얻습니다. */
	IGameScene* GetSwitchScene() { return switchScene_; }

	/** 업데이트할 엔티티를 추가합니다. */
	void AddUpdateEntity(IEntity* entity);
	
	/** 업데이트할 엔티티를 삭제합니다. */
	void RemoveUpdateEntity(IEntity* entity);

	/** 렌더링할 엔티티를 추가합니다.  */
	void AddRenderEntity(IEntity2D* entity);

	/** 렌더링할 엔티티를 삭제합니다. */
	void RemoveRenderEntity(IEntity2D* entity);

protected:
	/** 업데이트할 엔티티의 우선 순위를 비교합니다. */
	static bool CompareUpdateOrder(IEntity* lhs, IEntity* rhs)
	{
		return lhs->GetTickOrder() < rhs->GetTickOrder();
	}

	/** 렌더링할 엔티티의 우선 순위를 비교합니다. */
	static bool CompareRenderOrder(IEntity2D* lhs, IEntity2D* rhs)
	{
		return lhs->GetRenderOrder() < rhs->GetRenderOrder();
	}
	
protected:
	/** 현재 씬에 진입했는지 확인합니다. */
	bool bIsEnter_ = false;

	/** 씬 전환이 감지되었는지 확인합니다. */
	bool bIsSwitched_ = false;

	/** 전환할 씬의 포인터입니다. */
	IGameScene* switchScene_ = nullptr;

	/** 업데이트할 엔티티입니다. */
	std::list<IEntity*> updateEntites_;

	/** 렌더링할 엔티티입니다. */
	std::list<IEntity2D*> renderEntities_;
};