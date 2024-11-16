#include "Entity/Background.h"
#include "Entity/EntityManager.h"
#include "Entity/Player.h"
#include "GL/GLManager.h"
#include "GL/RenderManager2D.h"
#include "GL/Texture2D.h"
#include "GLFW/GLFWManager.h"
#include "Utils/Assertion.h"

Background::Background()
{
	tickOrder_ = 2;
	renderOrder_ = 0;

	player_ = EntityManager::GetRef().GetByName<Player>("Player");

	glm::vec2 screenSize = glm::vec2(0.0f, 0.0f);
	GLFWManager::GetRef().GetWindowSize(screenSize.x, screenSize.y);

	textureAtlas_ = GLManager::GetRef().GetByName<TextureAtlas2D>("TextureAtlas");
	screenBound_ = Rect2D(player_->GetPosition(), screenSize);
	playground_ = Circle2D(glm::vec2(0.0f, 0.0f), 1000.0f);
	playgroundColor_ = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);

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
	screenBound_.center = player_->GetPosition();
}

void Background::Render()
{
	renderManager_->DrawTextureAtlas(textureAtlas_, "Background", screenBound_.center, screenBound_.size.x, screenBound_.size.y, 0.0f);
	renderManager_->DrawCircleWireframe(playground_.center, playground_.radius, playgroundColor_);
}

void Background::Release()
{
	CHECK(bIsInitialized_);

	textureAtlas_ = nullptr;
	player_ = nullptr;

	bIsInitialized_ = false;
}