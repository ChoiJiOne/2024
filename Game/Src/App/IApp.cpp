#include <mimalloc-new-delete.h>

#include "App/IApp.h"
#include "Audio/AudioManager.h"
#include "Crash/CrashManager.h"
#include "Entity/EntityManager.h"
#include "Game/GameManager.h"
#include "GL/GLAssertion.h"
#include "GL/GLManager.h"
#include "GL/RenderManager2D.h"
#include "GLFW/GLFWManager.h"
#include "Scene/SceneManager.h"
#include "Utils/Assertion.h"

IApp* IApp::appPtr_ = nullptr;

IApp::IApp(uint32_t windowWidth, uint32_t windowHeight, const char* windowTitle, const char* windowIcon, bool bIsWindowCentered)
{
	appPtr_ = this;

	/** 앱 내부에서 사용할 매니저들의 포인터 초기화 */
	audioManager_ = AudioManager::GetPtr();
	crashManager_ = CrashManager::GetPtr();
	entityManager_ = EntityManager::GetPtr();
	gameManager_ = GameManager::GetPtr();
	glManager_ = GLManager::GetPtr();
	renderManager_ = RenderManager2D::GetPtr();
	glfwManager_ = GLFWManager::GetPtr();
	sceneManager_ = SceneManager::GetPtr();

	/** 앱 내부에서 사용할 매니저들의 초기화. */
	crashManager_->Startup();
	glfwManager_->Startup(windowWidth, windowHeight, windowTitle, windowIcon, bIsWindowCentered);
	glManager_->Startup();
	renderManager_->Startup();
	audioManager_->Startup();
	gameManager_->Startup();

	/** 루프 종료 이벤트 설정. */
	doneLoopEvent_ = [&]() { bIsDoneLoop_ = true; };
	glfwManager_->AddWindowEventAction(EWindowEvent::CLOSE_WINDOW, doneLoopEvent_, true);

	/** 알파 블랜딩 활성화. */
	glManager_->SetAlphaBlendMode(true);
}

IApp::~IApp()
{
	/** 매니저들의 초기화 해제. */
	gameManager_->Shutdown();
	sceneManager_->Shutdown();
	entityManager_->Shutdown();
	audioManager_->Shutdown();
	renderManager_->Shutdown();
	glManager_->Shutdown();
	glfwManager_->Shutdown();
	crashManager_->Shutdown();

	/** 앱 내부에서 사용할 매니저들의 포인터 해제. */
	sceneManager_ = nullptr;
	glfwManager_ = nullptr;
	renderManager_ = nullptr;
	glManager_ = nullptr;
	gameManager_ = nullptr;
	entityManager_ = nullptr;
	crashManager_ = nullptr;
	audioManager_ = nullptr;

	appPtr_ = nullptr;
}

void IApp::Run()
{
	loopTimer_.Reset();

	appScene_->Enter();
	while (!bIsDoneLoop_)
	{
		loopTimer_.Tick();
		glfwManager_->Tick();

		appScene_->Tick(loopTimer_.GetDeltaSeconds());
		appScene_->Render();

		if (appScene_->IsSceneSwitched())
		{
			appScene_->Exit();
			appScene_ = appScene_->GetSwitchScene();
			appScene_->Enter();
		}
	}
}

void IApp::RequestDoneLoop()
{
	bIsDoneLoop_ = true;
}
