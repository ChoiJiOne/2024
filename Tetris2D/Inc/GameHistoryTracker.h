#pragma once

#include <list>
#include <string>

#include "IEntity.h"

class GameHistoryTracker : public IEntity
{
public:
	GameHistoryTracker();
	virtual ~GameHistoryTracker();

	DISALLOW_COPY_AND_ASSIGN(GameHistoryTracker);

	virtual void Tick(float deltaSeconds) override;
	virtual void Release() override;

	void AddScore(int32_t score);

private:
	struct Histroy
	{
		std::wstring time;
		int32_t score;
	};

private:
	std::list<Histroy> histories_;
};