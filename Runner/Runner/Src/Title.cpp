#include "Assertion.h"
#include "Atlas2D.h"
#include "EntityManager.h"
#include "IApp.h"
#include "RenderManager2D.h"
#include "ResourceManager.h"
#include "TTFont.h"

#include "Title.h"

Title::Title()
{
	font_ = ResourceManager::Get().GetByName<TTFont>("Font128");
	title_ = L"Runner";

	Vec2f size;
	font_->MeasureText(title_, size.x, size.y);

	position_ = Vec2f(0.0f, 100.0f);
	position_ += Vec2f(-size.x * 0.5f, +size.y * 0.5f);
	shadowPosition_ = position_ + Vec2f(5.0f, -5.0f);

	titleColor_ = Vec4f(0.0f, 0.0f, 0.0f, 1.0f);
	shadowColor_ = Vec4f(0.5f, 0.5f, 0.5f, 0.5f);

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
	RenderManager2D::Get().DrawString(font_, title_, shadowPosition_, shadowColor_);
	RenderManager2D::Get().DrawString(font_, title_, position_, titleColor_);
}

void Title::Release()
{
	CHECK(bIsInitialized_);

	font_ = nullptr;

	bIsInitialized_ = false;
}
