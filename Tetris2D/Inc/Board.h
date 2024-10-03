#pragma once

#include <vector>

#include "IEntity2D.h"
#include "GameMath.h"

#include "Block.h"

class Board : public IEntity2D
{
public:
	/** row: За, col: ї­ */
	Board(const Vec2f& center, float blockSize, uint32_t row, uint32_t col);
	virtual ~Board();

	DISALLOW_COPY_AND_ASSIGN(Board);

	virtual void Tick(float deltaSeconds) override;
	virtual void Render() override;
	virtual void Release() override;

	float GetBlockSize() const { return blockSize_; }
	uint32_t GetRow() const { return row_; }
	uint32_t GetCol() const { return col_; }

	const Vec2f& GetStartPos() const { return startPos_; }
	bool IsBlockInside(const Block* blocks, uint32_t count);

private:
	Vec2f CalculateCellPos(uint32_t row, uint32_t col);

private:
	Vec2f center_;
	float blockSize_ = 0.0f;
	uint32_t row_ = 0U;
	uint32_t col_ = 0U;
	Vec2f size_;
	Vec2f startPos_;

	Vec4f outlineColor_;
	Vec4f inlineColor_;

	std::vector<Vec2f> inlines_;
	std::vector<Block> cells_;
};