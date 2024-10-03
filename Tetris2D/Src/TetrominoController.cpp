#include "Assertion.h"
#include "EntityManager.h"

#include "Board.h"
#include "Tetromino.h"
#include "TetrominoController.h"

TetrominoController::TetrominoController()
{
	bIsInitialized_ = true;
}

TetrominoController::~TetrominoController()
{
	if (bIsInitialized_)
	{
		Release();
	}
}

void TetrominoController::Tick(float deltaSeconds)
{
}

void TetrominoController::Render()
{
}

void TetrominoController::Release()
{
	CHECK(bIsInitialized_);

	board_ = nullptr;

	bIsInitialized_ = false;
}
