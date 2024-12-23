#pragma once

#include "Entity/Camera2D.h"

/** Ŭ������ ���� �����Դϴ�. */
class Player;

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
	Player* player_ = nullptr;
};