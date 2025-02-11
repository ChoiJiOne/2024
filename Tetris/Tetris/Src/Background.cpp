#include "Assertion.h"
#include "EntityManager.h"
#include "ResourceManager.h"
#include "Texture2D.h"

#include "Background.h"

Background::Background()
{
	bound_ = Rect2D(Vec2f(0.0f, 0.0f), Vec2f(800.0f, 800.0f));
	texture_ = ResourceManager::GetRef().GetByName<Texture2D>("Background");
	
	bIsInitialized_ = true;
}

Background::~Background()
{
	if (bIsInitialized_)
	{
		Release();
	}
}

void Background::Tick(float deltaSeconds)
{
}

void Background::Render()
{
	RenderManager2D::GetRef().DrawSprite(texture_, bound_.center, bound_.size.x, bound_.size.y, 0.0f, option_);
}

void Background::Release()
{
	CHECK(bIsInitialized_);

	texture_ = nullptr;

	bIsInitialized_ = false;
}
