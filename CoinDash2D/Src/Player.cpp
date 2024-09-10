#include "Assertion.h"
#include "Atlas2D.h"
#include "IApp.h"
#include "RenderManager2D.h"
#include "ResourceManager.h"
#include "SpriteAnim2D.h"

#include "Player.h"

Player::Player()
{
	app_ = IApp::Get();

	Atlas2D* atlas = ResourceManager::Get().GetByName<Atlas2D>("Atlas");

	std::vector<std::string> idleClips = { "Idle_1", "Idle_2", "Idle_3", "Idle_4", };
	anims_.insert({ Status::IDLE, ResourceManager::Get().Create<SpriteAnim2D>(atlas, idleClips, true, 0.7f) });

	std::vector<std::string> runClips = { "Run_1", "Run_2", "Run_3", "Run_4", "Run_5", "Run_6", };
	anims_.insert({ Status::RUN, ResourceManager::Get().Create<SpriteAnim2D>(atlas, runClips, true, 0.5f) });

	std::vector<std::string> hurtClip = { "Hurt_1", "Hurt_2", };
	anims_.insert({ Status::HURT, ResourceManager::Get().Create<SpriteAnim2D>(atlas, hurtClip, true, 0.5f) });

	spriteBound_.center = GameMath::Vec2f();
	spriteBound_.size = GameMath::Vec2f(50.0f, 50.0f);

	collisionBound_.center = spriteBound_.center + GameMath::Vec2f(0.0f, -5.0f);
	collisionBound_.size = GameMath::Vec2f(30.0f, 40.0f);

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
	static std::map<Key, GameMath::Vec2f> keyDirections =
	{
		{ Key::KEY_RIGHT, GameMath::Vec2f(+1.0f, +0.0f) },
		{ Key::KEY_UP,    GameMath::Vec2f(+0.0f, +1.0f) },
		{ Key::KEY_LEFT,  GameMath::Vec2f(-1.0f, +0.0f) },
		{ Key::KEY_DOWN,  GameMath::Vec2f(+0.0f, -1.0f) },
	};

	bool bIsPress = false;

	direction_ = GameMath::Vec2f(0.0f, 0.0f);
	for (const auto& keyDirection : keyDirections)
	{
		if (app_->GetKeyPress(keyDirection.first) == Press::HELD)
		{
			bIsPress = true;
			direction_ += keyDirection.second;
		}
	}
	status_ = (bIsPress) ? Status::RUN : Status::IDLE;

	if (!GameMath::NearZero(GameMath::Vec2f::LengthSq(direction_)))
	{
		direction_ = GameMath::Vec2f::Normalize(direction_);

		spriteBound_.center.x += direction_.x * deltaSeconds * speed_;
		spriteBound_.center.y += direction_.y * deltaSeconds * speed_;
		collisionBound_.center = spriteBound_.center + GameMath::Vec2f(0.0f, -5.0f);
	}

	anims_.at(status_)->Update(deltaSeconds);
}

void Player::Render()
{
	SpriteAnim2D* anim = anims_.at(status_);
	RenderManager2D::Get().DrawSprite(anim->GetAtlas(), anim->GetCurrentClip(), spriteBound_.center, spriteBound_.size.x, spriteBound_.size.y);
	RenderManager2D::Get().DrawRectWireframe(collisionBound_.center, collisionBound_.size.x, collisionBound_.size.y, GameMath::Vec4f(1.0f, 0.0f, 0.0f, 1.0f));
}

void Player::Release()
{
	CHECK(bIsInitialized_);

	for (auto& anim : anims_)
	{
		ResourceManager::Get().Destroy(anim.second);
		anim.second = nullptr;
	}

	app_ = nullptr;

	bIsInitialized_ = false;
}
