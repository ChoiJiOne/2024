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

	inlines_ = std::vector<Vec2f>((row_ - 2) * (col_ - 2) * 2);
	
	int32_t index = 0;
	for (uint32_t row = 1; row < row_; ++row)
	{
		inlines_[index++] = center_ + Vec2f(-size_.x * 0.5f + static_cast<float>(row) * blockSize_, size_.y * 0.5f - static_cast<float>(0) * blockSize_);
		inlines_[index++] = center_ + Vec2f(-size_.x * 0.5f + static_cast<float>(row) * blockSize_, size_.y * 0.5f - static_cast<float>(col_) * blockSize_);
	}

	for (uint32_t col = 1; col < col_; ++col)
	{
		inlines_[index++] = center_ + Vec2f(-size_.x * 0.5f + static_cast<float>(0) * blockSize_, size_.y * 0.5f - static_cast<float>(col) * blockSize_);
		inlines_[index++] = center_ + Vec2f(-size_.x * 0.5f + static_cast<float>(row_) * blockSize_, size_.y * 0.5f - static_cast<float>(col) * blockSize_);
	}

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

	maxBlockCenter_ = center_ + Vec2f(-size_.x * 0.5f + (static_cast<float>(row_ - 1) + 0.5f) * blockSize_, (size_.y - blockSize_) * 0.5f);
	minBlockCenter_ = center_ + Vec2f((-size_.x + blockSize_) * 0.5f, +size_.y * 0.5f - (static_cast<float>(col_ - 1) + 0.5f) * blockSize_);

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

	for (uint32_t index = 0; index < inlines_.size(); index += 2)
	{
		renderMgr.DrawLine(inlines_[index + 0], inlines_[index + 1], inlineColor_);
	}
}

void Board::Release()
{
	CHECK(bIsInitialized_);

	bIsInitialized_ = false;
}
