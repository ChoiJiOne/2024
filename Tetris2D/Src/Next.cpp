#include "Assertion.h"
#include "RenderManager2D.h"
#include "TTFont.h"

#include "Next.h"

Next::Next()
{
	lineColor_ = Vec4f(0.5f, 0.5f, 0.5f, 0.5f);

	Vec2f startPos = Vec2f(135.0f, 115.0f);
	Vec2f endPos = Vec2f(255.0f, 55.0f);
	float stride = 30.0f;
	for (int32_t xi = 0; xi < 5; ++xi)
	{
		lines_.push_back(Vec2f(startPos.x + static_cast<float>(xi) * stride, startPos.y));
		lines_.push_back(Vec2f(startPos.x + static_cast<float>(xi) * stride, endPos.y));
	}

	for (int32_t yi = 0; yi < 3; ++yi)
	{
		lines_.push_back(Vec2f(startPos.x, startPos.y - static_cast<float>(yi) * stride));
		lines_.push_back(Vec2f(endPos.x, startPos.y - static_cast<float>(yi) * stride));
	}
	
	bIsInitialized_ = true;
}

Next::~Next()
{
	if (bIsInitialized_)
	{
		Release();
	}
}

void Next::Tick(float deltaSeconds)
{
}

void Next::Render()
{
	for (uint32_t index = 0; index < lines_.size(); index += 2)
	{
		RenderManager2D::Get().DrawLine(lines_[index + 0], lines_[index + 1], lineColor_);
	}
}

void Next::Release()
{
	CHECK(bIsInitialized_);

	bIsInitialized_ = false;
}
