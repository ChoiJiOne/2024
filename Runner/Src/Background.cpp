#include "Assertion.h"
#include "Atlas2D.h"
#include "Camera2D.h"
#include "EntityManager.h"
#include "RenderManager2D.h"
#include "ResourceManager.h"
#include "IApp.h"

#include "Background.h"
#include "Player.h"

static const float OFFSET = 1.0f;

Background::Background()
	: player_(EntityManager::Get().GetByName<Player>("Player"))
	, camera_(EntityManager::Get().GetByName<Camera2D>("Camera"))
	, bCanMove_(false)
{
	atlas_ = ResourceManager::Get().GetByName<Atlas2D>("Atlas");
	rects_ =
	{ 
		Rect2D(Vec2f(-camera_->GetWidth() * 0.5f + OFFSET, 0.0f), Vec2f(camera_->GetWidth(), camera_->GetHeight())),
		Rect2D(Vec2f(+camera_->GetWidth() * 0.5f - OFFSET, 0.0f), Vec2f(camera_->GetWidth(), camera_->GetHeight())),
	};
	
	bIsInitialized_ = true;
}

Background::~Background()
{
	if (bIsInitialized_)
	{
		Release();
	}
}

void Background::Tick(float deltaSeconds)
{
	if (!bCanMove_)
	{
		bCanMove_ = GetMovable();
		return;
	}

	bCanMove_ = GetMovable();
	if (bCanMove_)
	{
		for (auto& rect : rects_)
		{
			rect.center.x -= deltaSeconds * scrollSpeed_;
		}

		if (!rects_.front().Intersect(camera_->GetCollision()))
		{
			rects_.front() = rects_.back();
			rects_.back().center.x = rects_.front().center.x + rects_.front().size.x - OFFSET;
		}
	}
}

void Background::Render()
{
	RenderManager2D& renderMgr = RenderManager2D::Get();
	static RenderManager2D::SpriteRenderOptions option;

	for (const auto& rect : rects_)
	{
		renderMgr.DrawSprite(atlas_, "Background", rect.center, rect.size.x, rect.size.y, 0.0f, option);
	}
}

void Background::Release()
{
	CHECK(bIsInitialized_);

	camera_ = nullptr;
	atlas_ = nullptr;
	player_ = nullptr;

	bIsInitialized_ = false;
}

bool Background::GetMovable()
{
	Player::EStatus status = player_->GetStatus();
	return status == Player::EStatus::JUMP || status == Player::EStatus::RUN;
}