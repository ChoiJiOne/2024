#include "Assertion.h"
#include "EntityManager.h"
#include "GameUtils.h"
#include "RenderManager2D.h"
#include "ResourceManager.h"
#include "TTFont.h"

#include "GameOver.h"

GameOver::GameOver()
{
	font_ = ResourceManager::Get().GetByName<TTFont>("Font128");
	text_ = L"GAME OVER";

	font_->MeasureText(text_, textSize_.x, textSize_.y);

	textOriginPos_ = Vec2f(0.0f, 50.0f) + Vec2f(-textSize_.x * 0.5f, +textSize_.y * 0.5f);
	textPos_ = textOriginPos_;
	textColor_ = Vec4f(0.0f, 0.0f, 0.0f, 1.0f);

	shadowOffset_ = Vec2f(+3.0f, -3.0f);
	shadowColor_ = Vec4f(0.5f, 0.5f, 0.5f, 0.5f);

	maxTime_ = 1.0f;
	moveLength_ = 50.0f;

	bIsInitialized_ = true;
}

GameOver::~GameOver()
{
	if (bIsInitialized_)
	{
		Release();
	}
}

void GameOver::Tick(float deltaSeconds)
{
	time_ += deltaSeconds;
	if (time_ >= maxTime_)
	{
		time_ -= maxTime_;
	}

	textPos_.y = textOriginPos_.y + (-moveLength_ * time_ * (time_ - maxTime_));
}

void GameOver::Render()
{
	RenderManager2D::Get().DrawString(font_, text_, textPos_ + shadowOffset_, shadowColor_);
	RenderManager2D::Get().DrawString(font_, text_, textPos_, textColor_);
}

void GameOver::Release()
{
	CHECK(bIsInitialized_);

	font_ = nullptr;

	bIsInitialized_ = false;
}
