#pragma once

#include "IGameScene2D.h"

class GamePlayScene2D : public IGameScene2D
{
public:
	GamePlayScene2D();
	virtual ~GamePlayScene2D();

	DISALLOW_COPY_AND_ASSIGN(GamePlayScene2D);

	virtual void Tick(float deltaSeconds) override;
	virtual void Render() override;
	virtual void Enter() override;
	virtual void Exit() override;

	virtual bool IsSceneSwitched() override;
	virtual IGameScene* GetSwitchScene() override;
};