#include "Assertion.h"
#include "RenderManager2D.h"
#include "ResourceManager.h"
#include "TTFont.h"

#include "Score.h"

Score::Score()
{
	font_ = ResourceManager::Get().GetByName<TTFont>("Font32");

	text_ = L"SCORE";
	Vec2f textSize;
	font_->MeasureText(text_, textSize.x, textSize.y);
	
	Vec2f textPos = Vec2f(195.0f, 0.0f);
	textPos_ = textPos + Vec2f(-textSize.x * 0.5f, +textSize.y * 0.5f);
	textColor_ = Vec4f(1.0f, 1.0f, 1.0f, 1.0f);

	bIsInitialized_ = true;
}

Score::~Score()
{
	if (bIsInitialized_)
	{
		Release();
	}
}

void Score::Tick(float deltaSeconds)
{
	if (bIsUpdateScore_)
	{


		bIsUpdateScore_ = false;
	}
}

void Score::Render()
{
	RenderManager2D::Get().DrawString(font_, text_, textPos_, textColor_);
}

void Score::Release()
{
	CHECK(bIsInitialized_);

	font_ = nullptr;

	bIsInitialized_ = false;
}

void Score::SetScore(int32_t score)
{
	score_ = score;
	bIsUpdateScore_ = true;
}