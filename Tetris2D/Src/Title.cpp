#include "Assertion.h"
#include "RenderManager2D.h"
#include "ResourceManager.h"
#include "TTFont.h"

#include "Title.h"

Title::Title()
{
	font_ = ResourceManager::Get().GetByName<TTFont>("Font128");

	text_ = L"TETRIS2D";
	Vec2f textSize;
	font_->MeasureText(text_, textSize.x, textSize.y);

	Vec2f textPos = Vec2f(0.0f, 200.0f);
	textPos_ = textPos + Vec2f(-textSize.x * 0.5f, +textSize.y * 0.5f);
	textColor_ = Vec4f(1.0f, 1.0f, 1.0f, 1.0f);

	bIsInitialized_ = true;
}

Title::~Title()
{
	if (bIsInitialized_)
	{
		Release();
	}
}

void Title::Tick(float deltaSeconds)
{
}

void Title::Render()
{
	RenderManager2D& renderMgr = RenderManager2D::Get();
	renderMgr.DrawString(font_, text_, textPos_, textColor_);
}

void Title::Release()
{
	CHECK(bIsInitialized_);

	font_ = nullptr;

	bIsInitialized_ = false;
}
