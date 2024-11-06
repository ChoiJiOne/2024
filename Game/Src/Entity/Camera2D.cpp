#include <glm/gtc/matrix_transform.hpp>

#include "Entity/Camera2D.h"
#include "Utils/Assertion.h"

Camera2D::Camera2D(const glm::vec2& center, const glm::vec2& size) 
	: center_(center)
	, size_(size)
{
	ortho_ = CalculateOrtho(center_, size_);
	bIsInitialized_ = true;
}

Camera2D::~Camera2D()
{
	if (bIsInitialized_)
	{
		Release();
	}
}

void Camera2D::Tick(float deltaSeconds)
{
	// nothing...
}

void Camera2D::Release()
{
	CHECK(bIsInitialized_);

	// nothing...
	
	bIsInitialized_ = false;
}

glm::mat4 Camera2D::CalculateOrtho(const glm::vec2& center, const glm::vec2& size, float zNear, float zFar)
{
	return glm::ortho(-size.x * 0.5f + center.x, +size.x * 0.5f + center.x, -size.y * 0.5f + center.y, +size.y * 0.5f + center.y, zNear, zFar);
}