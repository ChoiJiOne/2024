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
	Histroy history;
	history.score = score;
	history.time = GameTimer::GetCurrentSystemTimeAsWString();

	histories_.push_back(history);
}