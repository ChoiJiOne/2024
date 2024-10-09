#include "Assertion.h"
#include "RenderManager2D.h"
#include "ResourceManager.h"
#include "TTFont.h"

#include "Next.h"

Next::Next()
{
	font_ = ResourceManager::Get().GetByName<TTFont>("Font32");

	text_ = L"NEXT";
	Vec2f textSize;
	font_->MeasureText(text_, textSize.x, textSize.y);

	Vec2f textPos = Vec2f(195.0f, 140.0f);
	textPos_ = textPos + Vec2f(-textSize.x * 0.5f, +textSize.y * 0.5f);
	textColor_ = Vec4f(1.0f, 1.0f, 1.0f, 1.0f);

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

	lineColor_ = Vec4f(0.5f, 0.5f, 0.5f, 0.5f);
	
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
	RenderManager2D& renderMgr = RenderManager2D::Get();

	renderMgr.DrawString(font_, text_, textPos_, textColor_);
	for (uint32_t index = 0; index < lines_.size(); index += 2)
	{
		renderMgr.DrawLine(lines_[index + 0], lines_[index + 1], lineColor_);
	}
}

void Next::Release()
{
	CHECK(bIsInitialized_);

	font_ = nullptr;

	bIsInitialized_ = false;
}
