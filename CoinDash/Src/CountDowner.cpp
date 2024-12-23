#include "Assertion.h"
#include "Atlas2D.h"
#include "EntityManager.h"
#include "GameUtils.h"
#include "IApp.h"
#include "RenderManager2D.h"
#include "ResourceManager.h"
#include "TTFont.h"

#include "CountDowner.h"
#include "GameApp.h"
#include "Player.h"

CountDowner::CountDowner()
{
	player_ = EntityManager::Get().GetByName<Player>("Player");
	font_ = ResourceManager::Get().GetByName<TTFont>("Font64");

	time_ = 31.0f;
	textColor_ = Vec4f(1.0f, 1.0f, 1.0f, 1.0f);
	textShadowColor_ = Vec4f(0.5f, 0.5f, 0.5f, 0.5f);

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
	Player::Status status = player_->GetStatus();
	if (status == Player::Status::HURT)
	{
		return;
	}

	time_ -= deltaSeconds;
	if (time_ <= 0.0f)
	{
		time_ = 0.0f;

		GameApp* app = reinterpret_cast<GameApp*>(IApp::Get());
		GameApp::Status status = app->GetStatus();
		if (status == GameApp::Status::PLAY)
		{
			app->SetStatus(GameApp::Status::DONE);
			player_->SetStatus(Player::Status::HURT);
		}
		return;
	}

	if (remainTime_ != static_cast<int32_t>(time_))
	{
		remainTime_ = static_cast<int32_t>(time_);
		text_ = GameUtils::PrintF(L"%d", remainTime_);

		textPos_ = Vec2f(240.0f, 350.0f);

		Vec2f size;
		font_->MeasureText(text_, size.x, size.y);

		textPos_.x -= (size.x + 5.0f);
		textShadowPos_ = textPos_ + Vec2f(+3.0f, -3.0f);
	}

	textColor_ = (time_ <= 6.0f) ? Vec4f(1.0f, 0.3f, 0.3f, 1.0f) : Vec4f(1.0f, 1.0f, 1.0f, 1.0f);
}

void CountDowner::Render()
{
	RenderManager2D::Get().DrawString(font_, text_, textShadowPos_, textShadowColor_);
	RenderManager2D::Get().DrawString(font_, text_, textPos_, textColor_);
}

void CountDowner::Release()
{
	CHECK(bIsInitialized_);

	font_ = nullptr;
	player_ = nullptr;

	bIsInitialized_ = false;
}

void CountDowner::Reset()
{
	time_ = 31.0f;
	remainTime_ = 0;
}
