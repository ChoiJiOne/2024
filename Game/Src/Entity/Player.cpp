#include <array>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtc/constants.hpp>
#include <glm/gtc/epsilon.hpp>

#include "Entity/Player.h"
#include "GL/GLManager.h"
#include "GL/SpriteAnimator2D.h"
#include "GL/TextureAtlas2D.h"
#include "GLFW/GLFWManager.h"
#include "Utils/Assertion.h"

Player::Player()
{
	textureAtlas_ = GLManager::GetRef().GetByName<TextureAtlas2D>("TextureAtlas");
	renderBound_ = Rect2D(glm::vec2(0.0f, 0.0f), glm::vec2(66.0f, 64.0f));
	collisionBound_.radius = 22.0f;
	collisionBound_.center = renderBound_.center;
	collisionBound_.center.y += -renderBound_.size.y * 0.5f + collisionBound_.radius;

	shadow_.scale = 0.5f;
	shadow_.bound = renderBound_;
	shadow_.bound.size.y *= shadow_.scale;
	shadow_.bound.center.y += (-renderBound_.size.y * 0.5f) + (-shadow_.bound.size.y * 0.5f);
	shadow_.option.blend = glm::vec3(0.0f, 0.0f, 0.0f);
	shadow_.option.factor = 1.0f;
	shadow_.option.transparent = 0.3f;
	shadow_.option.bIsFlipV = true;

	direction_ = glm::vec2(0.0f, -1.0f);
	speed_ = 500.0f;

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
	bool bIsPress = false;
	const static std::map<EKey, glm::vec2> KEY_DIRECTIONS =
	{
		{ EKey::KEY_LEFT,  glm::vec2(-1.0f, +0.0f) },
		{ EKey::KEY_UP,    glm::vec2(+0.0f, +1.0f) },
		{ EKey::KEY_RIGHT, glm::vec2(+1.0f, +0.0f) },
		{ EKey::KEY_DOWN,  glm::vec2(+0.0f, -1.0f) },
	};

	GLFWManager& glfwManager = GLFWManager::GetRef();
	glm::vec2 direction = glm::vec2(0.0f, 0.0f);
	for (const auto& keyDirection : KEY_DIRECTIONS)
	{
		if (glfwManager.GetKeyPress(keyDirection.first) == EPress::HELD)
		{
			direction += keyDirection.second;
			bIsPress = true;
		}
	}

	if (bIsPress)
	{
		animationState_ = EAnimationState::RUN;
		direction_ = direction;

		renderBound_.center += direction_ * speed_ * deltaSeconds;

		collisionBound_.center = renderBound_.center;
		collisionBound_.center.y += -renderBound_.size.y * 0.5f + collisionBound_.radius;

		shadow_.bound.center = renderBound_.center;
		shadow_.bound.center.y += (-renderBound_.size.y * 0.5f) + (-shadow_.bound.size.y * 0.5f);

		if (glm::epsilonNotEqual<float>(direction_.x, 0.0f, glm::epsilon<float>()))
		{
			renderOption_.bIsFlipH = (direction_.x < 0.0f);
			shadow_.option.bIsFlipH = renderOption_.bIsFlipH;
		}
	}
	else
	{
		animationState_ = EAnimationState::IDLE;
	}

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
		0.0f,
		renderOption_
	);

	RenderManager2D::GetRef().DrawTextureAtlas(
		animations_.at(animationState_)->GetTextureAtlas(),
		animations_.at(animationState_)->GetCurrentClipName(),
		shadow_.bound.center,
		shadow_.bound.size.x,
		shadow_.bound.size.y,
		0.0f,
		shadow_.option
	);
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