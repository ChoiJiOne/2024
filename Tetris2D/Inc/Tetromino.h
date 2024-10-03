#pragma once

#include <array>

#include "IEntity2D.h"
#include "GameMath.h"

#include "Block.h"

class Board;

class Tetromino : public IEntity2D
{
public:
	/** https://en.wikipedia.org/wiki/Tetromino */
	enum class Type
	{
		I = 0x00,
		O = 0x01,
		T = 0x02,
		J = 0x03,
		L = 0x04,
		S = 0x05,
		Z = 0x06,
	};

	static const uint32_t NUM_BLOCKS = 4;
	
public:
	Tetromino(const Vec2f& startPos, float blockSize, float stride, const Type& type, const Vec4f& color);
	virtual ~Tetromino();

	DISALLOW_COPY_AND_ASSIGN(Tetromino);

	virtual void Tick(float deltaSeconds) override;
	virtual void Render() override;
	virtual void Release() override;

	const std::array<Block, NUM_BLOCKS>& GetBlocks() const { return blocks_; }

private:
	void ConstructBlocks(const Vec2f& startPos, float blockSize, float stride, const Type& type, const Vec4f& color);

private:
	Board* board_ = nullptr;

	Vec2f rotatePos_;
	std::array<Block, NUM_BLOCKS> blocks_;
};