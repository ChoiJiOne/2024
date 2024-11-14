#pragma once

#include "Scene/IGameScene.h"

/** ���� �÷��� ���Դϴ�. */
class GamePlayScene : public IGameScene
{
public:
	GamePlayScene();
	virtual ~GamePlayScene();

	DISALLOW_COPY_AND_ASSIGN(GamePlayScene);

	virtual void Tick(float deltaSeconds) override;
	virtual void Render() override;
	virtual void Enter() override;
	virtual void Exit() override;

private:
	class EntityManager* entityManager_ = nullptr;
	class GLManager* glManager_ = nullptr;
	class RenderManager2D* renderManager_ = nullptr;

	class Camera2D* mainCamera_ = nullptr;
	class Background* background_ = nullptr;
	class Player* player_ = nullptr;
	class Coin* coin_ = nullptr;
};