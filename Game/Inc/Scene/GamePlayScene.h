#pragma once

#include <map>

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

	/** 
	 * ��ƼƼ�� �߰��մϴ�. 
	 * - �߰��ϴ� ��ƼƼ�� ���������� �ʽ��ϴ�. 
	 * - ���� �������� �켱���� ���� �����ϴ�. 
	 */
	void AddEntity(IEntity* entity, int32_t updateOrder);

	/** 
	 * ��ƼƼ�� �߰��մϴ�. 
	 * - �߰��ϴ� ��ƼƼ�� �������� �����մϴ�. 
	 * - ���� �������� �켱���� ���� �����ϴ�. 
	 */
	void AddEntity(IEntity2D* entity, int32_t updateOrder, int32_t renderOrder);

	/** ��ƼƼ�� �����մϴ�. */
	void RemoveEntity(IEntity* entity);

private:
	/** Tick�� �����ϱ� ���� ȣ���մϴ�. */
	void PreTick(float deltaSeconds);

private:
	/** ������Ʈ�� ��ƼƼ�Դϴ�. */
	std::multimap<int32_t, IEntity*> updateEntites_;

	/** �������� ��ƼƼ�Դϴ�. */
	std::multimap<int32_t, IEntity2D*> renderEntities_;

	/** ���� �÷��� ���� ���� ī�޶��Դϴ�. */
	Camera2D* mainCamera_ = nullptr;

	/** ���� �÷��� ���� ��ũ�� ī�޶��Դϴ�. */
	UICamera* uiCamera_ = nullptr;

	/** ������ �÷����� �÷��̾��Դϴ�. */
	Player* player_ = nullptr;
	
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