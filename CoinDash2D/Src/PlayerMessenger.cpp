#include "Assertion.h"
#include "Atlas2D.h"
#include "Collision2D.h"
#include "EntityManager.h"
#include "GameUtils.h"
#include "RenderManager2D.h"
#include "ResourceManager.h"
#include "TTFont.h"

#include "Player.h"
#include "PlayerMessenger.h"

PlayerMessenger::PlayerMessenger()
{
	player_ = EntityManager::Get().GetByName<Player>("Player");
	font_ = ResourceManager::Get().GetByName<TTFont>("Font16");

	bIsInitialized_ = true;
}

PlayerMessenger::~PlayerMessenger()
{
	if (bIsInitialized_)
	{
		Release();
	}
}

void PlayerMessenger::Tick(float deltaSeconds)
{
	if (!bIsDetectMessage_)
	{
		return;
	}

	remainTime_ -= deltaSeconds;
	if (remainTime_ <= 0.0f)
	{
		bIsDetectMessage_ = false;
	}

	CalcMessagePosFromPlayer();

	float alpha = remainTime_ / messageTime_;
	messageColor_.w = alpha;
}

void PlayerMessenger::Render()
{
	if (!bIsDetectMessage_)
	{
		return;
	}

	RenderManager2D::Get().DrawString(font_, message_, messagePos_, messageColor_);
}

void PlayerMessenger::Release()
{
	CHECK(bIsInitialized_);

	font_ = nullptr;
	player_ = nullptr;

	bIsInitialized_ = false;
}

void PlayerMessenger::Send(const std::wstring& message, const Vec4f& color, float time)
{
	message_ = message;
	messageColor_ = color;
	remainTime_ = time;
	messageTime_ = time;

	font_->MeasureText(message_, messageSize_.x, messageSize_.y);

	CalcMessagePosFromPlayer();

	bIsDetectMessage_ = true;
}

void PlayerMessenger::Reset()
{
	remainTime_ = 0.0f;
	messageTime_ = 0.0f;
	bIsDetectMessage_ = false;
}

void PlayerMessenger::CalcMessagePosFromPlayer()
{
	Rect2D* collision = reinterpret_cast<Rect2D*>(player_->GetCollisionBound());
	messagePos_ = collision->center;

	messagePos_.x -= messageSize_.x * 0.5f;
	messagePos_.y += (collision->size.y * 0.5f + messageSize_.y + 15.0f);
}