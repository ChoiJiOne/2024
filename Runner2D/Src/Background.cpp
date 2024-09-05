#include "Assertion.h"
#include "RenderManager2D.h"
#include "ResourceManager.h"
#include "IApp.h"
#include "Texture2D.h"

#include "Background.h"
#include "Camera.h"

Background::Background(Camera* camera)
	: camera_(camera)
{
	texture_ = ResourceManager::Get().GetByName<Texture2D>("Background");
	rect_ = Rect2D(camera->GetCenter(), GameMath::Vec2f(camera->GetWidth(), camera->GetHeight()));

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
	RenderManager2D::Get().DrawSprite(texture_, rect_.center, rect_.size.x, rect_.size.y);
}

void Background::Release()
{
	CHECK(bIsInitialized_);

	camera_ = nullptr;
	texture_ = nullptr;

	bIsInitialized_ = false;
}