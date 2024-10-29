#pragma once

#include "IGameScene2D.h"

class GameScene : public IGameScene2D
{
public:
	GameScene();
	virtual ~GameScene();

	DISALLOW_COPY_AND_ASSIGN(GameScene);
};