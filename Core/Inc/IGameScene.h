#pragma once

#include "Macro.h"

/** ���� ���� �� �������̽��Դϴ�. */
class IGameScene
{
public:
	IGameScene();
	virtual ~IGameScene();

	DISALLOW_COPY_AND_ASSIGN(IGameScene);

	virtual void Tick(float deltaSeconds) = 0;
	virtual void Render() = 0;
	
	virtual bool IsSceneSwitched() = 0;
	virtual IGameScene* GetSwitchScene() = 0;

protected:
	virtual void SetSwitchScene(IGameScene* switchScene) = 0;

protected:
	class IApp* app_ = nullptr;
	IGameScene* switchScene_ = nullptr;
};