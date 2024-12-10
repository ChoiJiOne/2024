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
		ACTIVE   = 0x00, /** 활성화 상태 */
		DEACTIVE = 0x01, /** 비활성화 상태 */
		DONE     = 0x02, /** 더 이상 진행할 수 없는 상태 */
	};

public:
	TetrominoController();
	virtual ~TetrominoController();

	DISALLOW_COPY_AND_ASSIGN(TetrominoController);

	virtual void Tick(float deltaSeconds) override;
	virtual void Render() override;
	virtual void Release() override;

	void Reset();

	const Status& GetStatus() const { return status_; }

private:
	Tetromino* CreateRandomTetromino(const Vec2f& startPos, float blockSize, float stride);

	void UpdateActiveStatus(float deltaSeconds);
	void UpdateDeactiveStatus(float deltaSeconds);
	
private:
	Vec2f startPos_;
	Vec2f waitPos_;
	float blockSize_ = 0.0f;
	float blockStride_ = 0.0f;

	Board* board_ = nullptr;
	Tetromino* currentTetromino_ = nullptr;
	Tetromino* nextTetromino_ = nullptr;

	Status status_ = Status::ACTIVE;
};