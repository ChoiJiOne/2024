#pragma once

#include "Entity/Camera2D.h"

/** 화면의 UI 처리를 위한 카메라입니다. */
class UICamera : public Camera2D
{
public:
	UICamera();
	virtual ~UICamera();

	DISALLOW_COPY_AND_ASSIGN(UICamera);

	virtual void Tick(float deltaSeconds) override;
	virtual void Release() override;
};