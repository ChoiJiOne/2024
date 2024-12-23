#pragma once

#include "Entity/Camera2D.h"

/** 클래스의 전방 선언입니다. */
class Player;

/** 플레이어를 따라다니는 카메라입니다. */
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