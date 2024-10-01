#include "Assertion.h"
#include "EntityManager.h"
#include "RenderManager2D.h"

#include "Board.h"
#include "Tetromino.h"

Tetromino::Tetromino()
{
	board_ = EntityManager::Get().GetByName<Board>("Board");

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
	Vec2f start = Vec2f(board_->GetMinBlockCenterX(), board_->GetMaxBlockCenterY());

	RenderManager2D& renderMgr = RenderManager2D::Get();
	for (uint32_t count = 0; count < 4; ++count)
	{
		start.x = board_->GetMinBlockCenterX() + static_cast<float>(count) * board_->GetBlockSize();
		renderMgr.DrawRoundRect(start, board_->GetBlockSize() * 0.9f, board_->GetBlockSize() * 0.9f, 5.0f, Vec4f(1.0f, 1.0f, 0.0f, 1.0f), 0.0f);
	}
}

void Tetromino::Release()
{
	CHECK(bIsInitialized_);

	board_ = nullptr;

	bIsInitialized_ = false;
}
