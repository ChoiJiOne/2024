#pragma once

#include "IGameScene.h"

class GameScene : public IGameScene
{
public:
	GameScene();
	virtual ~GameScene();

	DISALLOW_COPY_AND_ASSIGN(GameScene);

	virtual void Tick(float deltaSeconds) override;
	virtual void Render() override;
	virtual void Enter() override;
	virtual void Exit() override;
};