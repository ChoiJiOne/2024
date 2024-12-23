#include "Assertion.h"
#include "Atlas2D.h"
#include "EntityManager.h"
#include "IApp.h"
#include "RenderManager2D.h"
#include "ResourceManager.h"
#include "Sound.h"

#include "Player.h"
#include "PlayerMessenger.h"
#include "SpriteAnimation.h"

static const float MIN_SPEED = 300.0f;
static const float MAX_SPEED = 600.0f;

Player::Player()
{
	app_ = IApp::Get();
	atlas_ = ResourceManager::Get().GetByName<Atlas2D>("Atlas");

	spriteBound_.size = Vec2f(60.0f, 60.0f);
	spriteBound_.center = Vec2f(-200.0f, -200.0f + spriteBound_.size.y * 0.5f);
	originSpriteBound_ = spriteBound_;

	collisionBound_.radius = 20.0f;
	collisionBound_.center = Vec2f(-200.0f, -200.0f + collisionBound_.radius);
	originCollisionBound_ = collisionBound_;

	speed_ = MIN_SPEED;
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
	if (status_ == EStatus::STOP)
	{
		return;
	}

	if (status_ == EStatus::RUN && app_->GetKeyPress(Key::KEY_SPACE) == Press::PRESSED)
	{
		status_ = EStatus::JUMP;
		animations_.at(status_)->Reset();

		Sound* jumpSound = ResourceManager::Get().GetByName<Sound>("Jump");
		jumpSound->Reset();
		jumpSound->Play();
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
	if (status_ == EStatus::STOP)
	{
		return;
	}

	static RenderManager2D::SpriteRenderOptions option;
	RenderManager2D::Get().DrawSprite(atlas_, animations_.at(status_)->GetCurrentClip(), spriteBound_.center, spriteBound_.size.x, spriteBound_.size.y, 0.0f, option);
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

void Player::PickupCherry()
{
	numPickupCherry_ += 1;
}

void Player::PickupGem()
{
	numPickupGem_ += 1;

	float messageTime = 2.0f;
	std::wstring message = L"Speed Up!";

	speed_ += 10.0f;
	if (speed_ >= MAX_SPEED)
	{
		speed_ = MAX_SPEED;
		message = L"Max Speed!";
	}

	PlayerMessenger* playerMessenger = EntityManager::Get().GetByName<PlayerMessenger>("PlayerMessenger");
	playerMessenger->Send(message, Vec4f(0.0f, 0.0f, 0.0f, 1.0f), messageTime);
}

void Player::Reset()
{
	spriteBound_.size = Vec2f(60.0f, 60.0f);
	spriteBound_.center = Vec2f(-200.0f, -200.0f + spriteBound_.size.y * 0.5f);
	originSpriteBound_ = spriteBound_;

	collisionBound_.radius = 20.0f;
	collisionBound_.center = Vec2f(-200.0f, -200.0f + collisionBound_.radius);
	originCollisionBound_ = collisionBound_;

	speed_ = MIN_SPEED;

	status_ = EStatus::IDLE;

	numPickupCherry_ = 0;
	numPickupGem_ = 0;
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
