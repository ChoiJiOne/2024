#pragma once

#include <vector>

#include "IEntity2D.h"
#include "GameMath.h"

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

	const std::vector<Vec2f>& GetBlockCenters() { return blockCenters_; }

private:
	Vec2f center_;
	float blockSize_ = 0.0f;
	uint32_t row_ = 0U;
	uint32_t col_ = 0U;
	Vec2f size_;

	Vec4f outlineColor_;
	Vec4f inlineColor_;

	std::vector<Vec2f> inlines_;
	std::vector<Vec2f> blockCenters_;
};