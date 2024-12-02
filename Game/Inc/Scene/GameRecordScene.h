#pragma once

#include <list>

#include "Scene/IGameScene.h"
#include "GL/RenderManager2D.h"

/** 클래스 전방 선언입니다. */
class ResultViewer;
class UICamera;

/** 게임 기록을 보여주는 씬입니다. */
class GameRecordScene : public IGameScene
{
public:
	GameRecordScene();
	virtual ~GameRecordScene();

	DISALLOW_COPY_AND_ASSIGN(GameRecordScene);

	virtual void Tick(float deltaSeconds) override;
	virtual void Render() override;
	virtual void Enter() override;
	virtual void Exit() override;

private:
	/** 게임 기록 씬을 초기화합니다. */
	void Initailize();

	/** 게임 기록 씬의 초기화를 해제합니다. */
	void UnInitailize();

private:	
	/** 게임 기록 씬의 스크린 카메라입니다. */
	UICamera* uiCamera_ = nullptr;

	/** 업데이트할 UI 엔티티입니다. */
	std::list<IEntity*> updateUiEntities_;

	/** 렌더링할 UI 엔티티입니다. */
	std::list<IEntity2D*> renderUiEntities_;

	/** 게임 플레이 기록을 보여주는 엔티티입니다. */
	ResultViewer* playTimeResultViewer_ = nullptr;
	ResultViewer* getCoinResultViewer_ = nullptr;
	ResultViewer* useSkillResultViewer_ = nullptr;
	ResultViewer* totalHealHpResultViewer_ = nullptr;
	ResultViewer* totalLostHpResultViewer_ = nullptr;
	ResultViewer* totalHealMpResultViewer_ = nullptr;
	ResultViewer* totalLostMpResultViewer_ = nullptr;

	/** 게임 플레이 기록을 표시할 시간입니다. */
	float playRecordViewTime_ = 0.0f;
};