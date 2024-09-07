#include "Assertion.h"
#include "Atlas2D.h"
#include "IApp.h"
#include "RenderManager2D.h"
#include "ResourceManager.h"

#include "Player.h"
#include "SpriteAnimation.h"

Player::Player()
{
	app_ = IApp::Get();
	atlas_ = ResourceManager::Get().GetByName<Atlas2D>("Atlas");

	spriteBound_.size = GameMath::Vec2f(60.0f, 60.0f);
	spriteBound_.center = GameMath::Vec2f(-200.0f, -200.0f + spriteBound_.size.y * 0.5f);
	originSpriteBound_ = spriteBound_;

	collisionBound_.radius = 20.0f;
	collisionBound_.center = GameMath::Vec2f(-200.0f, -200.0f + collisionBound_.radius);
	originCollisionBound_ = collisionBound_;

	jumpSpeed_ = 400.0f;

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
	if (status_ == EStatus::IDLE || status_ == EStatus::RUN)
	{
		if (app_->GetKeyPress(Key::KEY_SPACE) == Press::PRESSED)
		{
			status_ = EStatus::JUMP;
			animations_.at(status_)->Reset();
		}
	}

	if (status_ == EStatus::JUMP)
	{
		float time = animations_.at(status_)->GetTime();
		float animationTime = animations_.at(status_)->GetAnimationTime();

		if (time >= animationTime)
		{
			status_ = EStatus::RUN;
		}

		collisionBound_.center.y = originCollisionBound_.center.y + (-jumpSpeed_ * time * (time - animationTime));
		spriteBound_.center.y = originSpriteBound_.center.y + (-jumpSpeed_ * time * (time - animationTime));
	}

	animations_.at(status_)->Update(deltaSeconds);
}

void Player::Render()
{
	RenderManager2D::Get().DrawSprite(atlas_, animations_.at(status_)->GetCurrentClip(), spriteBound_.center, spriteBound_.size.x, spriteBound_.size.y);
}

void Player::Release()
{
	CHECK(bIsInitialized_);

	for (auto& animation : animations_)
	{
		ResourceManager::Get().Destroy(animation.second);
		animation.second = nullptr;
	}

	atlas_ = nullptr;

	bIsInitialized_ = false;
}

void Player::PickupCherry(int32_t numCherry)
{
	numPickupCherry_ += numCherry;
}

void Player::PickupGem(int32_t numGem)
{
	numPickupGem_ += numGem;
}

void Player::LoadAnimations()
{
	std::vector<std::string> hurt = { "Hurt_1", "Hurt_2" };
	std::vector<std::string> idle = { "Idle_1", "Idle_2", "Idle_3", "Idle_4", };
	std::vector<std::string> jump = { "Jump_1", "Jump_2"};
	std::vector<std::string> run = { "Run_1", "Run_2", "Run_3", "Run_4" , "Run_5" ,"Run_6" };

	animations_.insert({ EStatus::HURT, ResourceManager::Get().Create<SpriteAnimation>(atlas_, hurt, true, 0.5f)  });
	animations_.insert({ EStatus::IDLE, ResourceManager::Get().Create<SpriteAnimation>(atlas_, idle, true, 0.5f)  });
	animations_.insert({ EStatus::JUMP, ResourceManager::Get().Create<SpriteAnimation>(atlas_, jump, false, 1.0f) });
	animations_.insert({ EStatus::RUN,  ResourceManager::Get().Create<SpriteAnimation>(atlas_, run, true, 0.5f)   });
}
