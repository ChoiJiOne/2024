#include "Entity/Background.h"
#include "Entity/EntityManager.h"
#include "Entity/PlayerFollowCamera.h"
#include "GL/GLManager.h"
#include "GL/RenderManager2D.h"
#include "GL/Texture2D.h"
#include "GLFW/GLFWManager.h"
#include "Utils/Assertion.h"

Background::Background()
{
	camera_ = EntityManager::GetRef().GetByName<PlayerFollowCamera>("PlayerFollowCamera");

	glm::vec2 screenSize = glm::vec2(0.0f, 0.0f);
	GLFWManager::GetRef().GetWindowSize(screenSize.x, screenSize.y);

	textureAtlas_ = GLManager::GetRef().GetByName<TextureAtlas2D>("TextureAtlas");
	screenBound_ = Rect2D(camera_->GetCenter(), screenSize);

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
	screenBound_.center = camera_->GetCenter();
}

void Background::Render()
{
	renderManager_->DrawTextureAtlas(textureAtlas_, "Background", screenBound_.center, screenBound_.size.x, screenBound_.size.y, 0.0f);
}

void Background::Release()
{
	CHECK(bIsInitialized_);

	textureAtlas_ = nullptr;
	camera_ = nullptr;

	bIsInitialized_ = false;
}