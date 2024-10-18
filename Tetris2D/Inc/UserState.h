#pragma once

#include "GameMath.h"
#include "IEntity.h"

class Messenger;
class Board;

class UserState : public IEntity
{
public:
	UserState();
	virtual ~UserState();

	DISALLOW_COPY_AND_ASSIGN(UserState);

	virtual void Tick(float deltaSeconds) override;
	virtual void Release() override;

	void Reset();
	void GainScore(uint32_t removeLines);

private:
	bool IsDetectWarning();

private:
	Messenger* messenger_ = nullptr;
	Board* board_ = nullptr;

	int32_t level_ = 0;

	int32_t score_ = 0;
	int32_t scoreScale_ = 0;
	Vec2f gainScoreMessagePos_;
	Vec3f gainScoreMessageColor_;
	float gainScoreMessageTime_ = 0.0f;

	bool bEnableWarning_ = false;
	int32_t warningCol_ = 0;
	float warningStepTime_ = 0.0f;
	float maxWarningStepTime_ = 0.5f;
	Vec2f warningMessagePos_;
	Vec3f warningMessageColor_;
};