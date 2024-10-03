#include "Assertion.h"
#include "EntityManager.h"

#include "Board.h"
#include "Tetromino.h"
#include "TetrominoController.h"

TetrominoController::TetrominoController()
{
	board_ = EntityManager::Get().GetByName<Board>("Board");

	startPos_ = board_->GetStartPos();
	waitPos_ = Vec2f(150.0f, 100.0f);

	currentTetromino_ = Tetromino::CreateRandom(startPos_, 27.0f, 30.0f, Vec4f(1.0f, 1.0f, 1.0f, 1.0f));
	nextTetromino_ = Tetromino::CreateRandom(waitPos_, 27.0f, 30.0f, Vec4f(1.0f, 1.0f, 1.0f, 1.0f));

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
	currentTetromino_->Tick(deltaSeconds);
	nextTetromino_->Tick(deltaSeconds);
}

void TetrominoController::Render()
{
	currentTetromino_->Render();
	nextTetromino_->Render();
}

void TetrominoController::Release()
{
	CHECK(bIsInitialized_);

	if (nextTetromino_)
	{
		EntityManager::Get().Destroy(nextTetromino_);
		nextTetromino_ = nullptr;
	}

	if (currentTetromino_)
	{
		EntityManager::Get().Destroy(currentTetromino_);
		currentTetromino_ = nullptr;
	}

	board_ = nullptr;

	bIsInitialized_ = false;
}
