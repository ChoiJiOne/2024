#pragma once

#include <list>

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

	/** 게임 플레이 씬을 렌더링합니다. */
	void RenderGamePlayScene();

private:
	/** 게임을 중지시킨 플레이 씬입니다. */
	GamePlayScene* gamePlayScene_ = nullptr;

	/** 게임 기록 씬의 스크린 카메라입니다. */
	UICamera* uiCamera_ = nullptr;

	/** 업데이트할 UI 엔티티입니다. */
	std::list<IEntity*> updateUiEntities_;

	/** 렌더링할 UI 엔티티입니다. */
	std::list<IEntity2D*> renderUiEntities_;
};