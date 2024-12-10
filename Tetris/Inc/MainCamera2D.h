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

	void Reset();
	void Shake();

private:
	float shakeTime_ = 0.0f;
	float maxShakeTime_ = 0.0f;
	
	Rect2D originCollision_;
	float shakeMoveLength_ = 0.0f;

	bool bStartShake_ = false;
};