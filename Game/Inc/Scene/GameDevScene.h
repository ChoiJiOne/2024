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
	class VertexBuffer* vertexBuffer_ = nullptr;
	uint32_t vao_ = 0;
	class Shader* shader_ = nullptr;
};