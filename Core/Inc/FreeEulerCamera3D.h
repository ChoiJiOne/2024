#pragma once

#include "Camera3D.h"

namespace GameMaker
{
/** ���콺�� �����̴� ���� ������ 3D ���Ϸ� ī�޶� */
class FreeEulerCamera3D : public Camera3D
{
public:
	enum class EMovement
	{
		FORWARD  = 0x00,
		BACKWARD = 0x01,
		LEFT     = 0x02,
		RIGHT    = 0x03,
	};

public:
	/** ��� ������ ���� ���� �����Դϴ�. */
	FreeEulerCamera3D(const Vec3f& position, float yaw, float pitch, float fov, float nearZ, float farZ);
	FreeEulerCamera3D(const Vec3f& position, float yaw, float pitch, float aspectRatio, float fov, float nearZ, float farZ);
	virtual ~FreeEulerCamera3D();

	DISALLOW_COPY_AND_ASSIGN(FreeEulerCamera3D);

	virtual void Tick(float deltaSeconds) override;
	virtual void Release() override;

private:
	void UpdateDirectionState();

private:
	float speed_ = 2.5f;
	float yaw_ = 0.0f; /** y�� ���Ϸ� ȸ�� ���� */
	float pitch_ = 0.0f; /** x�� ���Ϸ� ȸ�� ���� */
};

}