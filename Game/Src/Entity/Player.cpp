#include <imgui.h>

#include "Entity/Player.h"
#include "GL/GLManager.h"
#include "GL/RenderManager2D.h"
#include "GL/Texture2D.h"
#include "GLFW/GLFWManager.h"
#include "Utils/Assertion.h"

Player::Player()
{
	textureAtlas_ = GLManager::GetRef().GetByName<TextureAtlas2D>("TextureAtlas");
	renderBound_ = Rect2D(glm::vec2(0.0f, 0.0f), glm::vec2(66.0f, 64.0f));
	collisionBound_.radius = 22.0f;
	collisionBound_.center.x = 0.0f;
	collisionBound_.center.y = renderBound_.center.y - renderBound_.size.y * 0.5f + collisionBound_.radius;

	bIsInitialized_ = true;
}

Player::~Player()
{
	if (bIsInitialized_)
	{
		Release();
	}
}

void Player::Tick(float deltaSeconds)
{
	ImGui::Begin("CONTROL");
	ImGui::SliderFloat("Radius", &collisionBound_.radius, 0.0f, 30.0f);

	collisionBound_.center.y = renderBound_.center.y - renderBound_.size.y * 0.5f + collisionBound_.radius;


	ImGui::End();
}

void Player::Render()
{
	RenderManager2D::GetRef().DrawTextureAtlas(textureAtlas_, "Foxy_Idle_1", renderBound_.center, renderBound_.size.x, renderBound_.size.y, 0.0f);
	RenderManager2D::GetRef().DrawRectWireframe(renderBound_.center, renderBound_.size.x, renderBound_.size.y, glm::vec4(1.0f, 0.0f, 0.0f, 1.0f), 0.0f);
	RenderManager2D::GetRef().DrawLine(glm::vec2(-500.0f, 0.0f), glm::vec2(500.0f, 0.0f), glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
	RenderManager2D::GetRef().DrawLine(glm::vec2(0.0f, 400.0f), glm::vec2(0.0f, -400.0f), glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
	RenderManager2D::GetRef().DrawCircleWireframe(collisionBound_.center, collisionBound_.radius, glm::vec4(0.0f, 0.0f, 1.0f, 1.0f));
}

void Player::Release()
{
	CHECK(bIsInitialized_);

	textureAtlas_ = nullptr;

	bIsInitialized_ = false;
}
