#include "Assertion.h"
#include "RenderManager2D.h"

#include "Board.h"

Board::Board(const Vec2f& center, float blockSize, uint32_t row, uint32_t col)
	: center_(center)
	, blockSize_(blockSize)
	, row_(row)
	, col_(col)
{
	center_ = Vec2f(-100.0f, 0.0f);
	size_.x = static_cast<float>(row) * blockSize;
	size_.y = static_cast<float>(col) * blockSize;

	outlineColor_ = Vec4f(1.0f, 1.0f, 1.0f, 1.0f);
	inlineColor_ = Vec4f(0.3f, 0.3f, 0.3f, 0.3f);

	blockCenters_ = std::vector<Vec2f>(row_ * col_, center_);
	for (uint32_t colIndex = 0; colIndex < col_; ++colIndex)
	{
		for (uint32_t rowIndex = 0; rowIndex < row_; ++rowIndex)
		{
			uint32_t index = rowIndex + colIndex * row_;
			blockCenters_[index] += Vec2f(
				-size_.x * 0.5f + (static_cast<float>(rowIndex) + 0.5f) * blockSize_,
				+size_.y * 0.5f - (static_cast<float>(colIndex) + 0.5f) * blockSize_
			);
		}
	}

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
}

void Board::Render()
{
	RenderManager2D& renderMgr = RenderManager2D::Get();

	renderMgr.DrawRectWireframe(center_, size_.x, size_.y, outlineColor_, 0.0f);

	Vec2f start;
	Vec2f end;
	for (uint32_t row = 1; row < row_; ++row)
	{
		start = center_ + Vec2f(-size_.x * 0.5f + static_cast<float>(row) * blockSize_, size_.y * 0.5f - static_cast<float>(0) * blockSize_);
		end = center_ + Vec2f(-size_.x * 0.5f + static_cast<float>(row) * blockSize_, size_.y * 0.5f - static_cast<float>(col_) * blockSize_);

		renderMgr.DrawLine(start, end, inlineColor_);
	}

	for (uint32_t col = 1; col < col_; ++col)
	{
		start = center_ + Vec2f(-size_.x * 0.5f + static_cast<float>(0) * blockSize_, size_.y * 0.5f - static_cast<float>(col) * blockSize_);
		end = center_ + Vec2f(-size_.x * 0.5f + static_cast<float>(row_) * blockSize_, size_.y * 0.5f - static_cast<float>(col) * blockSize_);

		renderMgr.DrawLine(start, end, inlineColor_);
	}
}

void Board::Release()
{
	CHECK(bIsInitialized_);

	bIsInitialized_ = false;
}
