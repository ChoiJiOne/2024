#pragma once

#include "Scene/IGameScene.h"

/** ���� ������ ���� ���Դϴ�. */
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

	class FrameBuffer* frameBuffer_ = nullptr;
	class PostProcessor* postProcessor_ = nullptr;

	class TextureAtlas2D* atlas_ = nullptr;
	class SpriteAnimator2D* animator_ = nullptr;
};