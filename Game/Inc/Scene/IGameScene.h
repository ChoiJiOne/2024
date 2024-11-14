#pragma once

#include <string>
#include <list>

#include "Entity/IEntity.h"
#include "Entity/IEntity2D.h"
#include "Utils/Macro.h"

/** ���� �� �������̽��Դϴ�. */
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

	/** ���� ���� �����ߴ��� Ȯ���մϴ�. */
	bool IsEnter() { return bIsEnter_; }

	/** �� ��ȯ�� �����Ǿ����� Ȯ���մϴ�. */
	bool IsSceneSwitched() { return bIsSwitched_; }

	/** ��ȯ�� ���� ������ ���� ����ϴ�. */
	IGameScene* GetSwitchScene() { return switchScene_; }

	/** ������Ʈ�� ��ƼƼ�� �߰��մϴ�. */
	void AddUpdateEntity(IEntity* entity);
	
	/** ������Ʈ�� ��ƼƼ�� �����մϴ�. */
	void RemoveUpdateEntity(IEntity* entity);

	/** �������� ��ƼƼ�� �߰��մϴ�.  */
	void AddRenderEntity(IEntity2D* entity);

	/** �������� ��ƼƼ�� �����մϴ�. */
	void RemoveRenderEntity(IEntity2D* entity);

protected:
	/** ������Ʈ�� ��ƼƼ�� �켱 ������ ���մϴ�. */
	static bool CompareUpdateOrder(IEntity* lhs, IEntity* rhs)
	{
		return lhs->GetTickOrder() < rhs->GetTickOrder();
	}

	/** �������� ��ƼƼ�� �켱 ������ ���մϴ�. */
	static bool CompareRenderOrder(IEntity2D* lhs, IEntity2D* rhs)
	{
		return lhs->GetRenderOrder() < rhs->GetRenderOrder();
	}
	
protected:
	/** ���� ���� �����ߴ��� Ȯ���մϴ�. */
	bool bIsEnter_ = false;

	/** �� ��ȯ�� �����Ǿ����� Ȯ���մϴ�. */
	bool bIsSwitched_ = false;

	/** ��ȯ�� ���� �������Դϴ�. */
	IGameScene* switchScene_ = nullptr;

	/** ������Ʈ�� ��ƼƼ�Դϴ�. */
	std::list<IEntity*> updateEntites_;

	/** �������� ��ƼƼ�Դϴ�. */
	std::list<IEntity2D*> renderEntities_;
};