#pragma once

#include "Camera2D.h"

class Camera : public Camera2D
{
public:
	Camera();
	virtual ~Camera();

	DISALLOW_COPY_AND_ASSIGN(Camera);

	virtual void Tick(float deltaSeconds) override;
	virtual void Release() override;
};