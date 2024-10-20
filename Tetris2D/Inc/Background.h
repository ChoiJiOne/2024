#pragma once

#include "Collision2D.h"
#include "IEntity2D.h"
#include "RenderManager2D.h"

class Texture2D;

class Background : public IEntity2D
{
public:
	Background();
	virtual ~Background();

	DISALLOW_COPY_AND_ASSIGN(Background);

	virtual void Tick(float deltaSeconds) override;
	virtual void Render() override;
	virtual void Release() override;

private:
	Rect2D bound_;
	Texture2D* texture_ = nullptr;
	RenderManager2D::SpriteRenderOptions option_;
};