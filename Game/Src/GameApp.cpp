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

GameApp::GameApp()
{
	const uint32_t windowWidth = 1000;
	const uint32_t windowHeight = 800;
	const char* windowTitle = "HyperCoinDash2D";

	GLFWManager::GetRef().Startup(windowWidth, windowHeight, windowTitle);
	GLManager::GetRef().Startup();
	RenderManager2D::GetRef().Startup();
	AudioManager::GetRef().Startup();

	/** 루프 종료 이벤트 설정. */
	doneLoopEvent_ = [&]() { bIsDoneLoop_ = true; };
	GLFWManager::GetRef().AddWindowEventAction(EWindowEvent::CLOSE_WINDOW, doneLoopEvent_, true);

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

	while (!bIsDoneLoop_)
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
