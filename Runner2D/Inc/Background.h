#pragma once

#include "Collision2D.h"

#include "Entity2D.h"

class Texture2D;

class Camera;

class Background : public Entity2D
{
public:
	Background(Camera* camera);
	virtual ~Background();

	DISALLOW_COPY_AND_ASSIGN(Background);

	virtual void Tick(float deltaSeconds) override;
	virtual void Render() override;
	virtual void Release() override;

private:
	Camera* camera_ = nullptr;
	
	Texture2D* texture_ = nullptr;

	Rect2D rect_;
};