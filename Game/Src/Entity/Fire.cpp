#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/vector_angle.hpp>

#include "Entity/Fire.h"
#include "Entity/EntityManager.h"
#include "Entity/Player.h"
#include "Entity/Playground.h"
#include "GL/GLManager.h"
#include "GL/SpriteAnimator2D.h"
#include "GL/TextureAtlas2D.h"
#include "Utils/Assertion.h"
#include "Utils/Math.h"

Fire::Fire(const glm::vec2& position, const glm::vec2& direction, float speed)
	: direction_(direction)
	, speed_(speed)
{
	tickOrder_ = 3;
	renderOrder_ = 4;

	textureAtlas_ = GLManager::GetRef().GetByName<TextureAtlas2D>("TextureAtlas");
	player_ = EntityManager::GetRef().GetByName<Player>("Player");
	playground_ = EntityManager::GetRef().GetByName<Playground>("Playground");
	
	float rotate = GetRadianVec2(direction_);
	renderBound_ = OrientedRect2D(position, glm::vec2(58.0f, 54.0f), rotate);

	collisionBound_.center = renderBound_.center;
	collisionBound_.radius = 20.0f;

	std::vector<std::string> fireBallClipNames =
	{
		"Fireball_1",
		"Fireball_2",
		"Fireball_3",
		"Fireball_4",
		"Fireball_5",
	};
	SpriteAnimator2D* fireBall = GLManager::GetRef().Create<SpriteAnimator2D>(textureAtlas_, fireBallClipNames, 0.2f, true);

	std::vector<std::string> fireBallHitClipNames =
	{
		"Fireball_Hit_1",
		"Fireball_Hit_2",
		"Fireball_Hit_3",
		"Fireball_Hit_4",
		"Fireball_Hit_5",
		"Fireball_Hit_6",
	};
	SpriteAnimator2D* fireBallHit = GLManager::GetRef().Create<SpriteAnimator2D>(textureAtlas_, fireBallHitClipNames, 0.5f, false);

	animations_ =
	{
		{ EState::NONE,       nullptr     },
		{ EState::MOVE,       fireBall    },
		{ EState::EXPLOSION,  fireBallHit },
		{ EState::DONE,       nullptr     },
	};

	lifeTime_ = 5.0f;
	state_ = EState::MOVE;

	bIsInitialized_ = true;
}

Fire::~Fire()
{
	if (bIsInitialized_)
	{
		Release();
	}
}

void Fire::Tick(float deltaSeconds)
{
	switch (state_)
	{
	case EState::MOVE:
	{
		Move(deltaSeconds);
		animations_.at(state_)->Update(deltaSeconds);

		if (collisionBound_.Intersect(player_->GetCollider()))
		{
			state_ = EState::EXPLOSION;
		}

		lifeTime_ -= deltaSeconds;
		if (lifeTime_ <= 0.0f || !collisionBound_.Intersect(playground_->GetSafeBound()))
		{
			state_ = EState::EXPLOSION;
		}
	}
	break;

	case EState::EXPLOSION:
	{
		SpriteAnimator2D* animation = animations_.at(state_);
		animation->Update(deltaSeconds);
		if (animation->GetTime() >= animation->GetAnimationTime())
		{
			state_ = EState::DONE;
		}
	}
	break;
	
	case EState::DONE:
	{

	}
	break;
	}
}

void Fire::Render()
{
	if (state_ == EState::NONE || state_ == EState::DONE)
	{
		return;
	}

	TextureAtlas2D* animationTexture = animations_.at(state_)->GetTextureAtlas();
	const std::string& animationClipName = animations_.at(state_)->GetCurrentClipName();

	renderManager_->DrawTextureAtlas(animationTexture, animationClipName, renderBound_.center, renderBound_.size.x, renderBound_.size.y, renderBound_.rotate);
}

void Fire::Release()
{
	CHECK(bIsInitialized_);

	GLManager::GetRef().Destroy(animations_.at(EState::MOVE));
	GLManager::GetRef().Destroy(animations_.at(EState::EXPLOSION));

	playground_ = nullptr;
	player_ = nullptr;
	textureAtlas_ = nullptr;
	
	bIsInitialized_ = false;
}

void Fire::Move(float deltaSeconds)
{
	direction_ = glm::normalize(player_->GetCollider()->center - renderBound_.center);
	renderBound_.rotate = GetRadianVec2(direction_);

	glm::vec2 movePos = renderBound_.center;
	movePos += direction_ * deltaSeconds * speed_;

	renderBound_.center = movePos;
	collisionBound_.center = movePos;
}