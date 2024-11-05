#include <mimalloc-new-delete.h>
#include <glad/glad.h>

#include <imgui.h>

#include "Entity/EntityManager.h"
#include "GL/GLAssertion.h"
#include "GL/GLManager.h"
#include "GL/RenderManager.h"
#include "GLFW/GLFWManager.h"
#include "Scene/GameDevScene.h"
#include "Scene/SceneManager.h"
#include "Utils/Assertion.h"
#include "Utils/Utils.h"

#include "GameApp.h"

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
	SceneManager::GetRef().Shutdown();
	EntityManager::GetRef().Shutdown();
	RenderManager::GetRef().Shutdown();
	GLManager::GetRef().Shutdown();
	GLFWManager::GetRef().Shutdown();
}

void GameApp::Startup()
{
	currentScene_ = SceneManager::GetRef().Create<GameDevScene>();
}

void GameApp::Run()
{
	currentScene_->Enter();

	while (!glfwWindowShouldClose(window_))
	{
		GLFWManager::GetRef().Tick();

		currentScene_->Tick(0.0f);
		currentScene_->Render();

		if (currentScene_->IsSceneSwitched())
		{
			currentScene_->Exit();
			currentScene_ = currentScene_->GetSwitchScene();
			currentScene_->Enter();
		}
	}
}

void GameApp::Shutdown()
{
	SceneManager::GetRef().Destroy(currentScene_);
}
