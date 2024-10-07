#pragma once

#include <list>
#include <functional>
#include <vector>

#include "IEntity2D.h"
#include "GameMath.h"

#include "Block.h"

class Board : public IEntity2D
{
public:
	enum class Status
	{
		WAIT    = 0x00, /** 대기 */
		REMOVE  = 0x01, /** 꽉 채워진 라인을 삭제 */
		CONFIRM = 0x02, /** 비워진 라인이 있는지 확인. */
		FILL    = 0x03, /** 비워진 라인을 채움. */
	};

public:
	/** row: 행, col: 열 */
	Board(const Vec2f& center, float cellSize, uint32_t row, uint32_t col);
	virtual ~Board();

	DISALLOW_COPY_AND_ASSIGN(Board);

	virtual void Tick(float deltaSeconds) override;
	virtual void Render() override;
	virtual void Release() override;

	float GetCellSize() const { return cellSize_; }
	uint32_t GetRow() const { return row_; }
	uint32_t GetCol() const { return col_; }
	const Status& GetStatus() const { return status_; }

	const Vec2f& GetStartPos() const { return startPos_; }

	/** 보드 내의 블럭 관련 기능. */
	bool IsBlocksInside(const Block* blocks, uint32_t count);
	bool CanBlocksDeploy(const Block* blocks, uint32_t count);
	void DeployBlocks(const Block* blocks, uint32_t count);

private:
	void CleanupInlines(std::vector<Vec2f>& inlines);
	void CleanupCells(std::vector<std::pair<Block, bool>>& cells);

	Vec2f CalculateCellPos(uint32_t row, uint32_t col);

	/** 열(Column) 관련 기능. */
	bool UpdateRemoveColumn();
	bool IsEmptyColumn(uint32_t col);
	void GotoColumn(float t, int32_t fromFillColumn, int32_t toFillColumn, std::vector<std::pair<Block, bool>>& fillBlocks);

private:
	Rect2D bound_;
	float cellSize_ = 0.0f;
	uint32_t row_ = 0U;
	uint32_t col_ = 0U;
	Vec2f startPos_;

	Vec4f outlineColor_;
	Vec4f inlineColor_;

	std::vector<Vec2f> inlines_;
	std::vector<std::pair<Block, bool>> cells_;

	float removeStepTime_ = 0.0f;
	float maxRemoveStepTime_ = 0.0f;
	std::vector<bool> removeColumn_;

	float fillStepTime_ = 0.0f;
	float maxFillStepTime_ = 0.0f;
	std::vector<std::pair<Block, bool>> fillBlocks_;
	int32_t fromFillColumn_;
	int32_t toFillColumn_;

	Status status_ = Status::WAIT;
};