#pragma once

#include <string>
#include <map>

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

	virtual void Tick(float deltaSeconds) = 0;
	virtual void Render() = 0;
	virtual void Enter() = 0;
	virtual void Exit() = 0;

	/** ���� ���� �����ߴ��� Ȯ���մϴ�. */
	bool IsEnter() { return bIsEnter_; }

	/** �� ��ȯ�� �����Ǿ����� Ȯ���մϴ�. */
	bool IsSceneSwitched() { return bIsSwitched_; }

	/** ��ȯ�� ���� ������ ���� ����ϴ�. */
	IGameScene* GetSwitchScene() { return switchScene_; }

	/** ������Ʈ�� ��ƼƼ�� �߰��մϴ�. �̶�, �̸��� �����ؾ� �մϴ�. */
	void AddUpdateEntity(const std::string& name, IEntity* updateEntity);

	/** ������Ʈ�� ��ƼƼ�� ����ϴ�. */
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

	/** ������Ʈ�� ��ƼƼ�� �����մϴ�. */
	void RemoveUpdateEntity(const std::string& name);

	/** �������� ��ƼƼ�� �߰��մϴ�. �̶�, �̸��� �����ؾ� �մϴ�. */
	void AddRenderEntity(const std::string& name, IEntity2D* renderEntity);

	/** �������� ��ƼƼ�� ����ϴ�. */
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

	/** �������� ��ƼƼ�� �����մϴ�. */
	void RemoveRenderEntity(const std::string& name);
	
protected:
	/** ������Ʈ�� ��ƼƼ�� �켱���� ������ ���� ����ü�Դϴ�. */
	struct UpdateEntityOrder 
	{
		bool operator()(const IEntity*& lhs, const IEntity*& rhs) const
		{
			return lhs->GetTickOrder() < rhs->GetTickOrder();
		}
	};

	/** �������� ��ƼƼ�� �켱���� ������ ���� ����ü�Դϴ�. */
	struct RenderEntityOrder
	{
		bool operator()(const IEntity2D*& lhs, const IEntity2D*& rhs) const
		{
			return lhs->GetRenderOrder() < rhs->GetRenderOrder();
		}
	};

protected:
	/** ���� ���� �����ߴ��� Ȯ���մϴ�. */
	bool bIsEnter_ = false;

	/** �� ��ȯ�� �����Ǿ����� Ȯ���մϴ�. */
	bool bIsSwitched_ = false;

	/** ��ȯ�� ���� �������Դϴ�. */
	IGameScene* switchScene_ = nullptr;

	/** ������Ʈ�� ��ƼƼ�Դϴ�. */
	std::map<std::string, IEntity*, UpdateEntityOrder> updateEntites_;

	/** �������� ��ƼƼ�Դϴ�. */
	std::map<std::string, IEntity2D*, RenderEntityOrder> renderEntities_;
};