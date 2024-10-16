#pragma once

#include "Macro.h"

/** ���� ���� �� �������̽��Դϴ�. */
class IGameScene
{
public:
	IGameScene() = default;
	virtual ~IGameScene() {}

	DISALLOW_COPY_AND_ASSIGN(IGameScene);

	virtual void Tick(float deltaSeconds) = 0;
	virtual void Render() = 0;
	
	virtual bool IsSceneSwitched() = 0;
	virtual IGameScene* GetSwitchScene() = 0;
};