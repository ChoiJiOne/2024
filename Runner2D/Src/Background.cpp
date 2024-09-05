#include "Assertion.h"
#include "Atlas2D.h"
#include "RenderManager2D.h"
#include "ResourceManager.h"
#include "IApp.h"

#include "Background.h"
#include "Camera.h"

Background::Background(Camera* camera)
	: camera_(camera)
	, bCanMove_(false)
{
	atlas_ = ResourceManager::Get().GetByName<Atlas2D>("Atlas");
	rects_ =
	{ 
		Rect2D(GameMath::Vec2f(-camera->GetWidth() * 0.5f, 0.0f), GameMath::Vec2f(camera->GetWidth(), camera->GetHeight())),
		Rect2D(GameMath::Vec2f(+camera->GetWidth() * 0.5f, 0.0f), GameMath::Vec2f(camera->GetWidth(), camera->GetHeight())),
	};
	
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
	if (!bCanMove_)
	{
		return;
	}

	for (auto& rect : rects_)
	{
		rect.center.x -= deltaSeconds * scrollSpeed_;
	}

	if (!rects_.front().Intersect(camera_->GetCollision()))
	{
		rects_.front() = rects_.back();
		rects_.back().center.x = rects_.front().center.x + rects_.front().size.x;
	}
}

void Background::Render()
{
	for (const auto& rect : rects_)
	{
		RenderManager2D::Get().DrawSprite(atlas_, "Background", rect.center, rect.size.x, rect.size.y);
	}
}

void Background::Release()
{
	CHECK(bIsInitialized_);

	camera_ = nullptr;
	atlas_ = nullptr;

	bIsInitialized_ = false;
}