#include "Assertion.h"
#include "EntityManager.h"
#include "GameUtils.h"
#include "GameTimer.h"
#include "RenderManager2D.h"

#include "GameHistoryTracker.h"

GameHistoryTracker::GameHistoryTracker()
{
	bIsInitialized_ = true;
}

GameHistoryTracker::~GameHistoryTracker()
{
	if (bIsInitialized_)
	{
		Release();
	}
}

void GameHistoryTracker::Tick(float deltaSeconds)
{
}

void GameHistoryTracker::Release()
{
	CHECK(bIsInitialized_);

	bIsInitialized_ = false;
}

void GameHistoryTracker::AddScore(int32_t score)
{
	History newHistory;
	newHistory.score = score;
	newHistory.time = GameTimer::GetCurrentSystemTimeAsWString();

	recentScore_ = score;

	if (histories_.empty())
	{
		highScore_ = score;
		bIsHighScoreBroken_ = true;
	}
	else
	{
		bIsHighScoreBroken_ = false;
		for (const auto& history : histories_)
		{
			if (score > history.score)
			{
				highScore_ = score;
				bIsHighScoreBroken_ = true;
				break;
			}
		}
	}
	
	histories_.push_back(newHistory);
}