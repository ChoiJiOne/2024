#pragma once

#include "Scene/IGameScene.h"

#include "GL/RenderManager2D.h"

/** 게임 개발을 위한 씬입니다. */
class GameDevScene : public IGameScene
{
public:
	GameDevScene();
	virtual ~GameDevScene();

	DISALLOW_COPY_AND_ASSIGN(GameDevScene);

	virtual void Tick(float deltaSeconds) override;
	virtual void Render() override;
	virtual void Enter() override;
	virtual void Exit() override;

private:
	class Camera2D* mainCamera_ = nullptr;

	class TTFont* alagard_ = nullptr;
	class TTFont* lower_ = nullptr;
	class TTFont* namsan_ = nullptr;
};