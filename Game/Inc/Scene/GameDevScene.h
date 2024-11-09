#pragma once

#include "Scene/IGameScene.h"

#include "GL/RenderManager2D.h"
#include "Physic/Circle2D.h"
#include "Physic/Line2D.h"
#include "Physic/OrientedRect2D.h"
#include "Physic/Rect2D.h"

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

	class TTFont* alagard_ = nullptr;
	class TTFont* lower_ = nullptr;
	class TTFont* namsan_ = nullptr;

	class TextureAtlas2D* atlas_ = nullptr;
	class SpriteAnimator2D* animator_ = nullptr;

	glm::vec2 mousePos_ = glm::vec2();

	TextureDrawOption option_;
	glm::vec3 outline_ = glm::vec3(0.0f, 0.0f, 0.0f);
};