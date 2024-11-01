#include <mimalloc-new-delete.h>
#include <glad/glad.h>

#include "GL/GLAssertion.h"
#include "GL/GLManager.h"
#include "GLFW/GLFWManager.h"
#include "Assertion.h"
#include "GameApp.h"
#include "Utils.h"

const uint32_t WINDOW_WIDTH = 1000;
const uint32_t WINDOW_HEIGHT = 800;

GameApp::GameApp()
{
	window_ = GLFWManager::GetRef().Startup(WINDOW_WIDTH, WINDOW_HEIGHT, "HyperCoinDash2D");
	GLManager::GetRef().Startup(window_);
}

GameApp::~GameApp()
{
	GLManager::GetRef().Shutdown();
	GLFWManager::GetRef().Shutdown();
}

void GameApp::Startup()
{
}

void GameApp::Run()
{
	while (!glfwWindowShouldClose(window_))
	{
		glfwPollEvents();
		if (glfwGetKey(window_, GLFW_KEY_ESCAPE) == GLFW_PRESS)
			glfwSetWindowShouldClose(window_, true);

		GLManager::GetRef().BeginFrame(1.0f, 0.0f, 0.0f, 1.0f);
		GLManager::GetRef().EndFrame();
	}
}

void GameApp::Shutdown()
{
}
