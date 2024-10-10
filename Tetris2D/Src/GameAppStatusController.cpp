#include "Assertion.h"

#include "GameApp.h"
#include "GameAppStatusController.h"

GameAppStatusController::GameAppStatusController()
{
	app_ = reinterpret_cast<GameApp*>(GameApp::Get());
	bIsInitialized_ = true;
}

GameAppStatusController::~GameAppStatusController()
{
	if (bIsInitialized_)
	{
		Release();
	}
}

void GameAppStatusController::Tick(float deltaSeconds)
{
}

void GameAppStatusController::Release()
{
	CHECK(bIsInitialized_);

	app_ = nullptr;

	bIsInitialized_ = false;
}
