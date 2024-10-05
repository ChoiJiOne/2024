#include "Assertion.h"
#include "RenderManager2D.h"

#include "Board.h"

Board::Board(const Vec2f& center, float cellSize, uint32_t row, uint32_t col)
	: center_(center)
	, cellSize_(cellSize)
	, row_(row)
	, col_(col)
	, removeColumn_(col_)
{
	size_.x = static_cast<float>(row) * cellSize_;
	size_.y = static_cast<float>(col) * cellSize_;

	outlineColor_ = Vec4f(1.0f, 1.0f, 1.0f, 1.0f);
	inlineColor_ = Vec4f(0.3f, 0.3f, 0.3f, 0.3f);

	inlines_ = std::vector<Vec2f>((row_ - 2) * (col_ - 2) * 2);
	
	int32_t index = 0;
	for (uint32_t row = 1; row < row_; ++row)
	{
		inlines_[index++] = center_ + Vec2f(-size_.x * 0.5f + static_cast<float>(row) * cellSize_, size_.y * 0.5f - static_cast<float>(0) * cellSize_);
		inlines_[index++] = center_ + Vec2f(-size_.x * 0.5f + static_cast<float>(row) * cellSize_, size_.y * 0.5f - static_cast<float>(col_) * cellSize_);
	}

	for (uint32_t col = 1; col < col_; ++col)
	{
		inlines_[index++] = center_ + Vec2f(-size_.x * 0.5f + static_cast<float>(0) * cellSize_, size_.y * 0.5f - static_cast<float>(col) * cellSize_);
		inlines_[index++] = center_ + Vec2f(-size_.x * 0.5f + static_cast<float>(row_) * cellSize_, size_.y * 0.5f - static_cast<float>(col) * cellSize_);
	}
	
	cells_ = std::vector<std::pair<Block, bool>>(row_ * col_);
	for (uint32_t colIndex = 0; colIndex < col_; ++colIndex)
	{
		for (uint32_t rowIndex = 0; rowIndex < row_; ++rowIndex)
		{
			uint32_t index = rowIndex + colIndex * row_;
			Vec2f center = CalculateCellPos(rowIndex, colIndex);

			cells_[index] = { Block(Rect2D(center, cellSize_), Vec4f(0.0f, 0.0f, 0.0f, 0.0f)), false };
		}
	}

	startPos_ = CalculateCellPos(4, 0);

	bIsInitialized_ = true;
}

Board::~Board()
{
	if (bIsInitialized_)
	{
		Release();
	}
}

void Board::Tick(float deltaSeconds)
{
	switch (status_)
	{
	case Status::WAIT:
	{

	}
	break;

	case Status::REMOVE:
	{

	}
	break;

	case Status::FILL:
	{

	}
	break;
	}

	//status_ = Status::WAIT;
}

void Board::Render()
{
	RenderManager2D& renderMgr = RenderManager2D::Get();

	renderMgr.DrawRectWireframe(center_, size_.x, size_.y, outlineColor_, 0.0f);

	for (uint32_t index = 0; index < inlines_.size(); index += 2)
	{
		renderMgr.DrawLine(inlines_[index + 0], inlines_[index + 1], inlineColor_);
	}

	for (const auto& cell : cells_)
	{
		if (cell.second)
		{
			const Block& block = cell.first;
			const Rect2D& bound = block.GetBound();
			renderMgr.DrawRoundRect(bound.center, bound.size.x, bound.size.y, 10.0f, block.GetColor(), 0.0f);
		}
	}
}

void Board::Release()
{
	CHECK(bIsInitialized_);

	bIsInitialized_ = false;
}

bool Board::IsBlocksInside(const Block* blocks, uint32_t count)
{
	for (uint32_t index = 0; index < count; ++index)
	{
		bool bIsBlockInside = false;
		const Rect2D& bound = blocks[index].GetBound();

		for (const auto& cell : cells_)
		{
			const Rect2D cellBound = cell.first.GetBound();

			if (cellBound.Intersect(&bound))
			{
				bIsBlockInside = true;
				break;
			}
		}

		if (!bIsBlockInside)
		{
			return false;
		}
	}
	
	return true;
}

bool Board::CanBlocksDeploy(const Block* blocks, uint32_t count)
{
	for (uint32_t index = 0; index < count; ++index)
	{
		bool bCanBlocksDeploy = true;
		const Rect2D& bound = blocks[index].GetBound();

		for (const auto& cell : cells_)
		{
			const Rect2D cellBound = cell.first.GetBound();

			if (cellBound.Intersect(&bound) && cell.second)
			{
				bCanBlocksDeploy = false;
				break;
			}
		}

		if (!bCanBlocksDeploy)
		{
			return false;
		}
	}

	return true;
}

void Board::DeployBlocks(const Block* blocks, uint32_t count)
{
	for (uint32_t index = 0; index < count; ++index)
	{
		const Block& block = blocks[index];
		const Rect2D& bound = block.GetBound();

		for (auto& cell : cells_)
		{
			const Rect2D cellBound = cell.first.GetBound();

			if (cellBound.Intersect(&bound))
			{
				cell = { block, true };
				break;
			}
		}
	}

	UpdateRemoveColumn();
	status_ = Status::REMOVE;
}

Vec2f Board::CalculateCellPos(uint32_t row, uint32_t col)
{
	Vec2f cellPos = center_;
	cellPos += Vec2f(-size_.x * 0.5f + (static_cast<float>(row) + 0.5f) * cellSize_, +size_.y * 0.5f - (static_cast<float>(col) + 0.5f) * cellSize_);
	return cellPos;
}

void Board::UpdateRemoveColumn()
{
	for (uint32_t col = 0; col < col_; ++col)
	{
		int32_t count = 0;

		for (uint32_t row = 0; row < row_; ++row)
		{
			uint32_t index = row + col * row_;
			if (cells_[index].second)
			{
				count++;
			}
		}

		removeColumn_[col] = (count == row_);
	}
}
