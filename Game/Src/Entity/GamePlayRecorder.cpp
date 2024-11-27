#include "Entity/GamePlayRecorder.h"
#include "Utils/Assertion.h"

GamePlayRecorder::GamePlayRecorder()
{
	bIsInitialized_ = true;
}

GamePlayRecorder::~GamePlayRecorder()
{
	if (bIsInitialized_)
	{
		Release();
	}
}

void GamePlayRecorder::Tick(float deltaSeconds)
{
	playTime_ += deltaSeconds;


}

void GamePlayRecorder::Release()
{
	CHECK(bIsInitialized_);

	bIsInitialized_ = false;
}