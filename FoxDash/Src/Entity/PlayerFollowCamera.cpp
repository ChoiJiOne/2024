#include "Entity/EntityManager.h"
#include "Entity/Player.h"
#include "Entity/PlayerFollowCamera.h"
#include "GLFW/GLFWManager.h"

PlayerFollowCamera::PlayerFollowCamera()
{
	player_ = EntityManager::GetRef().GetByName<Player>("Player");

	glm::vec2 screenSize = glm::vec2(0.0f, 0.0f);
	GLFWManager::GetRef().GetWindowSize(screenSize.x, screenSize.y);

	center_ = player_->GetPosition();
	size_ = screenSize;
	ortho_ = CalculateOrtho(center_, size_);

	bIsInitialized_ = true;
}

PlayerFollowCamera::~PlayerFollowCamera()
{
	if (bIsInitialized_)
	{
		Release();
	}
}

void PlayerFollowCamera::Tick(float deltaSeconds)
{
	center_ = player_->GetPosition();
	ortho_ = CalculateOrtho(center_, size_);
}

void PlayerFollowCamera::Release()
{
	player_ = nullptr;
	Camera2D::Release();
}