#pragma once

#include "Entity/Camera2D.h"

/** �÷��̾ ����ٴϴ� ī�޶��Դϴ�. */
class PlayerFollowCamera : public Camera2D
{
public:
	PlayerFollowCamera();
	virtual ~PlayerFollowCamera();

	DISALLOW_COPY_AND_ASSIGN(PlayerFollowCamera);

	virtual void Tick(float deltaSeconds) override;
	virtual void Release() override;

private:
	class Player* player_ = nullptr;
};