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

	CursorPos curr = InputController::GetCurrCursorPos();
	Vec2f mousePos = Vec2f(static_cast<float>(curr.x), static_cast<float>(curr.y));
	Vec2f viewportSize = Vec2f(static_cast<float>(screenWidth), static_cast<float>(screenHeight));

	UpdateMouseRay(mousePos, Vec2f(0.0f, 0.0f), viewportSize, view_, projection_);
	
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

	bool bIsUpdateRotateState = UpdateRotateState(deltaSeconds);
	bool bIsUpdateMoveState = UpdateMoveState(deltaSeconds);

	if (bIsUpdateRotateState || bIsUpdateMoveState)
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

bool Camera::UpdateRotateState(float deltaSeconds)
{
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

	return bIsUpdateState;
}

bool Camera::UpdateMoveState(float deltaSeconds)
{
	bool bIsUpdateState = false;

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

	return bIsUpdateState;
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
	Vec4f ndcSpace((viewportPosition.x - viewportOrigin.x) / viewportSize.x, (viewportPosition.y - viewportOrigin.y) / viewportSize.y, viewportPosition.z, 1.0f);
	ndcSpace.x = ndcSpace.x * 2.0f - 1.0f;
	ndcSpace.y = 1.0f - ndcSpace.y * 2.0f;
	ndcSpace.z = MathModule::Clamp<float>(ndcSpace.z, 0.0f, 1.0f);

	Mat4x4 projectInv = Mat4x4::Inverse(projection);
	Vec4f eyeSpace = ndcSpace * projectInv;

	Mat4x4 viewInv = Mat4x4::Inverse(view);
	Vec4f worldSpace = eyeSpace * viewInv;

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