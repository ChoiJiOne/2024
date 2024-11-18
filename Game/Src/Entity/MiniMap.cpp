#include "Entity/EntityManager.h"
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
	player_ = EntityManager::GetRef().GetByName<Player>("Player");
	
	Playground* playground = EntityManager::GetRef().GetByName<Playground>("Playground");
	playgroundRadius_ = playground->GetSafeBound()->radius;

	glm::vec2 uiCameraSize = uiCamera_->GetSize() * 0.5f;
	renderBound_ = Rect2D(glm::vec2(0.0f, 0.0f), glm::vec2(200.0f, 200.0f));
	renderBound_.center = glm::vec2(uiCameraSize.x, -uiCameraSize.y);
	renderBound_.center += glm::vec2(-renderBound_.size.x, +renderBound_.size.y) * 0.5f;

	minimapRadius_ = renderBound_.size.x * 0.4f;
	pointSize_ = 6.0f;
	playerColor_ = glm::vec4(0.0f, 1.0f, 0.0f, 1.0f);

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
	playerPosition_ = player_->GetCollider()->center / playgroundRadius_;
	playerPosition_ *= minimapRadius_;
	playerPosition_ += renderBound_.center;
}

void MiniMap::Render()
{
	renderManager_->DrawTextureAtlas(textureAtlas_, "MiniMap", renderBound_.center, renderBound_.size.x, renderBound_.size.y, 0.0f);

	renderManager_->DrawPoint(playerPosition_, playerColor_, pointSize_);
}

void MiniMap::Release()
{
	CHECK(bIsInitialized_);

	player_ = nullptr;
	textureAtlas_ = nullptr;

	bIsInitialized_ = false;
}
