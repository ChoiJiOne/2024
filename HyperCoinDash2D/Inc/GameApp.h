#pragma once

#include <memory>

#include <glfw/glfw3.h>

#include "Utils/Macro.h"

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
	/** GLFW 메인 윈도우의 포인터입니다. */
	GLFWwindow* window_ = nullptr;
	
	/** 현재 게임 앱의 씬입니다. */
	class IGameScene* currentScene_ = nullptr;
};