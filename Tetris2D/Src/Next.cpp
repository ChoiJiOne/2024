#include "Assertion.h"
#include "RenderManager2D.h"

#include "Next.h"

Next::Next()
	: backgroundColor_(Vec4f(0.0f, 0.0f, 0.0f, 0.5f))
	, lineColor_(Vec4f(0.5f, 0.5f, 0.5f, 0.5f))
{
	Vec2f startPos = Vec2f(135.0f, 115.0f);
	Vec2f endPos = Vec2f(255.0f, 55.0f);

	background_.center = (startPos + endPos) * 0.5f;
	background_.size = Vec2f(endPos.x - startPos.x, startPos.y - endPos.y);

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
	RenderManager2D& renderMgr = RenderManager2D::GetRef();

	renderMgr.DrawRect(background_.center, background_.size.x, background_.size.y, backgroundColor_, 0.0f);
	for (uint32_t index = 0; index < lines_.size(); index += 2)
	{
		renderMgr.DrawLine(lines_[index + 0], lines_[index + 1], lineColor_);
	}
}

void Next::Release()
{
	CHECK(bIsInitialized_);

	bIsInitialized_ = false;
}
