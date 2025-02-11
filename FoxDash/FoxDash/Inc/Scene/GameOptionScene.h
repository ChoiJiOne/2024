#pragma once

#include <list>

#include "Scene/IGameScene.h"
#include "GL/RenderManager2D.h"

/** 클래스 전방 선언입니다. */
class GameManager;
class UICamera;

/** 게임 옵션을 설정하는 씬입니다. */
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

	/** 뒤로 갈 때 돌아갈 씬을 설정합니다. */
	void SetBackwardsScene(IGameScene* backScene) { backScene_ = backScene; }

private:
	/** 게임 옵션 설정 씬을 초기화합니다. */
	void Initailize();

	/** 게임 옵션 설정 씬의 초기화를 해제합니다. */
	void UnInitailize();

private:
	/** 게임 옵션 설정 씬의 스크린 카메라입니다. */
	UICamera* uiCamera_ = nullptr;

	/** 뒤로 갈 때 돌아갈 씬입니다. */
	IGameScene* backScene_ = nullptr;

	/** 업데이트할 UI 엔티티입니다. */
	std::list<IEntity*> updateUiEntities_;

	/** 렌더링할 UI 엔티티입니다. */
	std::list<IEntity2D*> renderUiEntities_;

	/** 게임 매니저 포인터입니다. */
	GameManager* gameManager_ = nullptr;
};