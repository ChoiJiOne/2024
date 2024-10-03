#include "Assertion.h"
#include "EntityManager.h"
#include "RenderManager2D.h"

#include "Board.h"
#include "GameApp.h"
#include "Tetromino.h"

GameApp* Tetromino::app_ = nullptr;
std::map<Key, Tetromino::Direction> Tetromino::keyDirections_ =
{
	{ Key::KEY_LEFT,  Direction::LEFT  },
	{ Key::KEY_RIGHT, Direction::RIGHT },
	{ Key::KEY_DOWN,  Direction::DOWN  },
};

Tetromino::Tetromino(const Vec2f& startPos, float blockSize, float stride, const Type& type, const Vec4f& color)
	: stride_(stride)
	, type_(type)
{
	if (!app_)
	{
		app_ = reinterpret_cast<GameApp*>(IApp::Get());
	}
	
	board_ = EntityManager::Get().GetByName<Board>("Board");

	ConstructBlocks(startPos, blockSize, color);

	bIsInitialized_ = true;
}

Tetromino::~Tetromino()
{
	if (bIsInitialized_)
	{
		Release();
	}
}

void Tetromino::Tick(float deltaSeconds)
{
	for (const auto& keyDirection : keyDirections_)
	{
		if (app_->GetKeyPress(keyDirection.first) == Press::PRESSED && CanMove(keyDirection.second))
		{
			Move(keyDirection.second);
		}
	}

	if (app_->GetKeyPress(Key::KEY_UP) == Press::PRESSED && CanRotate())
	{
		Rotate();
	}
}

void Tetromino::Render()
{
	RenderManager2D& renderMgr = RenderManager2D::Get();
	for (const auto& block : blocks_)
	{
		const Rect2D& bound = block.GetBound();
		renderMgr.DrawRoundRect(bound.center, bound.size.x, bound.size.y, 10.0f, block.GetColor(), 0.0f);
	}
}

void Tetromino::Release()
{
	CHECK(bIsInitialized_);

	board_ = nullptr;

	bIsInitialized_ = false;
}

void Tetromino::ConstructBlocks(const Vec2f& startPos, float blockSize, const Vec4f& color)
{
	for (auto& block : blocks_)
	{
		const Rect2D& bound = block.GetBound();

		block.SetBound(Rect2D(Vec2f(0.0f, 0.0f), Vec2f(blockSize, blockSize)));
		block.SetColor(color);
	}

	switch (type_)
	{
	case Type::I:
	{
		blocks_[0].SetCenter(Vec2f(startPos.x + 0.0f * stride_, startPos.y - 1.0f * stride_));
		blocks_[1].SetCenter(Vec2f(startPos.x + 1.0f * stride_, startPos.y - 1.0f * stride_));
		blocks_[2].SetCenter(Vec2f(startPos.x + 2.0f * stride_, startPos.y - 1.0f * stride_));
		blocks_[3].SetCenter(Vec2f(startPos.x + 3.0f * stride_, startPos.y - 1.0f * stride_));

		rotatePos_ = startPos + Vec2f(+1.5f * stride_, -1.5f * stride_);
	}
	break;

	case Type::O:
	{
		blocks_[0].SetCenter(Vec2f(startPos.x + 0.0f * stride_, startPos.y - 0.0f * stride_));
		blocks_[1].SetCenter(Vec2f(startPos.x + 1.0f * stride_, startPos.y - 0.0f * stride_));
		blocks_[2].SetCenter(Vec2f(startPos.x + 0.0f * stride_, startPos.y - 1.0f * stride_));
		blocks_[3].SetCenter(Vec2f(startPos.x + 1.0f * stride_, startPos.y - 1.0f * stride_));

		rotatePos_ = startPos + Vec2f(+0.5f * stride_, -0.5f * stride_);
	}
	break;

	case Type::T:
	{
		blocks_[0].SetCenter(Vec2f(startPos.x + 0.0f * stride_, startPos.y - 1.0f * stride_));
		blocks_[1].SetCenter(Vec2f(startPos.x + 1.0f * stride_, startPos.y - 1.0f * stride_));
		blocks_[2].SetCenter(Vec2f(startPos.x + 2.0f * stride_, startPos.y - 1.0f * stride_));
		blocks_[3].SetCenter(Vec2f(startPos.x + 1.0f * stride_, startPos.y - 2.0f * stride_));

		rotatePos_ = startPos + Vec2f(stride_, -stride_);
	}
	break;

	case Type::J:
	{
		blocks_[0].SetCenter(Vec2f(startPos.x + 0.0f * stride_, startPos.y - 1.0f * stride_));
		blocks_[1].SetCenter(Vec2f(startPos.x + 1.0f * stride_, startPos.y - 1.0f * stride_));
		blocks_[2].SetCenter(Vec2f(startPos.x + 2.0f * stride_, startPos.y - 1.0f * stride_));
		blocks_[3].SetCenter(Vec2f(startPos.x + 2.0f * stride_, startPos.y - 2.0f * stride_));
		
		rotatePos_ = startPos + Vec2f(stride_, -stride_);
	}
	break;

	case Type::L:
	{
		blocks_[0].SetCenter(Vec2f(startPos.x + 0.0f * stride_, startPos.y - 1.0f * stride_));
		blocks_[1].SetCenter(Vec2f(startPos.x + 1.0f * stride_, startPos.y - 1.0f * stride_));
		blocks_[2].SetCenter(Vec2f(startPos.x + 2.0f * stride_, startPos.y - 1.0f * stride_));
		blocks_[3].SetCenter(Vec2f(startPos.x + 0.0f * stride_, startPos.y - 2.0f * stride_));

		rotatePos_ = startPos + Vec2f(stride_, -stride_);
	}
	break;

	case Type::S:
	{
		blocks_[0].SetCenter(Vec2f(startPos.x + 1.0f * stride_, startPos.y - 0.0f * stride_));
		blocks_[1].SetCenter(Vec2f(startPos.x + 2.0f * stride_, startPos.y - 0.0f * stride_));
		blocks_[2].SetCenter(Vec2f(startPos.x + 0.0f * stride_, startPos.y - 1.0f * stride_));
		blocks_[3].SetCenter(Vec2f(startPos.x + 1.0f * stride_, startPos.y - 1.0f * stride_));

		rotatePos_ = startPos + Vec2f(stride_, -stride_);
	}
	break;

	case Type::Z:
	{
		blocks_[0].SetCenter(Vec2f(startPos.x + 0.0f * stride_, startPos.y - 0.0f * stride_));
		blocks_[1].SetCenter(Vec2f(startPos.x + 1.0f * stride_, startPos.y - 0.0f * stride_));
		blocks_[2].SetCenter(Vec2f(startPos.x + 1.0f * stride_, startPos.y - 1.0f * stride_));
		blocks_[3].SetCenter(Vec2f(startPos.x + 2.0f * stride_, startPos.y - 1.0f * stride_));

		rotatePos_ = startPos + Vec2f(stride_, -stride_);
	}
	break;
	}
}

bool Tetromino::CanMove(const Direction& direction)
{
	std::array<Block, NUM_BLOCKS> tempBlocks = blocks_;
	Vec2f tempRotatePos = rotatePos_;

	MoveBlocks(direction, tempBlocks, tempRotatePos);

	return board_->IsBlockInside(tempBlocks.data(), NUM_BLOCKS);
}

void Tetromino::Move(const Direction& direction)
{
	MoveBlocks(direction, blocks_, rotatePos_);
}

bool Tetromino::CanRotate()
{
	std::array<Block, NUM_BLOCKS> tempBlocks = blocks_;
	Vec2f tempRotatePos = rotatePos_;

	RotateBlocks(tempBlocks, tempRotatePos);

	return board_->IsBlockInside(tempBlocks.data(), NUM_BLOCKS);
}

void Tetromino::Rotate()
{
	RotateBlocks(blocks_, rotatePos_);
}

void Tetromino::MoveBlocks(const Direction& direction, std::array<Block, NUM_BLOCKS>& blocks, Vec2f& rotatePos)
{
	Vec2f moveLength;
	moveLength.x = direction == Direction::LEFT ? -stride_ : (direction == Direction::RIGHT ? stride_ : 0.0f);
	moveLength.y = direction == Direction::DOWN ? -stride_ : (direction == Direction::UP ? stride_ : 0.0f);

	for (auto& block : blocks)
	{
		Vec2f center = block.GetBound().center;
		center += moveLength;
		block.SetCenter(center);
	}

	rotatePos += moveLength;
}

void Tetromino::RotateBlocks(std::array<Block, NUM_BLOCKS>& blocks, Vec2f& rotatePos)
{
	float rotate = -PI_DIV_2;
	Mat2x2 rotateMat(GameMath::Cos(rotate), -GameMath::Sin(rotate), GameMath::Sin(rotate), GameMath::Cos(rotate));

	for (auto& block : blocks)
	{
		Vec2f center = block.GetBound().center;

		center -= rotatePos;
		center = rotateMat * center;
		center += rotatePos;

		block.SetCenter(center);
	}
}