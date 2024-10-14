#include "Assertion.h"
#include "Atlas2D.h"
#include "EntityManager.h"
#include "RenderManager2D.h"
#include "ResourceManager.h"
#include "Sound.h"

#include "Cactus.h"
#include "GameApp.h"
#include "Player.h"

Cactus::Cactus(const Rect2D& bound)
	: spriteBound_(bound)
{
	player_ = EntityManager::Get().GetByName<Player>("Player");
	atlas_ = ResourceManager::Get().GetByName<Atlas2D>("Atlas");
	hitSound_ = ResourceManager::Get().GetByName<Sound>("Hit");

	collisionBound_ = spriteBound_;
	collisionBound_.size.x -= 10.0f;

	bIsInitialized_ = true;
}

Cactus::~Cactus()
{
	if (bIsInitialized_)
	{
		Release();
	}
}

void Cactus::Tick(float deltaSeconds)
{
	if (collisionBound_.Intersect(player_->GetCollisionBound()))
	{
		hitSound_->Reset();
		hitSound_->Play();

		GameApp* app = reinterpret_cast<GameApp*>(IApp::Get());
		GameApp::Status status = app->GetStatus();
		if (status == GameApp::Status::PLAY)
		{
			app->SetStatus(GameApp::Status::DONE);
			player_->SetStatus(Player::Status::HURT);
		}
	}
}

void Cactus::Render()
{
	static RenderManager2D::SpriteRenderOptions option;
	RenderManager2D::Get().DrawSprite(atlas_, "Cactus", spriteBound_.center, spriteBound_.size.x, spriteBound_.size.y, 0.0f, option);
}

void Cactus::Release()
{
	CHECK(bIsInitialized_);

	hitSound_ = nullptr;
	player_ = nullptr;
	atlas_ = nullptr;

	bIsInitialized_ = false;
}
