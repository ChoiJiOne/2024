#pragma once

#include <array>

#include "IApp.h"
#include "IEntity2D.h"
#include "GameMath.h"

#include "Block.h"

class Board;
class GameApp;

class Tetromino : public IEntity2D
{
public:
	/** https://en.wikipedia.org/wiki/Tetromino */
	enum class Type
	{
		NONE = 0x00,
		I = 0x01,
		O = 0x02,
		T = 0x03,
		J = 0x04,
		L = 0x05,
		S = 0x06,
		Z = 0x07,
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
	enum class Direction
	{
		LEFT  = 0x00,
		RIGHT = 0x01,
		DOWN  = 0x02,
		UP    = 0x03,
	};

	void ConstructBlocks(const Vec2f& startPos, float blockSize, const Vec4f& color);
	void Move(const Direction& direction);

private:
	Board* board_ = nullptr;

	float stride_ = 0.0f;
	Type type_ = Type::NONE;
	Vec2f rotatePos_;
	std::array<Block, NUM_BLOCKS> blocks_;

	static GameApp* app_;
	static std::map<Key, Direction> keyDirections_;
};