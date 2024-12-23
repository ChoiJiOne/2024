#include "Assertion.h"
#include "Atlas2D.h"
#include "IApp.h"
#include "RenderManager2D.h"
#include "ResourceManager.h"

#include "Background.h"

Background::Background()
{
	atlas_ = ResourceManager::Get().GetByName<Atlas2D>("Atlas");
	
	IApp::Get()->GetScreenSize(rect_.size.x, rect_.size.y);

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
	static RenderManager2D::SpriteRenderOptions option;
	RenderManager2D::Get().DrawSprite(atlas_, "Grass", rect_.center, rect_.size.x, rect_.size.y, 0.0f, option);
}

void Background::Release()
{
	CHECK(bIsInitialized_);

	atlas_ = nullptr;

	bIsInitialized_ = false;
}
