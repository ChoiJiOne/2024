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

	const History& GetRecent() const { return recent_; }
	const History& GetHigh() const { return high_; }
	const std::list<History>& GetHistories() const { return histories_; }
	bool IsHighScoreBroken() const { return bIsHighScoreBroken_; }

private:
	void LoadGameHistoryFile(const std::wstring& path);
	void SaveGameHistoryFile(const std::wstring& path);
	
private:
	std::list<History> histories_;

	History recent_;
	History high_;

	bool bIsHighScoreBroken_ = false;
	bool bSucceedLoadGameHistoryFile_ = false;
};