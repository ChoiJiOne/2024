#include "Assertion.h"
#include "Atlas2D.h"
#include "EntityManager.h"
#include "IApp.h"
#include "RenderManager2D.h"
#include "ResourceManager.h"
#include "SpriteAnim2D.h"
#include "Sound.h"

#include "Player.h"
#include "PlayerMessenger.h"

static const std::map<Key, Vec2f> KEY_DIRECTIONS =
{
	{ Key::KEY_RIGHT, Vec2f(+1.0f, +0.0f) },
	{ Key::KEY_UP,    Vec2f(+0.0f, +1.0f) },
	{ Key::KEY_LEFT,  Vec2f(-1.0f, +0.0f) },
	{ Key::KEY_DOWN,  Vec2f(+0.0f, -1.0f) },
};

static RenderManager2D::SpriteRenderOptions option_;

Player::Player()
{
	app_ = IApp::Get();
	camera_ = EntityManager::Get().GetByName<Camera2D>("Camera"); 
	coinSound_ = ResourceManager::Get().GetByName<Sound>("Coin");
	powerUpSound_ = ResourceManager::Get().GetByName<Sound>("PowerUp");

	Atlas2D* atlas = ResourceManager::Get().GetByName<Atlas2D>("Atlas");

	std::vector<std::string> idleClips = { "Idle_1", "Idle_2", "Idle_3", "Idle_4", };
	anims_.insert({ Status::IDLE, ResourceManager::Get().Create<SpriteAnim2D>(atlas, idleClips, true, 0.7f) });

	std::vector<std::string> runClips = { "Run_1", "Run_2", "Run_3", "Run_4", "Run_5", "Run_6", };
	anims_.insert({ Status::RUN, ResourceManager::Get().Create<SpriteAnim2D>(atlas, runClips, true, 0.5f) });

	std::vector<std::string> hurtClip = { "Hurt_1", "Hurt_2", };
	anims_.insert({ Status::HURT, ResourceManager::Get().Create<SpriteAnim2D>(atlas, hurtClip, true, 0.5f) });

	center_.center = Vec2f();

	spriteBound_.center = center_.center;
	spriteBound_.size = Vec2f(50.0f, 50.0f);

	collisionBound_.center = center_.center + Vec2f(0.0f, -7.0f);
	collisionBound_.size = Vec2f(30.0f, 36.0f);

	speed_ = normalSpeed_;

	powerUpBar_ = Rect2D(Vec2f(0.0f, 0.0f), Vec2f(30.0f, 5.0f));
	powerUpBarColor_ = Vec4f(0.0f, 0.0f, 0.0f, 1.0f);
	remainBarColor_ = Vec4f(1.0f, 0.0f, 0.0f, 1.0f);

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
	if (status_ == Status::HURT)
	{
		anims_.at(status_)->Update(deltaSeconds);
		return;
	}

	Move(deltaSeconds);
	UpdatePowerUpBar(deltaSeconds);
	anims_.at(status_)->Update(deltaSeconds);
}

void Player::Render()
{
	SpriteAnim2D* anim = anims_.at(status_);

	option_.bIsFlipH = bIsFlipH_;
	RenderManager2D::Get().DrawSprite(anim->GetAtlas(), anim->GetCurrentClip(), spriteBound_.center, spriteBound_.size.x, spriteBound_.size.y, 0.0f, option_);
	
	RenderManager2D::Get().DrawRect(powerUpBar_.center, powerUpBar_.size.x, powerUpBar_.size.y, powerUpBarColor_, 0.0f);
	RenderManager2D::Get().DrawRect(remainBar_.center, remainBar_.size.x, remainBar_.size.y, remainBarColor_, 0.0f);
}

void Player::Release()
{
	CHECK(bIsInitialized_);

	for (auto& anim : anims_)
	{
		ResourceManager::Get().Destroy(anim.second);
		anim.second = nullptr;
	}

	powerUpSound_ = nullptr;
	coinSound_ = nullptr;
	app_ = nullptr;

	bIsInitialized_ = false;
}

void Player::PickupCoin()
{
	numCoin_++;

	PlayerMessenger* messenger = EntityManager::Get().GetByName<PlayerMessenger>("PlayerMessenger");
	messenger->Send(L"+1", messageColor_, 1.0f);

	coinSound_->Reset();
	coinSound_->Play();
}

void Player::PickupPowerUpCoin()
{
	bIsPowerUp_ = true;
	powerUpTime_ = maxPowerUpTime_;
	speed_ = maxPowerUpSpeed_;

	PlayerMessenger* messenger = EntityManager::Get().GetByName<PlayerMessenger>("PlayerMessenger");
	messenger->Send(L"PowerUp!", messageColor_, 2.0f);

	powerUpSound_->Reset();
	powerUpSound_->Play();
}

void Player::Reset()
{
	status_ = Status::IDLE;

	center_.center = Vec2f();
	spriteBound_.center = center_.center;
	spriteBound_.size = Vec2f(50.0f, 50.0f);
	collisionBound_.center = center_.center + Vec2f(0.0f, -7.0f);
	collisionBound_.size = Vec2f(30.0f, 36.0f);

	speed_ = normalSpeed_;

	bIsFlipH_ = false;
	numCoin_ = 0;
	bIsPowerUp_ = false;
	powerUpTime_ = 0.0f;
}

void Player::Move(float deltaSeconds)
{
	bool bIsPress = false;
	for (const auto& keyDirection : KEY_DIRECTIONS)
	{
		if (app_->GetKeyPress(keyDirection.first) == Press::HELD)
		{
			bIsPress = true;
			direction_ += keyDirection.second;
		}
	}
	status_ = (bIsPress) ? Status::RUN : Status::IDLE;
	bIsFlipH_ = (direction_.x < 0.0f) ? true : false;

	if (bIsPress && !GameMath::NearZero(Vec2f::LengthSq(direction_)))
	{
		direction_ = Vec2f::Normalize(direction_);

		Vec2f center = center_.center;
		center_.center += direction_ * deltaSeconds * speed_;

		if (center_.Intersect(camera_->GetCollision()))
		{
			spriteBound_.center = center_.center;
			collisionBound_.center = center_.center + Vec2f(0.0f, -7.0f);
		}
		else
		{
			center_.center = center;
		}
	}
}

void Player::UpdatePowerUpBar(float deltaSeconds)
{
	if (bIsPowerUp_)
	{
		powerUpTime_ -= deltaSeconds;

		if (powerUpTime_ <= 0.0f)
		{
			powerUpTime_ = 0.0f;
			bIsPowerUp_ = false;
			speed_ = normalSpeed_;
		}
	}

	powerUpBar_.center = collisionBound_.center;
	powerUpBar_.center.y += collisionBound_.size.y * 0.5f + 5.0f;

	remainBar_.size = powerUpBar_.size;
	remainBar_.size.x *= (powerUpTime_ / maxPowerUpTime_);

	remainBar_.center = powerUpBar_.center + Vec2f(-powerUpBar_.size.x * 0.5f, +powerUpBar_.size.y * 0.5f);
	remainBar_.center += Vec2f(+remainBar_.size.x * 0.5f, -remainBar_.size.y * 0.5f);
}
