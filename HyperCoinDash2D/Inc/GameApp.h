#pragma once

#include <memory>

#include <glfw/glfw3.h>

#include "Macro.h"

class GameApp
{
public:
	GameApp();
	virtual ~GameApp();

	DISALLOW_COPY_AND_ASSIGN(GameApp);

	void Startup();
	void Run();
	void Shutdown();

private:
	GLFWwindow* mainWindow_ = nullptr;
};