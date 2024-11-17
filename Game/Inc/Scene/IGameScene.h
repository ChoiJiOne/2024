#pragma once

#include <string>
#include <list>

#include "Entity/IEntity.h"
#include "Entity/IEntity2D.h"
#include "Utils/Macro.h"

/** 게임 씬 인터페이스입니다. */
class IGameScene
{
public:
	IGameScene() {}
	virtual ~IGameScene() {}

	DISALLOW_COPY_AND_ASSIGN(IGameScene);

	virtual void Tick(float deltaSeconds);
	virtual void Render() = 0;
	virtual void Enter() = 0;
	virtual void Exit() = 0;

	/** 현재 씬에 진입했는지 확인합니다. */
	bool IsEnter() { return bIsEnter_; }

	/** 씬 전환이 감지되었는지 확인합니다. */
	bool IsSceneSwitched() { return bIsSwitched_; }

	/** 전환할 씬의 포인터 값을 얻습니다. */
	IGameScene* GetSwitchScene() { return switchScene_; }
	
protected:
	/** 현재 씬에 진입했는지 확인합니다. */
	bool bIsEnter_ = false;

	/** 씬 전환이 감지되었는지 확인합니다. */
	bool bIsSwitched_ = false;

	/** 전환할 씬의 포인터입니다. */
	IGameScene* switchScene_ = nullptr;
};