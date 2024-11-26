#pragma once

#include "Scene/IGameScene.h"
#include "GL/RenderManager2D.h"

/** Ŭ���� ���� �����Դϴ�. */
class Camera2D;
class FadeEffector;
class UICamera;
class Player;
class PostProcessor;
class FrameBuffer;


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

	/** UI ��ƼƼ�� �߰��մϴ�. */
	void AddUpdateUIEntity(IEntity* entity);

	/** UI ��ƼƼ�� �����մϴ�. */
	void RemoveUpdateUIEntity(IEntity* entity);

	/** �������� UI ��ƼƼ�� �߰��մϴ�.  */
	void AddRenderUIEntity(IEntity2D* entity);

	/** �������� UI ��ƼƼ�� �����մϴ�. */
	void RemoveRenderUIEntity(IEntity2D* entity);

private:
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

	void PreTick(float deltaSeconds);

private:
	/** ���� �÷��� ���� ���� ī�޶��Դϴ�. */
	Camera2D* mainCamera_ = nullptr;

	/** ���� �÷��� ���� ��ũ�� ī�޶��Դϴ�. */
	UICamera* uiCamera_ = nullptr;

	/** ������ �÷����� �÷��̾��Դϴ�. */
	Player* player_ = nullptr;

	/** ������Ʈ�� ��ƼƼ�Դϴ�. */
	std::list<IEntity*> updateEntites_;

	/** ������Ʈ�� ��ƼƼ�� �����ؾ� ���� Ȯ���մϴ�. */
	bool bNeedSortUpdateEntites_ = false;

	/** �������� ��ƼƼ�Դϴ�. */
	std::list<IEntity2D*> renderEntities_;

	/** �������� ��ƼƼ�� �����ؾ� ���� Ȯ���մϴ�. */
	bool bNeedSortRenderEntites_ = false;

	/** ������Ʈ�� UI ��ƼƼ�Դϴ�. */
	std::list<IEntity*> updateUiEntities_;

	/** ������Ʈ�� UI ��ƼƼ�� �����ؾ� ���� Ȯ���մϴ�. */
	bool bNeedSortUpdateUiEntites_ = false;

	/** �������� UI ��ƼƼ�Դϴ�. */
	std::list<IEntity2D*> renderUiEntities_;

	/** �������� UI ��ƼƼ�� �����ؾ� ���� Ȯ���մϴ�. */
	bool bNeedSortRenderUiEntites_ = false;

	/** ���̵� ȿ���� ������ ��ƼƼ�Դϴ�. */
	FadeEffector* fadeEffector_ = nullptr;

	/** ���̵� �� �ð��Դϴ�. */
	float fadeInTime_ = 1.0f;

	/** ���̵� �ƿ� �ð��Դϴ�. */
	float fadeOutTime_ = 3.0f;

	/** ������ ���ۿ� ��ó���� �����ϴ� ������Ʈ�Դϴ�. */
	PostProcessor* postProcessor_ = nullptr;

	/** �������� ������ ������ �����Դϴ�. */
	FrameBuffer* frameBuffer_ = nullptr;

	/** ������ ���ۿ� �������� �� ������ ������ �ɼ��Դϴ�. */
	RenderTargetOption renderTargetOption_;
};