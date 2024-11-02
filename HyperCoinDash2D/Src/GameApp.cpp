#include <mimalloc-new-delete.h>
#include <glad/glad.h>

#include <imgui.h>

#include "GL/GLAssertion.h"
#include "GL/GLManager.h"
#include "GL/RenderManager.h"
#include "GLFW/GLFWManager.h"
#include "Assertion.h"
#include "GameApp.h"
#include "Utils.h"

const uint32_t WINDOW_WIDTH = 1000;
const uint32_t WINDOW_HEIGHT = 800;

GameApp::GameApp()
{
	GLFWManager::GetRef().Startup(WINDOW_WIDTH, WINDOW_HEIGHT, "HyperCoinDash2D");
	GLManager::GetRef().Startup();
	RenderManager::GetRef().Startup();

	window_ = GLFWManager::GetRef().mainWindow_;
}

GameApp::~GameApp()
{
	RenderManager::GetRef().Shutdown();
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
		GLFWManager::GetRef().BeginTick();
		{
			// 게임 로직 업데이트.
			{
				ImGui::Begin("TEST");
				ImGui::Text("Hello ImGui!");
				ImGui::End();
			}

			// 렌더링.
			GLManager::GetRef().BeginFrame(0.0f, 0.0f, 0.0f, 1.0f);
			{

			}
			GLManager::GetRef().EndFrame();
		}
		GLFWManager::GetRef().EndTick();
	}
}

void GameApp::Shutdown()
{
}
