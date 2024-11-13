#pragma once

#include <glm/glm.hpp>

#include "Scene/IGameScene.h"

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
	class FrameBuffer* frameBuffer_ = nullptr;
	class PostProcessor* postProcessor_ = nullptr;
	class TextureAtlas2D* atlas_ = nullptr;
	class SpriteAnimator2D* animator_ = nullptr;

	int32_t type = 0;
	glm::vec3 color = glm::vec3(0.0f, 0.0f, 0.0f);
	float factor = 0.0f;
};