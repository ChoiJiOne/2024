#pragma once

#include "Scene/IGameScene.h"
#include "GL/RenderManager2D.h"

/** 클래스 전방 선언입니다. */
class FadeEffector;
class UICamera;
class PostProcessor;
class FrameBuffer;

/** 게임 오버 씬입니다. */
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
	/** 게임 오버 씬을 초기화합니다. */
	void Initailize();

	/** 게임 오버 씬의 초기화를 해제합니다. */
	void UnInitailize();

private:
	/** 게임 오버 씬의 스크린 카메라입니다. */
	UICamera* uiCamera_ = nullptr;

	/** 페이드 효과를 제어할 엔티티입니다. */
	FadeEffector* fadeEffector_ = nullptr;

	/** 페이드 인 시간입니다. */
	float fadeInTime_ = 1.0f;

	/** 프레임 버퍼에 후처리를 수행하는 오브젝트입니다. */
	PostProcessor* postProcessor_ = nullptr;

	/** 렌더링을 수행할 프레임 버퍼입니다. */
	FrameBuffer* frameBuffer_ = nullptr;

	/** 프레임 버퍼에 렌더링할 때 설정할 렌더링 옵션입니다. */
	RenderTargetOption renderTargetOption_;

	/** 업데이트할 UI 엔티티입니다. */
	std::map<std::string, IEntity*> updateUiEntities_;

	/** 렌더링할 UI 엔티티입니다. */
	std::map<std::string, IEntity2D*> renderUiEntities_;
};