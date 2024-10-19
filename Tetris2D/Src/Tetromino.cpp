#include "Assertion.h"
#include "EntityManager.h"
#include "RenderManager2D.h"

#include "Board.h"
#include "MainCamera2D.h"
#include "Tetromino.h"

float Tetromino::maxMoveStepTime_ = 0.0f;
InputManager* Tetromino::inputMgr_ = nullptr;
Board* Tetromino::board_ = nullptr;
MainCamera2D* Tetromino::camera_ = nullptr;
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
	if (!inputMgr_)
	{
		inputMgr_ = InputManager::GetPtr();
	}
	
	if (!board_)
	{
		board_ = EntityManager::GetRef().GetByName<Board>("Board");
	}

	if (!camera_)
	{
		camera_ = EntityManager::GetRef().GetByName<MainCamera2D>("MainCamera");
	}

	CreateBlocks(blocks_, rotatePos_, startPos, blockSize, color);

	moveStepTime_ = maxMoveStepTime_;

	shadowColor_ = Vec4f(1.0f, 1.0f, 1.0f, 0.3f);

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
	switch (status_)
	{
	case Status::WAIT:
		// Nothing...
		break;

	case Status::GOTO:
		UpdateGotoStatus(deltaSeconds);
		break;

	case Status::ACTIVE:
		UpdateActiveStatus(deltaSeconds);
		if (bNeedUpdateShadow_)
		{
			UpdateShadowBlocks();
		}
		break;

	case Status::DONE:
		// Nothing...
		break;
	}
}

void Tetromino::Render()
{
	if (status_ == Status::DONE)
	{
		return;
	}

	RenderManager2D& renderMgr = RenderManager2D::GetRef();
	if (status_ == Status::ACTIVE)
	{
		for (const auto& shadowBlock : shadowBlocks_)
		{
			const Rect2D& bound = shadowBlock.GetBound();
			const Vec4f& color = shadowBlock.GetColor();
			renderMgr.DrawRect(bound.center, bound.size.x, bound.size.y, color, 0.0f);
		}
	}

	for (const auto& block : blocks_)
	{
		const Rect2D& bound = block.GetBound();
		const Vec4f& color = block.GetColor();
		renderMgr.DrawRect(bound.center, bound.size.x, bound.size.y, color, 0.0f);
	}
}

void Tetromino::Release()
{
	CHECK(bIsInitialized_);

	bIsInitialized_ = false;
}

void Tetromino::GotoPosition(const Vec2f& gotoPos)
{
	const Block& block = blocks_.front();
	float blockSize = block.GetBound().size.x;
	Vec4f color = block.GetColor();

	gotoStepTime_ = 0.0f;
	maxGotoStepTime_ = 0.3f;

	startRotatePos_ = rotatePos_;
	startBlocks_ = blocks_;

	Vec2f startPos = board_->GetStartPos();
	CreateBlocks(gotoBlocks_, gotoRotatePos_, startPos, blockSize, color);
	
	status_ = Status::GOTO;
}

void Tetromino::SetMaxMoveStepTime(float maxMoveStepTime)
{
	maxMoveStepTime_ = maxMoveStepTime;
}

void Tetromino::Move(const Direction& direction)
{
	if (!CanMoveBlocks(direction, blocks_, rotatePos_))
	{
		return;
	}

	bNeedUpdateShadow_ = true;
	MoveBlocks(direction, blocks_, rotatePos_);
}

void Tetromino::Rotate()
{
	if (!CanRotateBlocks(blocks_, rotatePos_))
	{
		return;
	}

	bNeedUpdateShadow_ = true;
	RotateBlocks(blocks_, rotatePos_);
}

bool Tetromino::IsDone()
{
	std::array<Block, NUM_BLOCKS> tempBlocks = blocks_;
	Vec2f tempRotatePos = rotatePos_;

	MoveBlocks(Direction::DOWN, tempBlocks, tempRotatePos);

	return !board_->IsBlocksInside(tempBlocks.data(), NUM_BLOCKS) || !board_->CanBlocksDeploy(tempBlocks.data(), NUM_BLOCKS);
}

void Tetromino::UpdateGotoStatus(float deltaSeconds)
{
	gotoStepTime_ += deltaSeconds;
	float step = gotoStepTime_ / maxGotoStepTime_;
	step = GameMath::Clamp<float>(step, 0.0f, 1.0f);

	Vec2f rotateControll(startRotatePos_.x, gotoRotatePos_.y);
	rotatePos_ = Vec2f::Bezier(startRotatePos_, gotoRotatePos_, rotateControll, step);

	for (uint32_t index = 0; index < NUM_BLOCKS; ++index)
	{
		Vec2f start = startBlocks_[index].GetBound().center;
		Vec2f end = gotoBlocks_[index].GetBound().center;
		Vec2f controll = Vec2f(start.x, end.y);

		Vec2f center = Vec2f::Bezier(start, end, controll, step);
		blocks_[index].SetCenter(center);
	}

	if (step >= 1.0f)
	{
		status_ = Status::ACTIVE;
	}
}

void Tetromino::UpdateActiveStatus(float deltaSeconds)
{
	for (const auto& keyDirection : keyDirections_)
	{
		Press press = inputMgr_->GetKeyPress(keyDirection.first);

		if (press == Press::PRESSED)
		{
			Move(keyDirection.second);
		}
		else if (press == Press::HELD)
		{
			if (!bIsHoldKey_)
			{
				holdKeyStepTime_ += deltaSeconds;
				if (holdKeyStepTime_ >= holdWaitTime_)
				{
					holdKeyStepTime_ = 0.0f;
					bIsHoldKey_ = true;
				}
			}
			else
			{
				holdKeyStepTime_ += deltaSeconds;
				if (holdKeyStepTime_ >= maxHoldKeyStepTime_)
				{
					holdKeyStepTime_ -= maxHoldKeyStepTime_;
					Move(keyDirection.second);
				}
			}
		}
		else if (press == Press::RELEASED)
		{
			holdKeyStepTime_ = 0.0f;
			bIsHoldKey_ = false;
		}
	}

	if (inputMgr_->GetKeyPress(Key::KEY_UP) == Press::PRESSED)
	{
		Rotate();
	}

	if (inputMgr_->GetKeyPress(Key::KEY_SPACE) == Press::PRESSED)
	{
		while (CanMoveBlocks(Tetromino::Direction::DOWN, blocks_, rotatePos_))
		{
			MoveBlocks(Tetromino::Direction::DOWN, blocks_, rotatePos_);
		}

		camera_->Shake();
		status_ = Status::DONE;
		return;
	}

	Press press = inputMgr_->GetKeyPress(Key::KEY_DOWN);
	if (press == Press::PRESSED || press == Press::HELD)
	{
		moveStepTime_ = maxMoveStepTime_;
	}

	moveStepTime_ -= deltaSeconds;
	if (moveStepTime_ <= 0.0f)
	{
		if (IsDone())
		{
			status_ = Status::DONE;
		}
		else
		{
			moveStepTime_ = maxMoveStepTime_;
			Move(Direction::DOWN);
		}
	}
}

void Tetromino::UpdateShadowBlocks()
{
	std::array<Block, NUM_BLOCKS> tempBlocks = blocks_;
	Vec2f rotatePos = rotatePos_;

	while (CanMoveBlocks(Tetromino::Direction::DOWN, tempBlocks, rotatePos))
	{
		MoveBlocks(Tetromino::Direction::DOWN, tempBlocks, rotatePos);
	}

	shadowBlocks_ = tempBlocks;
	for (auto& shaodwBlock : shadowBlocks_)
	{
		shaodwBlock.SetColor(shadowColor_);
	}

	bNeedUpdateShadow_ = false;
}

void Tetromino::CreateBlocks(std::array<Block, NUM_BLOCKS>& outBlocks, Vec2f& outRotatePos, const Vec2f& startPos, float blockSize, const Vec4f& color)
{
	for (auto& block : outBlocks)
	{
		block.SetBound(Rect2D(Vec2f(0.0f, 0.0f), Vec2f(blockSize, blockSize)));
		block.SetColor(color);
	}

	switch (type_)
	{
	case Type::I:
	{
		outBlocks[0].SetCenter(Vec2f(startPos.x + 0.0f * stride_, startPos.y - 1.0f * stride_));
		outBlocks[1].SetCenter(Vec2f(startPos.x + 1.0f * stride_, startPos.y - 1.0f * stride_));
		outBlocks[2].SetCenter(Vec2f(startPos.x + 2.0f * stride_, startPos.y - 1.0f * stride_));
		outBlocks[3].SetCenter(Vec2f(startPos.x + 3.0f * stride_, startPos.y - 1.0f * stride_));

		outRotatePos = startPos + Vec2f(+1.5f * stride_, -1.5f * stride_);
	}
	break;

	case Type::O:
	{
		outBlocks[0].SetCenter(Vec2f(startPos.x + 0.0f * stride_, startPos.y - 0.0f * stride_));
		outBlocks[1].SetCenter(Vec2f(startPos.x + 1.0f * stride_, startPos.y - 0.0f * stride_));
		outBlocks[2].SetCenter(Vec2f(startPos.x + 0.0f * stride_, startPos.y - 1.0f * stride_));
		outBlocks[3].SetCenter(Vec2f(startPos.x + 1.0f * stride_, startPos.y - 1.0f * stride_));

		outRotatePos = startPos + Vec2f(+0.5f * stride_, -0.5f * stride_);
	}
	break;

	case Type::T:
	{
		outBlocks[0].SetCenter(Vec2f(startPos.x + 0.0f * stride_, startPos.y - 1.0f * stride_));
		outBlocks[1].SetCenter(Vec2f(startPos.x + 1.0f * stride_, startPos.y - 1.0f * stride_));
		outBlocks[2].SetCenter(Vec2f(startPos.x + 2.0f * stride_, startPos.y - 1.0f * stride_));
		outBlocks[3].SetCenter(Vec2f(startPos.x + 1.0f * stride_, startPos.y - 0.0f * stride_));

		outRotatePos = startPos + Vec2f(stride_, -stride_);
	}
	break;

	case Type::J:
	{
		outBlocks[0].SetCenter(Vec2f(startPos.x + 0.0f * stride_, startPos.y - 0.0f * stride_));
		outBlocks[1].SetCenter(Vec2f(startPos.x + 0.0f * stride_, startPos.y - 1.0f * stride_));
		outBlocks[2].SetCenter(Vec2f(startPos.x + 1.0f * stride_, startPos.y - 1.0f * stride_));
		outBlocks[3].SetCenter(Vec2f(startPos.x + 2.0f * stride_, startPos.y - 1.0f * stride_));

		outRotatePos = startPos + Vec2f(stride_, -stride_);
	}
	break;

	case Type::L:
	{
		outBlocks[0].SetCenter(Vec2f(startPos.x + 0.0f * stride_, startPos.y - 1.0f * stride_));
		outBlocks[1].SetCenter(Vec2f(startPos.x + 1.0f * stride_, startPos.y - 1.0f * stride_));
		outBlocks[2].SetCenter(Vec2f(startPos.x + 2.0f * stride_, startPos.y - 1.0f * stride_));
		outBlocks[3].SetCenter(Vec2f(startPos.x + 2.0f * stride_, startPos.y - 0.0f * stride_));

		outRotatePos = startPos + Vec2f(stride_, -stride_);
	}
	break;

	case Type::S:
	{
		outBlocks[0].SetCenter(Vec2f(startPos.x + 1.0f * stride_, startPos.y - 0.0f * stride_));
		outBlocks[1].SetCenter(Vec2f(startPos.x + 2.0f * stride_, startPos.y - 0.0f * stride_));
		outBlocks[2].SetCenter(Vec2f(startPos.x + 0.0f * stride_, startPos.y - 1.0f * stride_));
		outBlocks[3].SetCenter(Vec2f(startPos.x + 1.0f * stride_, startPos.y - 1.0f * stride_));

		outRotatePos = startPos + Vec2f(stride_, -stride_);
	}
	break;

	case Type::Z:
	{
		outBlocks[0].SetCenter(Vec2f(startPos.x + 0.0f * stride_, startPos.y - 0.0f * stride_));
		outBlocks[1].SetCenter(Vec2f(startPos.x + 1.0f * stride_, startPos.y - 0.0f * stride_));
		outBlocks[2].SetCenter(Vec2f(startPos.x + 1.0f * stride_, startPos.y - 1.0f * stride_));
		outBlocks[3].SetCenter(Vec2f(startPos.x + 2.0f * stride_, startPos.y - 1.0f * stride_));

		outRotatePos = startPos + Vec2f(stride_, -stride_);
	}
	break;
	}
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

bool Tetromino::CanMoveBlocks(const Direction& direction, const std::array<Block, NUM_BLOCKS>& blocks, const Vec2f& rotatePos)
{
	std::array<Block, NUM_BLOCKS> tempBlocks = blocks;
	Vec2f tempRotatePos = rotatePos;

	MoveBlocks(direction, tempBlocks, tempRotatePos);

	return board_->IsBlocksInside(tempBlocks.data(), NUM_BLOCKS) && board_->CanBlocksDeploy(tempBlocks.data(), NUM_BLOCKS);
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

bool Tetromino::CanRotateBlocks(const std::array<Block, NUM_BLOCKS>& blocks, const Vec2f& rotatePos)
{
	std::array<Block, NUM_BLOCKS> tempBlocks = blocks;
	Vec2f tempRotatePos = rotatePos;

	RotateBlocks(tempBlocks, tempRotatePos);

	return board_->IsBlocksInside(tempBlocks.data(), NUM_BLOCKS) && board_->CanBlocksDeploy(tempBlocks.data(), NUM_BLOCKS);
}