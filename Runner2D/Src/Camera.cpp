#include "Assertion.h"
#include "IApp.h"

#include "Camera.h"

Camera::Camera()
{
	IApp::Get()->GetScreenSize<float>(size_.x, size_.y);

	center_ = Vec2f(0.0f);
	ortho_ = CalculateOrtho(center_, size_.x, size_.y);
	rect_ = Rect2D(center_, Vec2f(size_.x, size_.y));

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
	// nothing...
}

void Camera::Release()
{
	CHECK(bIsInitialized_);
	bIsInitialized_ = false;
}