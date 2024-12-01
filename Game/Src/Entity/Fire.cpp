#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/vector_angle.hpp>

#include "Audio/AudioManager.h"
#include "Audio/Sound.h"
#include "Entity/EntityManager.h"
#include "Entity/Fire.h"
#include "Entity/GamePlayRecorder.h"
#include "Entity/Player.h"
#include "Game/GameManager.h"
#include "GL/GLManager.h"
#include "GL/SpriteAnimator2D.h"
#include "GL/TextureAtlas2D.h"
#include "Utils/Assertion.h"
#include "Utils/Math.h"

Fire::Fire(const glm::vec2& position, const glm::vec2& direction, float speed, float lifeTime)
	: IObject(IObject::EType::FIRE)
	, direction_(direction)
	, speed_(speed)
	, lifeTime_(lifeTime)
{
	textureAtlas_ = GLManager::GetRef().GetByName<TextureAtlas2D>("TextureAtlas");
	explosionSound_ = AudioManager::GetRef().GetByName<Sound>("Explosion");
	
	float rotate = GetRadianVec2(direction_);
	renderBound_ = OrientedRect2D(position, glm::vec2(58.0f, 54.0f), rotate);

	collisionBound_.center = renderBound_.center;
	collisionBound_.radius = 20.0f;

	LoadAnimations();

	damage_ = GameManager::GetRef().GetConfigValue<float>("Fire.damage");
	state_ = EState::MOVE;

	GamePlayRecorder* gamePlayRecorder = EntityManager::GetRef().GetByName<GamePlayRecorder>("GamePlayRecorder");
	gamePlayRecorder->AddRecord(GamePlayRecorder::ERecordType::GEN_FIRE, 1);

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
		animations_.at(animationState_)->Update(deltaSeconds);

		if (collisionBound_.Intersect(player_->GetCollider()))
		{
			float hp = player_->GetHP();
			hp -= damage_;
			player_->SetHP(hp);

			animationState_ = EAnimationState::EXPLOSION;
			state_ = EState::WAIT;
		}

		lifeTime_ -= deltaSeconds;
		if (lifeTime_ <= 0.0f)
		{
			animationState_ = EAnimationState::EXPLOSION;
			state_ = EState::WAIT;
		}

		if (animationState_ == EAnimationState::EXPLOSION && player_->GetState() != Player::EState::HURT)
		{
			explosionSound_->Start();
		}
	}
	break;

	case EState::WAIT:
	{
		SpriteAnimator2D* animation = animations_.at(animationState_);
		animation->Update(deltaSeconds);
		if (animation->GetTime() >= animation->GetAnimationTime())
		{
			state_ = EState::DONE;
		}
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

	TextureAtlas2D* animationTexture = animations_.at(animationState_)->GetTextureAtlas();
	const std::string& animationClipName = animations_.at(animationState_)->GetCurrentClipName();

	renderManager_->DrawTextureAtlas(animationTexture, animationClipName, renderBound_.center, renderBound_.size.x, renderBound_.size.y, renderBound_.rotate);
}

void Fire::Release()
{
	CHECK(bIsInitialized_);

	UnloadAnimation();

	explosionSound_ = nullptr;
	textureAtlas_ = nullptr;
	
	IObject::Release();
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

void Fire::LoadAnimations()
{
	GLManager& glManager = GLManager::GetRef();

	std::vector<std::string> fireBallClipNames =
	{
		"Fireball_1",
		"Fireball_2",
		"Fireball_3",
		"Fireball_4",
		"Fireball_5",
	};	
	SpriteAnimator2D* fireBall = glManager.Create<SpriteAnimator2D>(textureAtlas_, fireBallClipNames, 0.2f, true);
	animations_.insert({ EAnimationState::BURN, fireBall });

	std::vector<std::string> fireBallHitClipNames =
	{
		"Fireball_Hit_1",
		"Fireball_Hit_2",
		"Fireball_Hit_3",
		"Fireball_Hit_4",
		"Fireball_Hit_5",
		"Fireball_Hit_6",
	};
	SpriteAnimator2D* fireBallHit = glManager.Create<SpriteAnimator2D>(textureAtlas_, fireBallHitClipNames, 0.5f, false);
	animations_.insert({ EAnimationState::EXPLOSION, fireBallHit });
}

void Fire::UnloadAnimation()
{
	GLManager& glManager = GLManager::GetRef();
	for (auto& animation : animations_)
	{
		glManager.Destroy(animation.second);
	}
}