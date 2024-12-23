#include "Assertion.h"
#include "Atlas2D.h"
#include "EntityManager.h"
#include "GameUtils.h"
#include "IApp.h"
#include "RenderManager2D.h"
#include "ResourceManager.h"
#include "TTFont.h"

#include "Title.h"

Title::Title()
{
	font_ = ResourceManager::Get().GetByName<TTFont>("Font72");
	text_ = L"CoinDash";
	textColor_ = Vec4f(1.0f, 1.0f, 1.0f, 1.0f);
	textShadowColor_ = Vec4f(0.5f, 0.5f, 0.5f, 0.5f);

	Vec2f size;
	font_->MeasureText(text_, size.x, size.y);

	textPos_ = Vec2f(0.0f, 100.0f) + Vec2f(-size.x * 0.5f, +size.y * 0.5f);
	textShadowPos_ = textPos_ + Vec2f(+3.0f, -3.0f);
	
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
	RenderManager2D::Get().DrawString(font_, text_, textShadowPos_, textShadowColor_);
	RenderManager2D::Get().DrawString(font_, text_, textPos_, textColor_);
}

void Title::Release()
{
	CHECK(bIsInitialized_);

	font_ = nullptr;

	bIsInitialized_ = false;
}
