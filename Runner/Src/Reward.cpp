#include "Assertion.h"
#include "Atlas2D.h"
#include "EntityManager.h"
#include "RenderManager2D.h"
#include "ResourceManager.h"
#include "Sound.h"

#include "Camera2D.h"
#include "Player.h"
#include "Reward.h"
#include "SpriteAnimation.h"

Reward::Reward(const Circle2D& bound, const Type& type)
	: player_(EntityManager::Get().GetByName<Player>("Player"))
	, camera_(EntityManager::Get().GetByName<Camera2D>("Camera"))
	, type_(type)
	, bound_(bound)
	, bCanMove_(true)
{
	atlas_ = ResourceManager::Get().GetByName<Atlas2D>("Atlas");

	LoadAnimations();

	bIsInitialized_ = true;
}

Reward::~Reward()
{
	if (bIsInitialized_)
	{
		Release();
	}
}

void Reward::Tick(float deltaSeconds)
{
	if (status_ == EStatus::DONE)
	{
		return;
	}

	bCanMove_ = GetMovable();
	if (bCanMove_)
	{
		bound_.center.x -= deltaSeconds * player_->GetSpeed();
	}

	if (!bound_.Intersect(camera_->GetCollision()) && bound_.center.x < 0.0f)
	{
		status_ = EStatus::DONE;
	}

	switch (status_)
	{
	case EStatus::ACTIVE:
	{
		if (bound_.Intersect(player_->GetCollision()))
		{
			Sound* sound = nullptr;

			if (type_ == Type::CHERRY)
			{
				sound = ResourceManager::Get().GetByName<Sound>("Reward");
				player_->PickupCherry();
			}
			else // type_ == Type::GEM
			{
				sound = ResourceManager::Get().GetByName<Sound>("SpeedUp");
				player_->PickupGem();
			}

			status_ = EStatus::PICKUP;

			SpriteAnimation* anim = animations_.at(status_);
			anim->Reset();

			sound->Reset();
			sound->Play();
		}
	}
	break;

	case EStatus::PICKUP:
	{
		SpriteAnimation* anim = animations_.at(status_);
		if (anim->GetTime() >= anim->GetAnimationTime())
		{
			status_ = EStatus::DONE;
		}
	}
	break;
	}

	if (status_ != EStatus::DONE)
	{
		SpriteAnimation* anim = animations_.at(status_);
		anim->Update(deltaSeconds);
	}
}

void Reward::Render()
{
	if (status_ == EStatus::DONE)
	{
		return;
	}

	SpriteAnimation* anim = animations_.at(status_);

	static RenderManager2D::SpriteRenderOptions option;
	RenderManager2D::Get().DrawSprite(atlas_, anim->GetCurrentClip(), bound_.center, bound_.radius * 2.0f, bound_.radius * 2.0f, 0.0f, option);
}

void Reward::Release()
{
	CHECK(bIsInitialized_);

	for (auto& animation : animations_)
	{
		ResourceManager::Get().Destroy(animation.second);
		animation.second = nullptr;
	}

	atlas_ = nullptr;
	camera_ = nullptr;
	player_ = nullptr;

	bIsInitialized_ = false;
}

Reward::Type Reward::GetRandomType()
{
	return static_cast<Reward::Type>(GameMath::GenerateRandomInt(
		static_cast<int32_t>(Type::CHERRY), 
		static_cast<int32_t>(Type::GEM)
	));
}

void Reward::LoadAnimations()
{
	switch (type_)
	{
	case Type::CHERRY:
	{
		std::vector<std::string> cherry = { "Cherry_1", "Cherry_2", "Cherry_3", "Cherry_4", "Cherry_5", "Cherry_6", "Cherry_7", };
		animations_.insert({ EStatus::ACTIVE, ResourceManager::Get().Create<SpriteAnimation>(atlas_, cherry, true, 1.0f) });
	}
	break;
	
	case Type::GEM:
	{
		std::vector<std::string> gem = { "Gem_1", "Gem_2", "Gem_3", "Gem_4", "Gem_5", };
		animations_.insert({ EStatus::ACTIVE, ResourceManager::Get().Create<SpriteAnimation>(atlas_, gem, true, 1.0f) });
	}
	break;
	}
	 
	std::vector<std::string> itemFeedback = { "ItemFeedback_1", "ItemFeedback_2", "ItemFeedback_3", "ItemFeedback_4", };
	animations_.insert({ EStatus::PICKUP, ResourceManager::Get().Create<SpriteAnimation>(atlas_, itemFeedback, false, 0.4f) });
	animations_.insert({ EStatus::DONE, nullptr });
}

bool Reward::GetMovable()
{
	Player::EStatus status = player_->GetStatus();
	return status == Player::EStatus::RUN || status == Player::EStatus::JUMP;
}
