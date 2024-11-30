#pragma once

#include "Scene/IGameScene.h"
#include "GL/RenderManager2D.h"

/** 클래스 전방 선언입니다. */
class FrameBuffer;
class GamePlayScene;
class PostProcessor;
class UICamera;

/** 게임 중지 씬입니다. */
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
	/** 게임 중지 씬을 초기화합니다. */
	void Initailize();

	/** 게임 중지 씬의 초기화를 해제합니다. */
	void UnInitailize();

private:
	/** 프레임 버퍼에 후처리를 수행하는 오브젝트입니다. */
	PostProcessor* postProcessor_ = nullptr;

	/** 렌더링을 수행할 프레임 버퍼입니다. */
	FrameBuffer* frameBuffer_ = nullptr;

	/** 프레임 버퍼에 렌더링할 때 설정할 렌더링 옵션입니다. */
	RenderTargetOption renderTargetOption_;

	/** 게임을 중지시킨 플레이 씬입니다. */
	GamePlayScene* gamePlayScene_ = nullptr;
};