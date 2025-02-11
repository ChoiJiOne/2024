#include "Entity/Backdrop.h"
#include "GL/GLManager.h"
#include "GL/RenderManager2D.h"
#include "GL/Texture2D.h"
#include "GLFW/GLFWManager.h"
#include "Utils/Assertion.h"

Backdrop::Backdrop()
{
	glm::vec2 screenSize = glm::vec2(0.0f, 0.0f);
	GLFWManager::GetRef().GetWindowSize(screenSize.x, screenSize.y);

	if (!texture_)
	{
		texture_ = GLManager::GetRef().Create<Texture2D>("Resource\\Texture\\Background.png", Texture2D::EFilter::NEAREST);
	}

	bound_ = Rect2D(glm::vec2(0.0f, 0.0f), screenSize);

	bIsInitialized_ = true;
}

Backdrop::~Backdrop()
{
	if (bIsInitialized_)
	{
		Release();
	}
}

void Backdrop::Tick(float deltaSeconds)
{
}

void Backdrop::Render()
{
	renderManager_->DrawTexture(texture_, bound_.center, bound_.size.x, bound_.size.y, 0.0f);
}

void Backdrop::Release()
{
	CHECK(bIsInitialized_);

	if (texture_)
	{
		GLManager::GetRef().Destroy(texture_);
		texture_ = nullptr;
	}

	bIsInitialized_ = false;
}
