#pragma once

#include <memory>

#include <glfw/glfw3.h>

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
	/** GLFW ���� �������� �������Դϴ�. */
	GLFWwindow* window_ = nullptr;

	/** ���� ���� ���� Ÿ�̸��Դϴ�. */
	Timer loopTimer_;
	
	/** ���� ���� ���� ���Դϴ�. */
	class IGameScene* currentScene_ = nullptr;
};