#pragma once

#include <functional>
#include <memory>

#include "Utils/Macro.h"
#include "Utils/Timer.h"

class GameApp
{
public:
	GameApp();
	virtual ~GameApp();

	DISALLOW_COPY_AND_ASSIGN(GameApp);

	/** 게임 앱을 초기화합니다. */
	void Startup();

	/** 게임 앱을 실행합니다. */
	void Run();

	/** 게임 앱을 초기화 해제합니다. */
	void Shutdown();

private:
	/** 게임 앱의 루프 타이머입니다. */
	Timer loopTimer_;

	/** 게임 앱의 루프 종료 여부입니다. */
	bool bIsDoneLoop_ = false;

	/** 게임 앱의 루프 종료 이벤트입니다. */
	std::function<void()> doneLoopEvent_ = nullptr;
	
	/** 현재 게임 앱의 씬입니다. */
	class IGameScene* currentScene_ = nullptr;
};