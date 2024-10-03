#pragma once

#include "IEntity2D.h"

#include "Block.h"

class Board;
class Tetromino;

class TetrominoController : public IEntity2D
{
public:
	TetrominoController();
	virtual ~TetrominoController();

	DISALLOW_COPY_AND_ASSIGN(TetrominoController);

	virtual void Tick(float deltaSeconds) override;
	virtual void Render() override;
	virtual void Release() override;

private:
	Board* board_ = nullptr;
	Tetromino* currentTetromino_ = nullptr;
	Tetromino* nextTetromino_ = nullptr;
};