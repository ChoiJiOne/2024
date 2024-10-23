#include "Assertion.h"
#include "EntityManager.h"
#include "GameUtils.h"
#include "RenderManager2D.h"
#include "ResourceManager.h"
#include "TTFont.h"

#include "GameHistoryTracker.h"
#include "HistoryViewer.h"

HistoryViewer::HistoryViewer()
{
	font_ = ResourceManager::GetRef().GetByName<TTFont>("Font24");
	gameHistoryTracker_ = EntityManager::GetRef().GetByName<GameHistoryTracker>("GameHistoryTracker");

	background_ = Rect2D(Vec2f(0.0f, 80.0f), Vec2f(400.0f, 480.0f));
	backgroundColor_ = Vec4f(0.0f, 0.0f, 0.0f, 0.7f);
	backgroundSide_ = 10.0f;

	startTimeTextPos_ = Vec2f(-190.0f, 250.0f);
	startScoreTextPos_ = Vec2f(50.0f, 250.0f);
	historyTextColor_ = Vec4f(1.0f, 1.0f, 1.0f, 1.0f);
	historyTextStride_ = 30.0f;

	bestTimeTextPos_ = Vec2f(-190.0f, -120.0f);
	bestScoreTextPos_ = Vec2f(50.0f, -120.0f);
	bestTextColor_ = Vec4f(1.0f, 0.3f, 0.3f, 1.0f);

	bIsInitialized_ = true;
}

HistoryViewer::~HistoryViewer()
{
	if (bIsInitialized_)
	{
		Release();
	}
}

void HistoryViewer::Tick(float deltaSeconds)
{
}

void HistoryViewer::Render()
{
	RenderManager2D& renderMgr = RenderManager2D::GetRef();

	renderMgr.DrawRoundRect(background_.center, background_.size.x, background_.size.y, backgroundSide_, backgroundColor_, 0.0f);

	Vec2f timeTextPos = startTimeTextPos_;
	Vec2f scoreTextPos = startScoreTextPos_;
	for (int32_t index = 0; index < currentHistoryTextSize_; ++index)
	{
		renderMgr.DrawString(font_, timeHistoryTexts_[index], timeTextPos, historyTextColor_);
		renderMgr.DrawString(font_, scoreHistoryTexts_[index], scoreTextPos, historyTextColor_);
		timeTextPos.y -= historyTextStride_;
		scoreTextPos.y -= historyTextStride_;
	}

	renderMgr.DrawString(font_, bestTimeText_, bestTimeTextPos_, bestTextColor_);
	renderMgr.DrawString(font_, bestScoreText_, bestScoreTextPos_, bestTextColor_);
}

void HistoryViewer::Release()
{
	CHECK(bIsInitialized_);

	gameHistoryTracker_ = nullptr;
	font_ = nullptr;

	bIsInitialized_ = false;
}

void HistoryViewer::UpdateRecentHistory()
{
	const std::list<GameHistoryTracker::History>& histories = gameHistoryTracker_->GetHistories();
	if (histories.empty())
	{
		return;
	}

	currentHistoryTextSize_ = 0;
	for (auto& rit = histories.rbegin(); rit != histories.rend(); ++rit)
	{
		const GameHistoryTracker::History& recent = *rit;

		timeHistoryTexts_[currentHistoryTextSize_] = GameUtils::PrintF(L"TIME: %s", recent.time.c_str());
		scoreHistoryTexts_[currentHistoryTextSize_] = GameUtils::PrintF(L"SCORE: %d", recent.score);
		currentHistoryTextSize_++;

		if (currentHistoryTextSize_ >= MAX_VIEW_HISTORY)
		{
			break;
		}
	}

	const GameHistoryTracker::History& high = gameHistoryTracker_->GetHigh();
	bestTimeText_ = GameUtils::PrintF(L"TIME: %s", high.time.c_str());
	bestScoreText_ = GameUtils::PrintF(L"SCORE: %d", high.score);
}
