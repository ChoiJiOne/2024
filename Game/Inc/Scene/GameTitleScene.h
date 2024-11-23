#pragma once

#include "Scene/IGameScene.h"

/** 게임 타이틀 씬입니다. */
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
	/** 게임 타이틀 씬을 초기화합니다. */
	void Initailize();

	/** 게임 타이틀 씬의 초기화를 해제합니다. */
	void UnInitailize();

private:
	/** 게임 타이틀 씬의 스크린 카메라입니다. */
	class UICamera* uiCamera_ = nullptr;
	
	/** 업데이트할 UI 엔티티입니다. */
	std::map<std::string, IEntity*> updateUiEntities_;

	/** 렌더링할 UI 엔티티입니다. */
	std::map<std::string, IEntity2D*> renderUiEntities_;
};