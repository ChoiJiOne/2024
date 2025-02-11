#include "Assertion.h"
#include "EntityManager.h"

#include "Board.h"
#include "Tetromino.h"
#include "TetrominoController.h"

TetrominoController::TetrominoController()
{
	board_ = EntityManager::GetRef().GetByName<Board>("Board");

	startPos_ = board_->GetStartPos();
	waitPos_ = Vec2f(150.0f, 100.0f);
	blockSize_ = 27.0f;
	blockStride_ = 30.0f;

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
	switch (status_)
	{
	case Status::ACTIVE:
		UpdateActiveStatus(deltaSeconds);
		break;

	case Status::DEACTIVE:
		UpdateDeactiveStatus(deltaSeconds);
		break;
	
	case Status::DONE:
		// Nothing...
		break;
	}
}

void TetrominoController::Render()
{
	if (currentTetromino_)
	{
		currentTetromino_->Render();
	}

	if (nextTetromino_)
	{
		nextTetromino_->Render();
	}
}

void TetrominoController::Release()
{
	CHECK(bIsInitialized_);

	if (nextTetromino_)
	{
		EntityManager::GetRef().Destroy(nextTetromino_);
		nextTetromino_ = nullptr;
	}

	if (currentTetromino_)
	{
		EntityManager::GetRef().Destroy(currentTetromino_);
		currentTetromino_ = nullptr;
	}

	board_ = nullptr;

	bIsInitialized_ = false;
}

void TetrominoController::Reset()
{
	if (nextTetromino_)
	{
		EntityManager::GetRef().Destroy(nextTetromino_);
		nextTetromino_ = nullptr;
	}

	if (currentTetromino_)
	{
		EntityManager::GetRef().Destroy(currentTetromino_);
		currentTetromino_ = nullptr;
	}

	currentTetromino_ = CreateRandomTetromino(startPos_, blockSize_, blockStride_);
	currentTetromino_->status_ = Tetromino::Status::ACTIVE; /** 여기만 예외적으로 접근! */

	nextTetromino_ = CreateRandomTetromino(waitPos_, blockSize_, blockStride_);

	status_ = Status::ACTIVE;
}

Tetromino* TetrominoController::CreateRandomTetromino(const Vec2f& startPos, float blockSize, float stride)
{
	static const std::array<Tetromino::Type, 7> types = 
	{ 
		Tetromino::Type::I,
		Tetromino::Type::O,
		Tetromino::Type::T,
		Tetromino::Type::J,
		Tetromino::Type::L,
		Tetromino::Type::S,
		Tetromino::Type::Z
	};
	uint32_t randomTypeIndex = GameMath::GenerateRandomInt(0, types.size() - 1);

	static const std::array<Vec4f, 6> colors =
	{
		Vec4f(1.0f, 0.5f, 0.5f, 1.0f),
		Vec4f(0.5f, 1.0f, 0.5f, 1.0f),
		Vec4f(0.5f, 0.5f, 1.0f, 1.0f),
		Vec4f(1.0f, 1.0f, 0.5f, 1.0f),
		Vec4f(1.0f, 0.5f, 1.0f, 1.0f),
		Vec4f(0.5f, 1.0f, 1.0f, 1.0f),
	};
	uint32_t randomColorIndex = GameMath::GenerateRandomInt(0, colors.size() - 1);

	return EntityManager::GetRef().Create<Tetromino>(startPos, blockSize, stride, types[randomTypeIndex], colors[randomColorIndex]);
}

void TetrominoController::UpdateActiveStatus(float deltaSeconds)
{
	currentTetromino_->Tick(deltaSeconds);
	nextTetromino_->Tick(deltaSeconds);

	Tetromino::Status status = currentTetromino_->GetStatus();
	if (status == Tetromino::Status::DONE)
	{
		const std::array<Block, Tetromino::NUM_BLOCKS>& currentBlocks = currentTetromino_->GetBlocks();
		board_->DeployBlocks(currentBlocks.data(), currentBlocks.size());

		EntityManager::GetRef().Destroy(currentTetromino_);
		currentTetromino_ = nullptr;

		status_ = Status::DEACTIVE;
	}
}

void TetrominoController::UpdateDeactiveStatus(float deltaSeconds)
{
	Board::Status status = board_->GetStatus();
	if (status != Board::Status::WAIT)
	{
		return;
	}

	currentTetromino_ = nextTetromino_;
	currentTetromino_->GotoPosition(startPos_);

	const std::array<Block, Tetromino::NUM_BLOCKS>& newCurrentBlocks = currentTetromino_->gotoBlocks_;
	if (!board_->CanBlocksDeploy(newCurrentBlocks.data(), newCurrentBlocks.size()))
	{
		status_ = Status::DONE;
		return;
	}

	status_ = Status::ACTIVE;
	nextTetromino_ = CreateRandomTetromino(waitPos_, blockSize_, blockStride_);
}