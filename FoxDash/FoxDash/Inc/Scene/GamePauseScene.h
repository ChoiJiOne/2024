#pragma once

#include <list>

#include "Scene/IGameScene.h"
#include "GL/RenderManager2D.h"

/** Ŭ���� ���� �����Դϴ�. */
class FrameBuffer;
class GamePlayScene;
class PostProcessor;
class UICamera;

/** ���� ���� ���Դϴ�. */
class GamePauseScene : public IGameScene
{
public:
	GamePauseScene();
	virtual ~GamePauseScene();

	DISALLOW_COPY_AND_ASSIGN(GamePauseScene);

	virtual void Tick(float deltaSeconds) override;
	virtual void Render() override;
	virtual void Enter() override;
	virtual void Exit() override;

private:
	/** ���� ���� ���� �ʱ�ȭ�մϴ�. */
	void Initailize();

	/** ���� ���� ���� �ʱ�ȭ�� �����մϴ�. */
	void UnInitailize();

	/** ���� �÷��� ���� �������մϴ�. */
	void RenderGamePlayScene();

private:
	/** ������ ������Ų �÷��� ���Դϴ�. */
	GamePlayScene* gamePlayScene_ = nullptr;

	/** ���� ��� ���� ��ũ�� ī�޶��Դϴ�. */
	UICamera* uiCamera_ = nullptr;

	/** ������Ʈ�� UI ��ƼƼ�Դϴ�. */
	std::list<IEntity*> updateUiEntities_;

	/** �������� UI ��ƼƼ�Դϴ�. */
	std::list<IEntity2D*> renderUiEntities_;
};