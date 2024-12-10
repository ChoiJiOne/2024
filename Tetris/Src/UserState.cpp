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
	maxStepTimeLevels_ =
	{
		{ Level::LEVEL_1,  1.0f },
		{ Level::LEVEL_2,  0.9f },
		{ Level::LEVEL_3,  0.8f },
		{ Level::LEVEL_4,  0.7f },
		{ Level::LEVEL_5,  0.6f },
		{ Level::LEVEL_6,  0.5f },
		{ Level::LEVEL_7,  0.4f },
		{ Level::LEVEL_8,  0.3f },
		{ Level::LEVEL_9,  0.2f },
		{ Level::LEVEL_10, 0.1f },
	};

	score_ = 0;
	scoreScale_ = 10;
	gainScoreMessagePos_ = board_->bound_.center - Vec2f(0.65f * static_cast<float>(board_->row_) * board_->cellSize_, 0.0f);
	gainScoreMessageColor_ = Vec3f(1.0f, 1.0f, 1.0f);
	gainScoreMessageTime_ = 2.0f;

	bEnableWarning_ = false;
	warningCol_ = 3;
	warningStepTime_ = 0.0f;
	maxWarningStepTime_ = 0.5f;
	warningMessagePos_ = board_->bound_.center + Vec2f(0.0f, 0.55f * static_cast<float>(board_->col_) * board_->cellSize_);
	warningMessageColor_ = Vec3f(1.0f, 0.0f, 0.0f);

	levelUpScore_ = 100;
	levelUpMessagePos_ = Vec2f(195.0f, -200.0f);
	levelUPMessageColor_ = Vec3f(1.0f, 1.0f, 1.0f);
	levelUpMessageTime_ = 2.0f;

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
	accumulateGainScore_ = 0;
	
	RequestUpdateScoreUI();
	RequestUpdateLevelUI();

	Tetromino::SetMaxMoveStepTime(maxStepTimeLevels_.at(level_));
}

void UserState::GainScore(uint32_t removeLines)
{
	UpdateGainScoreMessagePos();

	int32_t gainScore = scoreScale_ * removeLines;
	messenger_->Send(GameUtils::PrintF(L"+%d", gainScore), gainScoreMessagePos_, gainScoreMessageColor_, gainScoreMessageTime_);
	
	score_ += gainScore;
	RequestUpdateScoreUI();

	if (LevelUp(gainScore))
	{
		messenger_->Send(L"LEVEL UP!", levelUpMessagePos_, levelUPMessageColor_, levelUpMessageTime_);
		RequestUpdateLevelUI();
	}
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

void UserState::UpdateGainScoreMessagePos()
{
	for (uint32_t col = 0; col < board_->col_; ++col)
	{
		if (board_->removeColumn_[col])
		{
			gainScoreMessagePos_.x = board_->bound_.center.x;
			gainScoreMessagePos_.y = board_->CalculateCellPos(0, col).y;
			break;
		}
	}
}

bool UserState::LevelUp(int32_t gainScore)
{
	if (level_ >= Level::LEVEL_10)
	{
		return false;
	}

	accumulateGainScore_ += gainScore;
	if (accumulateGainScore_ < levelUpScore_)
	{
		return false;
	}
	
	accumulateGainScore_ -= levelUpScore_;
	int32_t level = static_cast<int32_t>(level_);
	level_ = static_cast<Level>(level + 1);
	Tetromino::SetMaxMoveStepTime(maxStepTimeLevels_.at(level_));

	return true;
}

void UserState::RequestUpdateScoreUI()
{
	PanelUI* scoreUI = EntityManager::GetRef().GetByName<PanelUI>("Score");
	scoreUI->SetText(GameUtils::PrintF(L"%d", score_));
}

void UserState::RequestUpdateLevelUI()
{
	PanelUI* levelUI = EntityManager::GetRef().GetByName<PanelUI>("Level");
	levelUI->SetText(GameUtils::PrintF(L"%d", static_cast<int32_t>(level_)));
}
