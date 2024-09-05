#include "Assertion.h"
#include "Atlas2D.h"
#include "RenderManager2D.h"
#include "ResourceManager.h"

#include "Player.h"
#include "SpriteAnimation.h"

Player::Player()
{
	atlas_ = ResourceManager::Get().GetByName<Atlas2D>("Atlas");

	spriteBound_.size = GameMath::Vec2f(60.0f, 60.0f);
	spriteBound_.center = GameMath::Vec2f(-200.0f, -200.0f + spriteBound_.size.y * 0.5f);

	collisionBound_.radius = 20.0f;
	collisionBound_.center = GameMath::Vec2f(-200.0f, -200.0f + collisionBound_.radius);

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
	animations_.at(status_)->Update(deltaSeconds);
}

void Player::Render()
{
	RenderManager2D::Get().DrawSprite(atlas_, animations_.at(status_)->GetCurrentClip(), spriteBound_.center, spriteBound_.size.x, spriteBound_.size.y);
	RenderManager2D::Get().DrawCircleWireframe(collisionBound_.center, collisionBound_.radius, GameMath::Vec4f(1.0f, 0.0f, 0.0f, 1.0f));
}

void Player::Release()
{
	CHECK(bIsInitialized_);

	atlas_ = nullptr;

	bIsInitialized_ = false;
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
