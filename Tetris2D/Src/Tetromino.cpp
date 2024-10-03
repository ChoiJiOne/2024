#include "Assertion.h"
#include "EntityManager.h"
#include "RenderManager2D.h"

#include "Board.h"
#include "Tetromino.h"

Tetromino::Tetromino(const Vec2f& startPos, float blockSize, float stride, const Type& type, const Vec4f& color)
{
	board_ = EntityManager::Get().GetByName<Board>("Board");

	ConstructBlocks(startPos, blockSize, stride, type, color);

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

void Tetromino::ConstructBlocks(const Vec2f& startPos, float blockSize, float stride, const Type& type, const Vec4f& color)
{
	for (auto& block : blocks_)
	{
		const Rect2D& bound = block.GetBound();

		block.SetBound(Rect2D(Vec2f(0.0f, 0.0f), Vec2f(blockSize, blockSize)));
		block.SetColor(color);
	}

	switch (type)
	{
	case Type::I:
	{
		blocks_[0].SetCenter(Vec2f(startPos.x + 0.0f * stride, startPos.y - 1.0f * stride));
		blocks_[1].SetCenter(Vec2f(startPos.x + 1.0f * stride, startPos.y - 1.0f * stride));
		blocks_[2].SetCenter(Vec2f(startPos.x + 2.0f * stride, startPos.y - 1.0f * stride));
		blocks_[3].SetCenter(Vec2f(startPos.x + 3.0f * stride, startPos.y - 1.0f * stride));
	}
	break;

	case Type::O:
	{
		blocks_[0].SetCenter(Vec2f(startPos.x + 0.0f * stride, startPos.y - 0.0f * stride));
		blocks_[1].SetCenter(Vec2f(startPos.x + 1.0f * stride, startPos.y - 0.0f * stride));
		blocks_[2].SetCenter(Vec2f(startPos.x + 0.0f * stride, startPos.y - 1.0f * stride));
		blocks_[3].SetCenter(Vec2f(startPos.x + 1.0f * stride, startPos.y - 1.0f * stride));
	}
	break;

	case Type::T:
	{
		blocks_[0].SetCenter(Vec2f(startPos.x + 0.0f * stride, startPos.y - 1.0f * stride));
		blocks_[1].SetCenter(Vec2f(startPos.x + 1.0f * stride, startPos.y - 1.0f * stride));
		blocks_[2].SetCenter(Vec2f(startPos.x + 2.0f * stride, startPos.y - 1.0f * stride));
		blocks_[3].SetCenter(Vec2f(startPos.x + 1.0f * stride, startPos.y - 2.0f * stride));
	}
	break;

	case Type::J:
	{
		blocks_[0].SetCenter(Vec2f(startPos.x + 0.0f * stride, startPos.y - 1.0f * stride));
		blocks_[1].SetCenter(Vec2f(startPos.x + 1.0f * stride, startPos.y - 1.0f * stride));
		blocks_[2].SetCenter(Vec2f(startPos.x + 2.0f * stride, startPos.y - 1.0f * stride));
		blocks_[3].SetCenter(Vec2f(startPos.x + 2.0f * stride, startPos.y - 2.0f * stride));
	}
	break;

	case Type::L:
	{
		blocks_[0].SetCenter(Vec2f(startPos.x + 0.0f * stride, startPos.y - 1.0f * stride));
		blocks_[1].SetCenter(Vec2f(startPos.x + 1.0f * stride, startPos.y - 1.0f * stride));
		blocks_[2].SetCenter(Vec2f(startPos.x + 2.0f * stride, startPos.y - 1.0f * stride));
		blocks_[3].SetCenter(Vec2f(startPos.x + 0.0f * stride, startPos.y - 2.0f * stride));
	}
	break;

	case Type::S:
	{
		blocks_[0].SetCenter(Vec2f(startPos.x + 1.0f * stride, startPos.y - 0.0f * stride));
		blocks_[1].SetCenter(Vec2f(startPos.x + 2.0f * stride, startPos.y - 0.0f * stride));
		blocks_[2].SetCenter(Vec2f(startPos.x + 0.0f * stride, startPos.y - 1.0f * stride));
		blocks_[3].SetCenter(Vec2f(startPos.x + 1.0f * stride, startPos.y - 1.0f * stride));
	}
	break;

	case Type::Z:
	{
		blocks_[0].SetCenter(Vec2f(startPos.x + 0.0f * stride, startPos.y - 0.0f * stride));
		blocks_[1].SetCenter(Vec2f(startPos.x + 1.0f * stride, startPos.y - 0.0f * stride));
		blocks_[2].SetCenter(Vec2f(startPos.x + 1.0f * stride, startPos.y - 1.0f * stride));
		blocks_[3].SetCenter(Vec2f(startPos.x + 2.0f * stride, startPos.y - 1.0f * stride));
	}
	break;
	}
}
