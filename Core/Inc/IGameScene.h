#pragma once

#include "Macro.h"

/** 게임 내의 씬 인터페이스입니다. */
class IGameScene
{
public:
	IGameScene() {}
	virtual ~IGameScene() {}

	DISALLOW_COPY_AND_ASSIGN(IGameScene);

	virtual void Tick(float deltaSeconds) = 0;
	virtual void Render() = 0;
	virtual void Enter() = 0;
	virtual void Exit() = 0;
	
	bool IsEnter() { return bIsEnter_; }
	bool IsSceneSwitched() { return bIsSwitched_; }
	IGameScene* GetSwitchScene() { return switchScene_; }

protected:
	bool bIsEnter_ = false;
	bool bIsSwitched_ = false;
	IGameScene* switchScene_ = nullptr;
};