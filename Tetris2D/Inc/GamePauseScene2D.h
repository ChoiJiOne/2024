#pragma once

#include "IGameScene2D.h"

class GamePauseScene2D : public IGameScene2D
{
public:
	GamePauseScene2D();
	virtual ~GamePauseScene2D();

	DISALLOW_COPY_AND_ASSIGN(GamePauseScene2D);

	virtual void Tick(float deltaSeconds) override;
	virtual void Render() override;
	virtual void Enter() override;
	virtual void Exit() override;
};