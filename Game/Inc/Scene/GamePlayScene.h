#pragma once

#include "Scene/IGameScene.h"

/** 게임 플레이 씬입니다. */
class GamePlayScene : public IGameScene
{
public:
	GamePlayScene();
	virtual ~GamePlayScene();

	DISALLOW_COPY_AND_ASSIGN(GamePlayScene);

	virtual void Tick(float deltaSeconds) override;
	virtual void Render() override;
	virtual void Enter() override;
	virtual void Exit() override;

	/** 업데이트할 엔티티를 추가합니다. */
	void AddUpdateEntity(IEntity* entity);

	/** 업데이트할 엔티티를 삭제합니다. */
	void RemoveUpdateEntity(IEntity* entity);

	/** 렌더링할 엔티티를 추가합니다.  */
	void AddRenderEntity(IEntity2D* entity);

	/** 렌더링할 엔티티를 삭제합니다. */
	void RemoveRenderEntity(IEntity2D* entity);

private:
	/** UI 엔티티를 추가합니다. */
	void AddUIEntity(IEntity2D* entity);

	/** UI 엔티티를 삭제합니다. */
	void RemoveUIEntity(IEntity2D* entity);
	
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

private:
	/** 게임 플레이 씬에서 사용할 매니저들의 포인터입니다. */
	class EntityManager* entityManager_ = nullptr;
	class GLManager* glManager_ = nullptr;
	class RenderManager2D* renderManager_ = nullptr;
	class SceneManager* sceneManager_ = nullptr;
	
	/** 게임 플레이 씬의 메인 카메라입니다. */
	class Camera2D* mainCamera_ = nullptr;

	/** 게임 플레이 씬의 스크린 카메라입니다. */
	class UICamera* uiCamera_ = nullptr;

	/** 업데이트할 엔티티입니다. */
	std::list<IEntity*> updateEntites_;

	/** 렌더링할 엔티티입니다. */
	std::list<IEntity2D*> renderEntities_;

	/** UI 엔티티입니다. */
	std::list<IEntity2D*> uiEntities_;

	// 테스트용.
	class UIBar* hpBar_ = nullptr;
};