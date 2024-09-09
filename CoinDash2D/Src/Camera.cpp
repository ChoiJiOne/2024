#include "Assertion.h"
#include "IApp.h"

#include "Camera.h"

Camera::Camera()
{
	IApp::Get()->GetScreenSize<float>(width_, height_);

	center_ = GameMath::Vec2f(0.0f);
	ortho_ = CalculateOrtho(center_, width_, height_);
	rect_ = Rect2D(center_, GameMath::Vec2f(width_, height_));

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
