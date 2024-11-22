#pragma once

#include <functional>
#include <memory>

#include "Utils/Macro.h"
#include "Utils/Timer.h"

/** 애플리케이션 인터페이스입니다. */
class IApp
{
public:
	IApp(uint32_t windowWidth, uint32_t windowHeight, const char* windowTitle, bool bIsWindowCentered);
	virtual ~IApp();

	DISALLOW_COPY_AND_ASSIGN(IApp);

	/** 애플리케이션을 초기화합니다. */
	virtual void Startup() = 0;

	/** 애플리케이션을 초기화 해제합니다. */
	virtual void Shutdown() = 0;

	/** 게임 앱을 실행합니다. */
	void Run();

protected:
	/** 애플리케이션의 씬을 설정합니다. */
	void SetAppScene(class IGameScene* appScene) { appScene_ = appScene; }

protected:
	/** 게임 앱의 루프 타이머입니다. */
	Timer loopTimer_;

	/** 게임 앱의 루프 종료 여부입니다. */
	bool bIsDoneLoop_ = false;

	/** 게임 앱의 루프 종료 이벤트입니다. */
	std::function<void()> doneLoopEvent_ = nullptr;
	
	/** 현재 애플리케이션의 씬입니다. */
	class IGameScene* appScene_ = nullptr;

	/** 애플리케이션 내의 매니저 포인터입니다. */
	class AudioManager* audioManager_ = nullptr;
	class CrashManager* crashManager_ = nullptr;
	class EntityManager* entityManager_ = nullptr;
	class GameManager* gameManager_ = nullptr;
	class GLManager* glManager_ = nullptr;
	class RenderManager2D* renderManager_ = nullptr;
	class GLFWManager* glfwManager_ = nullptr;
	class SceneManager* sceneManager_ = nullptr;
};