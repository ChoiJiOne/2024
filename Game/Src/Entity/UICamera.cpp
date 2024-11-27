#include "Entity/UICamera.h"
#include "GLFW/GLFWManager.h"

UICamera::UICamera()
{
	glm::vec2 screenSize = glm::vec2(0.0f, 0.0f);
	GLFWManager::GetRef().GetWindowSize(screenSize.x, screenSize.y);

	center_ = glm::vec2(0.0f, 0.0f);
	size_ = screenSize;
	ortho_ = CalculateOrtho(center_, size_);

	mousePointer_.radius = 1.0f;
	mousePointer_.center = GLFWManager::GetRef().GetCurrCursorPos();
	
	bIsInitialized_ = true;
}

UICamera::~UICamera()
{
	if (bIsInitialized_)
	{
		Release();
	}
}

void UICamera::Tick(float deltaSeconds)
{
	mousePointer_.center = GLFWManager::GetRef().GetCurrCursorPos();
}

void UICamera::Release()
{
	Camera2D::Release();
}