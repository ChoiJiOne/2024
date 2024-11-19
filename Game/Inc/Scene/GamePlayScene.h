#pragma once

#include "Scene/IGameScene.h"

/** ���� �÷��� ���Դϴ�. */
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

	/** ������Ʈ�� ��ƼƼ�� �߰��մϴ�. */
	void AddUpdateEntity(IEntity* entity);

	/** ������Ʈ�� ��ƼƼ�� �����մϴ�. */
	void RemoveUpdateEntity(IEntity* entity);

	/** �������� ��ƼƼ�� �߰��մϴ�.  */
	void AddRenderEntity(IEntity2D* entity);

	/** �������� ��ƼƼ�� �����մϴ�. */
	void RemoveRenderEntity(IEntity2D* entity);

private:
	/** UI ��ƼƼ�� �߰��մϴ�. */
	void AddUIEntity(IEntity2D* entity);

	/** UI ��ƼƼ�� �����մϴ�. */
	void RemoveUIEntity(IEntity2D* entity);
	
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

private:
	/** ���� �÷��� ������ ����� �Ŵ������� �������Դϴ�. */
	class EntityManager* entityManager_ = nullptr;
	class GLManager* glManager_ = nullptr;
	class RenderManager2D* renderManager_ = nullptr;
	class SceneManager* sceneManager_ = nullptr;
	
	/** ���� �÷��� ���� ���� ī�޶��Դϴ�. */
	class Camera2D* mainCamera_ = nullptr;

	/** ���� �÷��� ���� ��ũ�� ī�޶��Դϴ�. */
	class UICamera* uiCamera_ = nullptr;

	/** ������Ʈ�� ��ƼƼ�Դϴ�. */
	std::list<IEntity*> updateEntites_;

	/** �������� ��ƼƼ�Դϴ�. */
	std::list<IEntity2D*> renderEntities_;

	/** UI ��ƼƼ�Դϴ�. */
	std::list<IEntity2D*> uiEntities_;

	// �׽�Ʈ��.
	class UIBar* hpBar_ = nullptr;
};