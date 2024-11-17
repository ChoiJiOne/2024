#pragma once

#include "Entity/Camera2D.h"

/** ȭ���� UI ó���� ���� ī�޶��Դϴ�. */
class UICamera : public Camera2D
{
public:
	UICamera();
	virtual ~UICamera();

	DISALLOW_COPY_AND_ASSIGN(UICamera);

	virtual void Tick(float deltaSeconds) override;
	virtual void Release() override;
};