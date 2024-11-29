#pragma once

#include <list>

#include "Scene/IGameScene.h"
#include "GL/RenderManager2D.h"

/** Ŭ���� ���� �����Դϴ�. */
class UICamera;

/** ���� �ɼ��� �����ϴ� ���Դϴ�. */
class GameOptionScene : public IGameScene
{
public:
	GameOptionScene();
	virtual ~GameOptionScene();

	DISALLOW_COPY_AND_ASSIGN(GameOptionScene);

	virtual void Tick(float deltaSeconds) override;
	virtual void Render() override;
	virtual void Enter() override;
	virtual void Exit() override;

private:
	/** ���� �ɼ� ���� ���� �ʱ�ȭ�մϴ�. */
	void Initailize();

	/** ���� �ɼ� ���� ���� �ʱ�ȭ�� �����մϴ�. */
	void UnInitailize();

private:
	/** ���� �ɼ� ���� ���� ��ũ�� ī�޶��Դϴ�. */
	UICamera* uiCamera_ = nullptr;

	/** ������Ʈ�� UI ��ƼƼ�Դϴ�. */
	std::list<IEntity*> updateUiEntities_;

	/** �������� UI ��ƼƼ�Դϴ�. */
	std::list<IEntity2D*> renderUiEntities_;
};