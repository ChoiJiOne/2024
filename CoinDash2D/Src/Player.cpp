#include "Assertion.h"
#include "Atlas2D.h"
#include "IApp.h"
#include "RenderManager2D.h"
#include "ResourceManager.h"
#include "SpriteAnim2D.h"

#include "Player.h"

Player::Player()
{
	Atlas2D* atlas = ResourceManager::Get().GetByName<Atlas2D>("Atlas");

	std::vector<std::string> idleClips = { "Idle_1", "Idle_2", "Idle_3", "Idle_4", };
	anims_.insert({ Status::IDLE, ResourceManager::Get().Create<SpriteAnim2D>(atlas, idleClips, true, 0.7f) });

	std::vector<std::string> runClips = { "Run_1", "Run_2", "Run_3", "Run_4", "Run_5", "Run_6", };
	anims_.insert({ Status::RUN, ResourceManager::Get().Create<SpriteAnim2D>(atlas, runClips, true, 0.5f) });

	std::vector<std::string> hurtClip = { "Hurt_1", "Hurt_2", };
	anims_.insert({ Status::HURT, ResourceManager::Get().Create<SpriteAnim2D>(atlas, hurtClip, true, 0.5f) });
	
	bound_.center = GameMath::Vec2f();
	bound_.size = GameMath::Vec2f(50.0f, 50.0f);

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
	anims_.at(status_)->Update(deltaSeconds);
}

void Player::Render()
{
	SpriteAnim2D* anim = anims_.at(status_);
	RenderManager2D::Get().DrawSprite(anim->GetAtlas(), anim->GetCurrentClip(), bound_.center, bound_.size.x, bound_.size.y);
}

void Player::Release()
{
	CHECK(bIsInitialized_);

	for (auto& anim : anims_)
	{
		ResourceManager::Get().Destroy(anim.second);
		anim.second = nullptr;
	}

	bIsInitialized_ = false;
}
