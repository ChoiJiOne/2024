#include "MathModule.h"
#include "InputController.h"
#include "RenderModule.h"

#include "Camera.h"

Camera::Camera()
{
	yaw_ = MathModule::ToRadian(-90.0f);
	pitch_ = MathModule::ToRadian(-30.0f);
	eyePosition_ = Vec3f(0.0f, 5.0f, 10.0f);
	UpdateViewState();

	int32_t screenWidth = 0;
	int32_t screenHeight = 0;
	RenderModule::GetScreenSize(screenWidth, screenHeight);
	aspectRatio_ = static_cast<float>(screenWidth) / static_cast<float>(screenHeight);

	fov_ = PiDiv4;
	nearZ_ = 0.01f;
	farZ_ = 100.0f;
	projection_ = Mat4x4::Perspective(fov_, aspectRatio_, nearZ_, farZ_);

	minPitch_ = -PiDiv2 + 0.1f;
	maxPitch_ = +PiDiv2 - 0.1f;
	
	bIsInitialized_ = true;
}

Camera::~Camera()
{
	if (bIsInitialized_)
	{
		Release();
	}
}

void Camera::Tick(float deltaSeconds)
{
	if (!bIsActive_)
	{
		return;
	}

	bool bIsUpdateState = false;

	if (InputController::GetKeyPressState(EKey::KEY_LBUTTON) == EPressState::HELD)
	{
		CursorPos prev = InputController::GetPrevCursorPos();
		CursorPos curr = InputController::GetCurrCursorPos();

		float xoffset = static_cast<float>(curr.x - prev.x);
		float yoffset = static_cast<float>(prev.y - curr.y);

		xoffset *= 0.01f;
		yoffset *= 0.01f;

		yaw_ += xoffset;
		pitch_ += yoffset;

		pitch_ = MathModule::Clamp<float>(pitch_, minPitch_, maxPitch_);
		bIsUpdateState = true;
	}

	if (InputController::GetKeyPressState(EKey::KEY_W) == EPressState::HELD)
	{
		eyePosition_ += eyeDirection_ * deltaSeconds * speed_;
		bIsUpdateState = true;
	}

	if (InputController::GetKeyPressState(EKey::KEY_S) == EPressState::HELD)
	{
		eyePosition_ -= eyeDirection_ * deltaSeconds * speed_;
		bIsUpdateState = true;
	}

	if (InputController::GetKeyPressState(EKey::KEY_A) == EPressState::HELD)
	{
		eyePosition_ -= rightDirection_ * deltaSeconds * speed_;
		bIsUpdateState = true;
	}

	if (InputController::GetKeyPressState(EKey::KEY_D) == EPressState::HELD)
	{
		eyePosition_ += rightDirection_ * deltaSeconds * speed_;
		bIsUpdateState = true;
	}

	if (bIsUpdateState)
	{
		UpdateViewState();
	}


	int32_t width = 0;
	int32_t height = 0;
	RenderModule::GetScreenSize(width, height);

	CursorPos curr = InputController::GetCurrCursorPos();
	Vec2f mousePos = Vec2f(static_cast<float>(curr.x), static_cast<float>(curr.y));
	Vec2f viewportSize = Vec2f(static_cast<float>(width), static_cast<float>(height));

	UpdateMouseRay(mousePos, Vec2f(0.0f, 0.0f), viewportSize, view_, projection_);
}

void Camera::Release()
{
	if (bIsInitialized_)
	{
		bIsInitialized_ = false;
	}
}

void Camera::UpdateViewState()
{
	Vec3f direction;
	direction.x = MathModule::Cos(yaw_) * MathModule::Cos(pitch_);
	direction.y = MathModule::Sin(pitch_);
	direction.z = MathModule::Sin(yaw_) * MathModule::Cos(pitch_);

	eyeDirection_ = Vec3f::Normalize(direction);
	rightDirection_ = Vec3f::Normalize(Vec3f::Cross(eyeDirection_, worldUpDirection_));
	upDirection_ = Vec3f::Normalize(Vec3f::Cross(rightDirection_, eyeDirection_));

	view_ = Mat4x4::LookAt(eyePosition_, eyePosition_ + eyeDirection_, upDirection_);
}

Vec3f Camera::Unproject(const Vec3f& viewportPosition, const Vec2f& viewportOrigin, const Vec2f& viewportSize, const Mat4x4& view, const Mat4x4& projection)
{
	float normalized[4] =
	{
		(viewportPosition.x - viewportOrigin.x) / viewportSize.x,
		(viewportPosition.y - viewportOrigin.y) / viewportSize.y,
		viewportPosition.z,
		1.0f
	};

	float ndcSpace[4] = { normalized[0], normalized[1], normalized[2], normalized[3] };

	ndcSpace[0] = ndcSpace[0] * 2.0f - 1.0f;
	ndcSpace[1] = 1.0f - ndcSpace[1] * 2.0f;
	ndcSpace[2] = MathModule::Clamp<float>(ndcSpace[2], 0.0f, 1.0f);

	Mat4x4 projectInv = Mat4x4::Inverse(projection);
	Vec4f eyeSpace;
	eyeSpace.x = ndcSpace[0] * projectInv.e00 + ndcSpace[1] * projectInv.e10 + ndcSpace[2] * projectInv.e20 + ndcSpace[3] * projectInv.e30;
	eyeSpace.y = ndcSpace[0] * projectInv.e01 + ndcSpace[1] * projectInv.e11 + ndcSpace[2] * projectInv.e21 + ndcSpace[3] * projectInv.e31;
	eyeSpace.z = ndcSpace[0] * projectInv.e02 + ndcSpace[1] * projectInv.e12 + ndcSpace[2] * projectInv.e22 + ndcSpace[3] * projectInv.e32;
	eyeSpace.w = ndcSpace[0] * projectInv.e03 + ndcSpace[1] * projectInv.e13 + ndcSpace[2] * projectInv.e23 + ndcSpace[3] * projectInv.e33;

	Mat4x4 viewInv = Mat4x4::Inverse(view);
	Vec4f worldSpace;
	worldSpace.x = eyeSpace.x * viewInv.e00 + eyeSpace.y * viewInv.e10 + eyeSpace.z * viewInv.e20 + eyeSpace.w * viewInv.e30;
	worldSpace.y = eyeSpace.x * viewInv.e01 + eyeSpace.y * viewInv.e11 + eyeSpace.z * viewInv.e21 + eyeSpace.w * viewInv.e31;
	worldSpace.z = eyeSpace.x * viewInv.e02 + eyeSpace.y * viewInv.e12 + eyeSpace.z * viewInv.e22 + eyeSpace.w * viewInv.e32;
	worldSpace.w = eyeSpace.x * viewInv.e03 + eyeSpace.y * viewInv.e13 + eyeSpace.z * viewInv.e23 + eyeSpace.w * viewInv.e33;

	if (!MathModule::NearZero(worldSpace.w))
	{
		worldSpace.x /= worldSpace.w;
		worldSpace.y /= worldSpace.w;
		worldSpace.z /= worldSpace.w;
	}

	return Vec3f(worldSpace.x, worldSpace.y, worldSpace.z);
}

void Camera::UpdateMouseRay(const Vec2f& mousePos, const Vec2f& viewportOrigin, const Vec2f& viewportSize, const Mat4x4& view, const Mat4x4& projection)
{
	Vec3f nearPosition(mousePos.x, mousePos.y, 0.0f);
	Vec3f farPosition(mousePos.x, mousePos.y, 1.0f);

	Vec3f pNear = Unproject(nearPosition, viewportOrigin, viewportSize, view, projection);
	Vec3f pFar = Unproject(farPosition, viewportOrigin, viewportSize, view, projection);
	
	mouseRay_.origin = pNear;
	mouseRay_.direction = Vec3f::Normalize(pFar - pNear);
}