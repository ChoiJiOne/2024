#pragma once

#include "IGameScene2D.h"

class GameHistoryScene2D : public IGameScene2D
{
public:
	GameHistoryScene2D();
	virtual ~GameHistoryScene2D();

	DISALLOW_COPY_AND_ASSIGN(GameHistoryScene2D);

	virtual void Enter() override;

private:
	class HistoryViewer* historyViewer_ = nullptr;
};