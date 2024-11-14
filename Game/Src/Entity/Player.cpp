#include <imgui.h>

#include "Entity/Player.h"
#include "GL/GLManager.h"
#include "GL/RenderManager2D.h"
#include "GL/SpriteAnimator2D.h"
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

	LoadAnimations();

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
	ImGui::Begin("ANIMATION");
	if (ImGui::RadioButton("IDLE", static_cast<int32_t>(animationState_) == 0))
	{
		animationState_ = EAnimationState::IDLE;
	}

	if (ImGui::RadioButton("RUN", static_cast<int32_t>(animationState_) == 1))
	{
		animationState_ = EAnimationState::RUN;
	}

	if (ImGui::RadioButton("HURT", static_cast<int32_t>(animationState_) == 2))
	{
		animationState_ = EAnimationState::HURT;
	}

	ImGui::End();

	animations_.at(animationState_)->Update(deltaSeconds);
}

void Player::Render()
{
	RenderManager2D::GetRef().DrawTextureAtlas(
		animations_.at(animationState_)->GetTextureAtlas(),
		animations_.at(animationState_)->GetCurrentClipName(),
		renderBound_.center, 
		renderBound_.size.x, 
		renderBound_.size.y, 
		0.0f
	);
	RenderManager2D::GetRef().DrawRectWireframe(renderBound_.center, renderBound_.size.x, renderBound_.size.y, glm::vec4(1.0f, 0.0f, 0.0f, 1.0f), 0.0f);
	RenderManager2D::GetRef().DrawLine(glm::vec2(-500.0f, 0.0f), glm::vec2(500.0f, 0.0f), glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
	RenderManager2D::GetRef().DrawLine(glm::vec2(0.0f, 400.0f), glm::vec2(0.0f, -400.0f), glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
	RenderManager2D::GetRef().DrawCircleWireframe(collisionBound_.center, collisionBound_.radius, glm::vec4(0.0f, 0.0f, 1.0f, 1.0f));
}

void Player::Release()
{
	CHECK(bIsInitialized_);

	UnloadAnimation();
	textureAtlas_ = nullptr;

	bIsInitialized_ = false;
}

void Player::LoadAnimations()
{
	GLManager& glManager = GLManager::GetRef();

	std::vector<std::string> idleClipNames =
	{
		"Foxy_Idle_1",
		"Foxy_Idle_2",
		"Foxy_Idle_3",
		"Foxy_Idle_4",
	};
	SpriteAnimator2D* idleAnimation = glManager.Create<SpriteAnimator2D>(textureAtlas_, idleClipNames, 0.5f, true);
	animations_.insert( { EAnimationState::IDLE, idleAnimation } );

	std::vector<std::string> runClipNames =
	{
		"Foxy_Run_1",
		"Foxy_Run_2",
		"Foxy_Run_3",
		"Foxy_Run_4",
		"Foxy_Run_5",
		"Foxy_Run_6",
	};
	SpriteAnimator2D* runAnimation = glManager.Create<SpriteAnimator2D>(textureAtlas_, runClipNames, 0.5f, true);
	animations_.insert({ EAnimationState::RUN, runAnimation });

	std::vector<std::string> hurtClipNames =
	{
		"Foxy_Hurt_1",
		"Foxy_Hurt_2",
	};
	SpriteAnimator2D* hurtAnimation = glManager.Create<SpriteAnimator2D>(textureAtlas_, hurtClipNames, 0.3f, true);
	animations_.insert({ EAnimationState::HURT, hurtAnimation });
}

void Player::UnloadAnimation()
{
	GLManager& glManager = GLManager::GetRef();
	for (auto& animation : animations_)
	{
		glManager.Destroy(animation.second);
	}
}