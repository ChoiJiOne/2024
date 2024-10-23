#include "Assertion.h"
#include "EntityManager.h"
#include "GameUtils.h"
#include "RenderManager2D.h"
#include "ResourceManager.h"
#include "TTFont.h"

#include "GameHistoryTracker.h"
#include "HighScoreViewer.h"

HighScoreViewer::HighScoreViewer()
{
	font_ = ResourceManager::GetRef().GetByName<TTFont>("Font64");
	gameHistoryTracker_ = EntityManager::GetRef().GetByName<GameHistoryTracker>("GameHistoryTracker");
	scoreTextPos_ = Vec2f(-160.0f, 120.0f);
	scoreTextColor_ = Vec4f(1.0f, 1.0f, 1.0f, 1.0f);
	highScoreTextPos_ = Vec2f(-160.0f, 40.0f);

	background_ = Rect2D(Vec2f(0.0f, 50.0f), Vec2f(440.0f, 200.0f));
	backgroundOutlineColor_ = Vec4f(0.5f, 0.5f, 0.5f, 0.5f);
	backgroundColor_ = Vec4f(0.0f, 0.0f, 0.0f, 0.8f);
	backgroundSide_ = 10.0f;

	bIsInitialized_ = true;
}

HighScoreViewer::~HighScoreViewer()
{
	if (bIsInitialized_)
	{
		Release();
	}
}

void HighScoreViewer::Tick(float deltaSeconds)
{
}

void HighScoreViewer::Render()
{
	RenderManager2D& renderMgr = RenderManager2D::GetRef();

	renderMgr.DrawRoundRectWireframe(background_.center, background_.size.x, background_.size.y, backgroundSide_, backgroundOutlineColor_, 0.0f);
	renderMgr.DrawRoundRect(background_.center, background_.size.x, background_.size.y, backgroundSide_, backgroundColor_, 0.0f);
	renderMgr.DrawString(font_, scoreText_, scoreTextPos_, scoreTextColor_);
	renderMgr.DrawString(font_, highScoreText_, highScoreTextPos_, highScoreTextColor_);
}

void HighScoreViewer::Release()
{
	CHECK(bIsInitialized_);

	bIsInitialized_ = false;
}

void HighScoreViewer::UpdateRecentState()
{
	int32_t score = gameHistoryTracker_->GetRecent().score;
	int32_t highScore = gameHistoryTracker_->GetHigh().score;

	scoreText_ = GameUtils::PrintF(L"SCORE: %d", score);
	highScoreText_ = GameUtils::PrintF(L"HIGH: %d", highScore);

	if (gameHistoryTracker_->IsHighScoreBroken())
	{
		highScoreTextColor_ = Vec4f(1.0f, 0.3f, 0.3f, 1.0f);
	}
	else
	{
		highScoreTextColor_ = Vec4f(1.0f, 1.0f, 1.0f, 1.0f);
	}
}
