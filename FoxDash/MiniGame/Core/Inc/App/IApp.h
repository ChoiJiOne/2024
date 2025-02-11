#pragma once

#include <functional>
#include <memory>

#include "Utils/Macro.h"
#include "Utils/Timer.h"

/**
 * 애플리케이션 인터페이스입니다.
 * 이때, 이 인터페이스를 상속받은 앱 클래스는 단 하나만 존재할 수 있습니다.
 */
class IApp
{
public:
	IApp(uint32_t windowWidth, uint32_t windowHeight, const char* windowTitle, const char* windowIcon, bool bIsWindowCentered);
	virtual ~IApp();

	DISALLOW_COPY_AND_ASSIGN(IApp);

	/** 애플리케이션을 초기화합니다. */
	virtual void Startup() = 0;

	/** 애플리케이션을 초기화 해제합니다. */
	virtual void Shutdown() = 0;

	/** 게임 앱을 실행합니다. */
	void Run();

	/** 강제 루프 종료를 요청합니다. */
	void RequestDoneLoop();

	/** 애플리케이션 앱의 포인터를 얻습니다. */
	static IApp* GetPtr() { return appPtr_; }

protected:
	/** 애플리케이션의 씬을 설정합니다. */
	void SetAppScene(class IGameScene* appScene) { appScene_ = appScene; }

protected:
	/** 애플리케이션 앱의 정적 포인터입니다. */
	static IApp* appPtr_;

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
	class GLManager* glManager_ = nullptr;
	class RenderManager2D* renderManager_ = nullptr;
	class GLFWManager* glfwManager_ = nullptr;
	class SceneManager* sceneManager_ = nullptr;
};