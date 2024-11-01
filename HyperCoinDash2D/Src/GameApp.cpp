#include <glad/glad.h>
#include <mimalloc-new-delete.h>

#include "GameApp.h"

const uint32_t WINDOW_WIDTH = 1000;
const uint32_t WINDOW_HEIGHT = 800;

GameApp::GameApp()
{
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

GameApp::~GameApp()
{
	glfwTerminate();
}

void GameApp::Startup()
{
	mainWindow_ = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "HyperCoinDash2D", nullptr, nullptr);

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
	glfwDestroyWindow(mainWindow_);
	mainWindow_ = nullptr;
}
