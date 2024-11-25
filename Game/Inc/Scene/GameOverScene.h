#pragma once

#include "Scene/IGameScene.h"
#include "GL/RenderManager2D.h"

/** Ŭ���� ���� �����Դϴ�. */
class FadeEffector;
class UICamera;
class PostProcessor;
class FrameBuffer;

/** ���� ���� ���Դϴ�. */
class GameOverScene : public IGameScene
{
public:
	GameOverScene();
	virtual ~GameOverScene();

	DISALLOW_COPY_AND_ASSIGN(GameOverScene);

	virtual void Tick(float deltaSeconds) override;
	virtual void Render() override;
	virtual void Enter() override;
	virtual void Exit() override;

private:
	/** ���� ���� ���� �ʱ�ȭ�մϴ�. */
	void Initailize();

	/** ���� ���� ���� �ʱ�ȭ�� �����մϴ�. */
	void UnInitailize();

private:
	/** ���� ���� ���� ��ũ�� ī�޶��Դϴ�. */
	UICamera* uiCamera_ = nullptr;

	/** ���̵� ȿ���� ������ ��ƼƼ�Դϴ�. */
	FadeEffector* fadeEffector_ = nullptr;

	/** ���̵� �� �ð��Դϴ�. */
	float fadeInTime_ = 1.0f;

	/** ������ ���ۿ� ��ó���� �����ϴ� ������Ʈ�Դϴ�. */
	PostProcessor* postProcessor_ = nullptr;

	/** �������� ������ ������ �����Դϴ�. */
	FrameBuffer* frameBuffer_ = nullptr;

	/** ������ ���ۿ� �������� �� ������ ������ �ɼ��Դϴ�. */
	RenderTargetOption renderTargetOption_;

	/** ������Ʈ�� UI ��ƼƼ�Դϴ�. */
	std::map<std::string, IEntity*> updateUiEntities_;

	/** �������� UI ��ƼƼ�Դϴ�. */
	std::map<std::string, IEntity2D*> renderUiEntities_;
};