#pragma once

#include <glfw/glfw3.h>

#include "Macro.h"

class GameApp
{
public:
	GameApp();
	virtual ~GameApp();

	DISALLOW_COPY_AND_ASSIGN(GameApp);

	void Startup();
	void Shutdown();
	void Run();

private:
	GLFWwindow* mainWindow_ = nullptr;
};