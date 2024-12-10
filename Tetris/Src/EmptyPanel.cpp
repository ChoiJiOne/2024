#include "Assertion.h"
#include "RenderManager2D.h"

#include "EmptyPanel.h"

EmptyPanel::EmptyPanel()
{
	bound_ = Rect2D(Vec2f(195.0f, -30.0f), Vec2f(150.0f, 400.0f));
	side_ = 10.0f;
	color_ = Vec4f(0.0f, 0.0f, 0.0f, 0.5f);
	
	bIsInitialized_ = true;
}

EmptyPanel::~EmptyPanel()
{
	if (bIsInitialized_)
	{
		Release();
	}
}

void EmptyPanel::Tick(float deltaSeconds)
{
}

void EmptyPanel::Render()
{
	RenderManager2D::GetRef().DrawRoundRect(bound_.center, bound_.size.x, bound_.size.y, side_, color_, 0.0f);
}

void EmptyPanel::Release()
{
	CHECK(bIsInitialized_);

	bIsInitialized_ = false;
}
