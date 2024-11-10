#include <mimalloc-new-delete.h>

#include "Audio/AudioManager.h"
#include "Entity/EntityManager.h"
#include "GL/GLAssertion.h"
#include "GL/GLManager.h"
#include "GL/RenderManager2D.h"
#include "GLFW/GLFWManager.h"
#include "Scene/GameDevScene.h"
#include "Scene/SceneManager.h"
#include "Utils/Assertion.h"
#include "Utils/Timer.h"
#include "Utils/Utils.h"

#include "GameApp.h"

const uint32_t WINDOW_WIDTH = 1000;
const uint32_t WINDOW_HEIGHT = 800;

GameApp::GameApp()
{
	GLFWManager::GetRef().Startup(WINDOW_WIDTH, WINDOW_HEIGHT, "HyperCoinDash2D");
	GLManager::GetRef().Startup();
	RenderManager2D::GetRef().Startup();
	AudioManager::GetRef().Startup();

	window_ = GLFWManager::GetRef().mainWindow_;

	/** 알파 블랜딩 활성화. */
	GLManager::GetRef().SetAlphaBlendMode(true);
}

GameApp::~GameApp()
{
	SceneManager::GetRef().Shutdown();
	EntityManager::GetRef().Shutdown();
	AudioManager::GetRef().Shutdown();
	RenderManager2D::GetRef().Shutdown();
	GLManager::GetRef().Shutdown();
	GLFWManager::GetRef().Shutdown();
}

void GameApp::Startup()
{
	currentScene_ = SceneManager::GetRef().Create<GameDevScene>();
}

void GameApp::Run()
{
	loopTimer_.Reset();

	currentScene_->Enter();
	while (!glfwWindowShouldClose(window_))
	{
		loopTimer_.Tick();
		GLFWManager::GetRef().Tick();

		currentScene_->Tick(loopTimer_.GetDeltaSeconds());
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
