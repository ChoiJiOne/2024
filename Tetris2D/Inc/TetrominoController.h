#pragma once

#include "IEntity2D.h"

#include "Block.h"

class Board;
class Tetromino;

class TetrominoController : public IEntity2D
{
public:
	enum class Status
	{
		WAIT   = 0x00, /** 대기 상태 */
		DEPLOY = 0x01, /** 테트로미노를 보드에 배포 */
		DONE   = 0x02, /** 더 이상 진행할 수 없는 상태 */
	};

public:
	TetrominoController();
	virtual ~TetrominoController();

	DISALLOW_COPY_AND_ASSIGN(TetrominoController);

	virtual void Tick(float deltaSeconds) override;
	virtual void Render() override;
	virtual void Release() override;

private:
	Tetromino* CreateRandomTetromino(const Vec2f& startPos, float blockSize, float stride);

private:
	Vec2f startPos_;
	Vec2f waitPos_;
	float blockSize_ = 0.0f;
	float blockStride_ = 0.0f;

	Board* board_ = nullptr;
	Tetromino* currentTetromino_ = nullptr;
	Tetromino* nextTetromino_ = nullptr;

	Status status_ = Status::WAIT;
};