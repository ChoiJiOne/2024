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

	enum class Status
	{
		WAIT   = 0x00, /** ���忡 ��ġ�Ǳ� ���� ���� */
		ACTIVE = 0x01, /** ���忡 ��ġ�Ǿ �÷��̾ ��Ʈ�� �� �� �ִ� ���� */
		DONE   = 0x02, /** �� �̻� ��Ʈ�ι̳븦 ������ �� ���� ���� */
	};

	static const uint32_t NUM_BLOCKS = 4;
	
public:
	Tetromino(const Vec2f& startPos, float blockSize, float stride, const Type& type, const Vec4f& color);
	virtual ~Tetromino();

	DISALLOW_COPY_AND_ASSIGN(Tetromino);

	virtual void Tick(float deltaSeconds) override;
	virtual void Render() override;
	virtual void Release() override;

	static Tetromino* CreateRandom(const Vec2f& startPos, float blockSize, float stride, const Vec4f& color);
	
private:
	enum class Direction
	{
		LEFT  = 0x00,
		RIGHT = 0x01,
		DOWN  = 0x02,
		UP    = 0x03,
	};

	friend class TetrominoController;

	void ConstructBlocks(const Vec2f& startPos, float blockSize, const Vec4f& color);

	bool CanMove(const Direction& direction);
	void Move(const Direction& direction);
	bool CanRotate();
	void Rotate();
	bool IsDone();

	void MoveBlocks(const Direction& direction, std::array<Block, NUM_BLOCKS>& blocks, Vec2f& rotatePos);
	void RotateBlocks(std::array<Block, NUM_BLOCKS>& blocks, Vec2f& rotatePos);

private:
	Board* board_ = nullptr;

	float stride_ = 0.0f;
	Type type_ = Type::NONE;
	Status status_ = Status::WAIT;
	Vec2f rotatePos_;
	std::array<Block, NUM_BLOCKS> blocks_;

	float moveStepTime_ = 0.0f;
	float maxMoveStepTime_ = 0.0f;

	static GameApp* app_;
	static std::map<Key, Direction> keyDirections_;
};