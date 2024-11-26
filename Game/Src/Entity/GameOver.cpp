#include <glm/gtc/type_ptr.hpp>

#include "Entity/GameOver.h"
#include "GL/GLManager.h"
#include "GL/RenderManager2D.h"
#include "GL/TextureAtlas2D.h"
#include "Utils/Assertion.h"

GameOver::GameOver()
{
	tickOrder_ = 1;
	renderOrder_ = 1;

	textureAtlas_ = GLManager::GetRef().GetByName<TextureAtlas2D>("TextureAtlas");

	bound_ = Rect2D(glm::vec2(0.0f, 160.0f), glm::vec2(650.0f, 195.0f));

	bIsInitialized_ = true;
}

GameOver::~GameOver()
{
	if (bIsInitialized_)
	{
		Release();
	}
}

void GameOver::Tick(float deltaSeconds)
{
}

void GameOver::Render()
{
	renderManager_->DrawTextureAtlas(textureAtlas_, "GameOver", bound_.center, bound_.size.x, bound_.size.y, 0.0f);
}

void GameOver::Release()
{
	CHECK(bIsInitialized_);

	textureAtlas_ = nullptr;

	bIsInitialized_ = false;
}