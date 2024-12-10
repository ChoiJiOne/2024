#pragma once

#include "IGameScene2D.h"

class GameOverScene2D : public IGameScene2D
{
public:
	GameOverScene2D();
	virtual ~GameOverScene2D();

	DISALLOW_COPY_AND_ASSIGN(GameOverScene2D);

	virtual void Enter() override;
};