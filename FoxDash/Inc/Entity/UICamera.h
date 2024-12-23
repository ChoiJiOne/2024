#pragma once

#include "Entity/Camera2D.h"
#include "Physic/Circle2D.h"

/** 화면의 UI 처리를 위한 카메라입니다. */
class UICamera : public Camera2D
{
public:
	UICamera();
	virtual ~UICamera();

	DISALLOW_COPY_AND_ASSIGN(UICamera);

	virtual void Tick(float deltaSeconds) override;
	virtual void Release() override;

	/** 마우스 포인터의 경계 영역을 얻습니다. */
	const Circle2D* GetMousePointer() const { return &mousePointer_; }

private:
	/** 마우스 포인터의 경계 영역입니다. */
	Circle2D mousePointer_;
};