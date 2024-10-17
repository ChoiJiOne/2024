#pragma once

#include "IGameScene2D.h"

class GameTitleScene2D : public IGameScene2D
{
public:
	GameTitleScene2D();
	virtual ~GameTitleScene2D();

	DISALLOW_COPY_AND_ASSIGN(GameTitleScene2D);

	virtual void Tick(float deltaSeconds) override;
	virtual void Render() override;
	virtual void Enter() override;
	virtual void Exit() override;
};