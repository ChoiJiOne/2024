#pragma once

#include <map>

#include "GameMath.h"
#include "IEntity.h"

class Messenger;
class Board;

class UserState : public IEntity
{
public:
	enum class Level
	{
		LEVEL_1  = 0x01,
		LEVEL_2  = 0x02,
		LEVEL_3  = 0x03,
		LEVEL_4  = 0x04,
		LEVEL_5  = 0x05,
		LEVEL_6  = 0x06,
		LEVEL_7  = 0x07,
		LEVEL_8  = 0x08,
		LEVEL_9  = 0x09,
		LEVEL_10 = 0x0A,
	};

public:
	UserState();
	virtual ~UserState();

	DISALLOW_COPY_AND_ASSIGN(UserState);

	virtual void Tick(float deltaSeconds) override;
	virtual void Release() override;

	void Reset();
	void GainScore(uint32_t removeLines);

	const Level& GetLevel() const { return level_; }
	const int32_t& GetScore() const { return score_; }

private:
	bool IsDetectWarning();
	void UpdateGainScoreMessagePos();
	bool LevelUp(int32_t gainScore);

	void RequestUpdateScoreUI();
	void RequestUpdateLevelUI();

private:
	Messenger* messenger_ = nullptr;
	Board* board_ = nullptr;

	Level level_ = Level::LEVEL_1;
	std::map<Level, float> maxStepTimeLevels_;

	int32_t score_ = 0;
	int32_t scoreScale_ = 0;
	Vec2f gainScoreMessagePos_;
	Vec3f gainScoreMessageColor_;
	float gainScoreMessageTime_ = 0.0f;

	int32_t accumulateGainScore_ = 0;
	int32_t levelUpScore_ = 0;
	Vec2f levelUpMessagePos_;
	Vec3f levelUPMessageColor_;
	float levelUpMessageTime_ = 0.0f;

	bool bEnableWarning_ = false;
	int32_t warningCol_ = 0;
	float warningStepTime_ = 0.0f;
	float maxWarningStepTime_ = 0.5f;
	Vec2f warningMessagePos_;
	Vec3f warningMessageColor_;
};