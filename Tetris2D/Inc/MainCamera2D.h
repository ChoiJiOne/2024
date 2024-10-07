#pragma once

#include "Camera2D.h"

class MainCamera2D : public Camera2D
{
public:
	MainCamera2D();
	virtual ~MainCamera2D();

	DISALLOW_COPY_AND_ASSIGN(MainCamera2D);

	virtual void Tick(float deltaSeconds) override;
	virtual void Release() override;

private:

};