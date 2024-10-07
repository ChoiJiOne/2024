#include "Assertion.h"
#include "IApp.h"

#include "MainCamera2D.h"

MainCamera2D::MainCamera2D()
{
	IApp::Get()->GetScreenSize<float>(size_.x, size_.y);
	
	ortho_ = CalculateOrtho(center_, size_);
	collision_ = Rect2D(center_, size_);

	bIsInitialized_ = true;
}

MainCamera2D::~MainCamera2D()
{
	if (bIsInitialized_)
	{
		Release();
	}
}

void MainCamera2D::Tick(float deltaSeconds)
{
}

void MainCamera2D::Release()
{
	CHECK(bIsInitialized_);

	bIsInitialized_ = false;
}
