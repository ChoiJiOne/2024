#include "Assertion.h"
#include "EntityManager.h"
#include "GameUtils.h"
#include "PanelUI.h"

#include "Board.h"
#include "Messenger.h"
#include "Tetromino.h"
#include "UserState.h"

UserState::UserState()
{
	messenger_ = EntityManager::GetRef().GetByName<Messenger>("Messenger");
	board_ = EntityManager::GetRef().GetByName<Board>("Board");

	level_ = Level::LEVEL_1;

	score_ = 0;
	scoreScale_ = 10;
	gainScoreMessagePos_ = board_->bound_.center - Vec2f(0.65f * static_cast<float>(board_->row_) * board_->cellSize_, 0.0f);
	gainScoreMessageColor_ = Vec3f(1.0f, 0.5f, 0.5f);
	gainScoreMessageTime_ = 1.0f;

	bEnableWarning_ = false;
	warningCol_ = 3;
	warningStepTime_ = 0.0f;
	maxWarningStepTime_ = 0.5f;
	warningMessagePos_ = board_->bound_.center + Vec2f(0.0f, 0.55f * static_cast<float>(board_->col_) * board_->cellSize_);
	warningMessageColor_ = Vec3f(1.0f, 0.0f, 0.0f);

	bIsInitialized_ = true;
}

UserState::~UserState()
{
	if (bIsInitialized_)
	{
		Release();
	}
}

void UserState::Tick(float deltaSeconds)
{
	if (bEnableWarning_)
	{
		warningStepTime_ += deltaSeconds;
		if (warningStepTime_ >= maxWarningStepTime_)
		{
			warningStepTime_ = 0.0f;
			bEnableWarning_ = false;
		}
	}

	if (!bEnableWarning_ && IsDetectWarning())
	{
		bEnableWarning_ = true;
		messenger_->Send(L"WARNING!", warningMessagePos_, warningMessageColor_, maxWarningStepTime_);
	}
}

void UserState::Release()
{
	CHECK(bIsInitialized_);

	board_ = nullptr;
	messenger_ = nullptr;

	bIsInitialized_ = false;
}

void UserState::Reset()
{
	level_ = Level::LEVEL_1;
	score_ = 0;
	bEnableWarning_ = false;
	warningStepTime_ = 0.0f;

	PanelUI* scoreUI = EntityManager::GetRef().GetByName<PanelUI>("Score");
	scoreUI->SetText(GameUtils::PrintF(L"%d", score_));

	PanelUI* levelUI = EntityManager::GetRef().GetByName<PanelUI>("Level");
	levelUI->SetText(GameUtils::PrintF(L"%d", static_cast<int32_t>(level_)));

	Tetromino::SetMaxMoveStepTime(1.0f);
}

void UserState::GainScore(uint32_t removeLines)
{
	for (uint32_t col = 0; col < board_->col_; ++col)
	{
		if (board_->removeColumn_[col])
		{
			gainScoreMessagePos_.y = board_->CalculateCellPos(0, col).y;
			break;
		}
	}

	int32_t gainScore = scoreScale_ * removeLines;
	messenger_->Send(GameUtils::PrintF(L"+%d", gainScore), gainScoreMessagePos_, gainScoreMessageColor_, gainScoreMessageTime_);

	score_ += gainScore;

	PanelUI* scoreUI = EntityManager::GetRef().GetByName<PanelUI>("Score");
	scoreUI->SetText(GameUtils::PrintF(L"%d", score_));
}

bool UserState::IsDetectWarning()
{
	for (uint32_t col = 0; col < warningCol_; ++col)
	{
		if (!board_->IsEmptyColumn(col))
		{
			return true;
		}
	}

	return false;
}