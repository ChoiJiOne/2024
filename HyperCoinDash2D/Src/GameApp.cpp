#include <glad/glad.h>
#include <mimalloc-new-delete.h>

#include "GameApp.h"
#include "GLFWAssertion.h"
#include "GLFWManager.h"
#include "Utils.h"

const uint32_t WINDOW_WIDTH = 1000;
const uint32_t WINDOW_HEIGHT = 800;

GameApp::GameApp()
{
	GLFWManager::GetRef().Startup(WINDOW_WIDTH, WINDOW_HEIGHT, "HyperCoinDash2D");

	mainWindow_ = GLFWManager::GetRef().mainWindow_;
}

GameApp::~GameApp()
{
	GLFWManager::GetRef().Shutdown();
}

void GameApp::Startup()
{
	glfwMakeContextCurrent(mainWindow_);

	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
}


void GameApp::Run()
{
	while (!glfwWindowShouldClose(mainWindow_))
	{
		glfwPollEvents();
		if (glfwGetKey(mainWindow_, GLFW_KEY_ESCAPE) == GLFW_PRESS)
			glfwSetWindowShouldClose(mainWindow_, true);

		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glfwSwapBuffers(mainWindow_);
	}
}

void GameApp::Shutdown()
{
}
