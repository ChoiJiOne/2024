#pragma once

#include "Scene/IGameScene.h"
#include "GL/RenderManager2D.h"

/** Ŭ���� ���� �����Դϴ�. */
class FadeEffector;
class UICamera;
class PostProcessor;
class FrameBuffer;

/** ���� Ÿ��Ʋ ���Դϴ�. */
class GameTitleScene : public IGameScene
{
public:
	GameTitleScene();
	virtual ~GameTitleScene();

	DISALLOW_COPY_AND_ASSIGN(GameTitleScene);

	virtual void Tick(float deltaSeconds) override;
	virtual void Render() override;
	virtual void Enter() override;
	virtual void Exit() override;

private:
	/** ���� Ÿ��Ʋ ���� �ʱ�ȭ�մϴ�. */
	void Initailize();

	/** ���� Ÿ��Ʋ ���� �ʱ�ȭ�� �����մϴ�. */
	void UnInitailize();

private:
	/** ���� Ÿ��Ʋ ���� ��ũ�� ī�޶��Դϴ�. */
	UICamera* uiCamera_ = nullptr;

	/** ���̵� ȿ���� ������ ��ƼƼ�Դϴ�. */
	FadeEffector* fadeEffector_ = nullptr;

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