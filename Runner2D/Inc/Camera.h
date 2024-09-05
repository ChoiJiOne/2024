#pragma once

#include "Collision2D.h"

#include "Camera2D.h"

class Camera : public Camera2D
{
public:
	Camera();
	virtual ~Camera();

	DISALLOW_COPY_AND_ASSIGN(Camera);

	virtual void Tick(float deltaSeconds) override;
	virtual void Release() override;

	ICollision2D* GetCollision() { return &rect_; }

private:
	Rect2D rect_;
};