#pragma once

#include <array>

#include "InputManager.h"
#include "IEntity2D.h"
#include "GameMath.h"

#include "Block.h"

class Board;
class GameApp;
class MainCamera2D;

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
		WAIT   = 0x00, /** ���忡 ��ġ�Ǳ� �� ��� ���� */
		GOTO   = 0x01, /** ���忡 ��ġ�Ǳ� ���� �����̴� ���� */
		ACTIVE = 0x02, /** ���忡 ��ġ�Ǿ �÷��̾ ��Ʈ�� �� �� �ִ� ���� */
		DONE   = 0x03, /** �� �̻� ��Ʈ�ι̳븦 ������ �� ���� ���� */
	};

	static const uint32_t NUM_BLOCKS = 4;
	
public:
	Tetromino(const Vec2f& startPos, float blockSize, float stride, const Type& type, const Vec4f& color);
	virtual ~Tetromino();

	DISALLOW_COPY_AND_ASSIGN(Tetromino);

	virtual void Tick(float deltaSeconds) override;
	virtual void Render() override;
	virtual void Release() override;

	const Status& GetStatus() const { return status_; }
	const std::array<Block, NUM_BLOCKS>& GetBlocks() const { return blocks_; }

	void GotoPosition(const Vec2f& gotoPos);

	static void SetMaxMoveStepTime(float maxMoveStepTime);

private:
	enum class Direction
	{
		LEFT  = 0x00,
		RIGHT = 0x01,
		DOWN  = 0x02,
		UP    = 0x03,
	};

	friend class TetrominoController;

	void Move(const Direction& direction);
	void Rotate();
	bool IsDone();

	/** ���� ������Ʈ. */
	void UpdateGotoStatus(float deltaSeconds);
	void UpdateActiveStatus(float deltaSeconds);
	void UpdateShadowBlocks();
	
	/** ��ü ���� ���� ����. */
	void CreateBlocks(std::array<Block, NUM_BLOCKS>& outBlocks, Vec2f& outRotatePos, const Vec2f& startPos, float blockSize, const Vec4f& color);
	void MoveBlocks(const Direction& direction, std::array<Block, NUM_BLOCKS>& blocks, Vec2f& rotatePos);
	bool CanMoveBlocks(const Direction& direction, const std::array<Block, NUM_BLOCKS>& blocks, const Vec2f& rotatePos);
	void RotateBlocks(std::array<Block, NUM_BLOCKS>& blocks, Vec2f& rotatePos);
	bool CanRotateBlocks(const std::array<Block, NUM_BLOCKS>& blocks, const Vec2f& rotatePos);
	
private:
	float stride_ = 0.0f;
	Type type_ = Type::NONE;
	Status status_ = Status::WAIT;
	
	Vec2f rotatePos_;
	std::array<Block, NUM_BLOCKS> blocks_;
	std::array<Block, NUM_BLOCKS> shadowBlocks_;

	float moveStepTime_ = 0.0f;

	float gotoStepTime_ = 0.0f;
	float maxGotoStepTime_ = 0.0f;
	Vec2f startRotatePos_;
	std::array<Block, NUM_BLOCKS> startBlocks_;
	Vec2f gotoRotatePos_;
	std::array<Block, NUM_BLOCKS> gotoBlocks_;

	bool bIsHoldKey_ = false;
	float holdKeyStepTime_ = 0.0f;
	float holdWaitTime_ = 0.1f;
	float maxHoldKeyStepTime_ = 0.05f;

	Vec4f shadowColor_;
	bool bNeedUpdateShadow_ = true;

	static float maxMoveStepTime_;
	static InputManager* inputMgr_;
	static Board* board_;
	static MainCamera2D* camera_;
	static std::map<Key, Direction> keyDirections_;
};