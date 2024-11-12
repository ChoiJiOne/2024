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

	/** ���� ���� �ʱ�ȭ�մϴ�. */
	void Startup();

	/** ���� ���� �����մϴ�. */
	void Run();

	/** ���� ���� �ʱ�ȭ �����մϴ�. */
	void Shutdown();

private:
	/** ���� ���� ���� Ÿ�̸��Դϴ�. */
	Timer loopTimer_;

	/** ���� ���� ���� ���� �����Դϴ�. */
	bool bIsDoneLoop_ = false;

	/** ���� ���� ���� ���� �̺�Ʈ�Դϴ�. */
	std::function<void()> doneLoopEvent_ = nullptr;
	
	/** ���� ���� ���� ���Դϴ�. */
	class IGameScene* currentScene_ = nullptr;
};