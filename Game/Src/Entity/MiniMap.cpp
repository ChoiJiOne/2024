#include "Entity/UICamera.h"
#include "Entity/MiniMap.h"
#include "Entity/Player.h"
#include "Entity/Playground.h"
#include "GL/GLManager.h"
#include "GL/TextureAtlas2D.h"
#include "GLFW/GLFWManager.h"
#include "Utils/Assertion.h"

MiniMap::MiniMap(UICamera* uiCamera)
	: uiCamera_(uiCamera)
{
	tickOrder_ = 0;
	renderOrder_ = 0;

	textureAtlas_ = GLManager::GetRef().GetByName<TextureAtlas2D>("TextureAtlas");
	
	glm::vec2 uiCameraSize = uiCamera_->GetSize() * 0.5f;
	renderBound_ = Rect2D(glm::vec2(0.0f, 0.0f), glm::vec2(256.0f, 256.0f));
	renderBound_.center = glm::vec2(uiCameraSize.x, -uiCameraSize.y);
	renderBound_.center += glm::vec2(-renderBound_.size.x, +renderBound_.size.y) * 0.5f;

	bIsInitialized_ = true;
}

MiniMap::~MiniMap()
{
	if (bIsInitialized_)
	{
		Release();
	}
}

void MiniMap::Tick(float deltaSeconds)
{
}

void MiniMap::Render()
{
	renderManager_->DrawTextureAtlas(textureAtlas_, "MiniMap", renderBound_.center, renderBound_.size.x, renderBound_.size.y, 0.0f);
}

void MiniMap::Release()
{
	CHECK(bIsInitialized_);

	textureAtlas_ = nullptr;

	bIsInitialized_ = false;
}
