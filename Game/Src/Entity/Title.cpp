#include <glm/gtc/type_ptr.hpp>

#include "Entity/Title.h"
#include "GL/GLManager.h"
#include "GL/RenderManager2D.h"
#include "GL/TextureAtlas2D.h"
#include "Utils/Assertion.h"

Title::Title()
{
	textureAtlas_ = GLManager::GetRef().GetByName<TextureAtlas2D>("TextureAtlas");

	bound_ = Rect2D(glm::vec2(0.0f, 160.0f), glm::vec2(650.0f, 195.0f));

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
	renderManager_->DrawTextureAtlas(textureAtlas_, "Title", bound_.center, bound_.size.x, bound_.size.y, 0.0f);
}

void Title::Release()
{
	CHECK(bIsInitialized_);

	textureAtlas_ = nullptr;

	bIsInitialized_ = false;
}