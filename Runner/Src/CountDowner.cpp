#include "Assertion.h"
#include "Atlas2D.h"
#include "EntityManager.h"
#include "GameUtils.h"
#include "RenderManager2D.h"
#include "ResourceManager.h"
#include "TTFont.h"

#include "CountDowner.h"
#include "Player.h"

CountDowner::CountDowner() 
	: player_(EntityManager::Get().GetByName<Player>("Player"))
{
	font_ = ResourceManager::Get().GetByName<TTFont>("Font64");

	time_ = 4.0f;
	messageCenter_ = Vec2f(0.0f, 0.0f);
	messageColor_ = Vec4f(0.0f, 0.0f, 0.0f, 1.0f);

	bIsInitialized_ = true;
}

CountDowner::~CountDowner()
{
	if (bIsInitialized_)
	{
		Release();
	}
}

void CountDowner::Tick(float deltaSeconds)
{
	if (!bIsStart_)
	{
		return;
	}

	time_ -= deltaSeconds;
	if (time_ <= 0.0f)
	{
		bIsStart_ = false;
		player_->SetStatus(Player::EStatus::RUN);
		return;
	}

	if (remainTime_ != static_cast<int32_t>(time_))
	{
		remainTime_ = static_cast<int32_t>(time_);
		message_ = GameUtils::PrintF(L"%d", remainTime_);

		Vec2f size;
		font_->MeasureText(message_, size.x, size.y);

		messagePos_ = messageCenter_ + Vec2f(-size.x * 0.5f, +size.y * 0.5f);
	}

	float alpha = time_ - static_cast<float>(remainTime_);
	messageColor_.w = alpha;
}

void CountDowner::Render()
{
	if (!bIsStart_)
	{
		return;
	}

	RenderManager2D::Get().DrawString(font_, message_, messagePos_, messageColor_);
}

void CountDowner::Release()
{
	CHECK(bIsInitialized_);

	player_ = nullptr;

	bIsInitialized_ = false;
}

void CountDowner::Start()
{
	bIsStart_ = true;
	time_ = 4.0f;
	remainTime_ = static_cast<int32_t>(time_);

	message_ = GameUtils::PrintF(L"%d", remainTime_);

	Vec2f size;
	font_->MeasureText(message_, size.x, size.y);

	messagePos_ = messageCenter_ + Vec2f(-size.x * 0.5f, +size.y * 0.5f);
}