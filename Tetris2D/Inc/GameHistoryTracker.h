#pragma once

#include <list>
#include <string>

#include "IEntity.h"

class GameHistoryTracker : public IEntity
{
public:
	struct History
	{
		std::wstring time;
		int32_t score;
	};

public:
	GameHistoryTracker();
	virtual ~GameHistoryTracker();

	DISALLOW_COPY_AND_ASSIGN(GameHistoryTracker);

	virtual void Tick(float deltaSeconds) override;
	virtual void Release() override;

	void AddScore(int32_t score);

	const int32_t& GetRecentScore() const { return recentScore_; }
	const int32_t& GetHighScore() const { return highScore_; }
	const std::list<History>& GetHistories() const { return histories_; }
	bool IsHighScoreBroken() const { return bIsHighScoreBroken_; }
	
private:
	std::list<History> histories_;
	
	int32_t recentScore_ = 0;
	int32_t highScore_ = -1;
	bool bIsHighScoreBroken_ = false;
};