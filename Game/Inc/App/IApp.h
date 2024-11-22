#pragma once

#include <functional>
#include <memory>

#include "Utils/Macro.h"
#include "Utils/Timer.h"

/** ���ø����̼� �������̽��Դϴ�. */
class IApp
{
public:
	IApp(uint32_t windowWidth, uint32_t windowHeight, const char* windowTitle, bool bIsWindowCentered);
	virtual ~IApp();

	DISALLOW_COPY_AND_ASSIGN(IApp);

	/** ���ø����̼��� �ʱ�ȭ�մϴ�. */
	virtual void Startup() = 0;

	/** ���ø����̼��� �ʱ�ȭ �����մϴ�. */
	virtual void Shutdown() = 0;

	/** ���� ���� �����մϴ�. */
	void Run();

protected:
	/** ���ø����̼��� ���� �����մϴ�. */
	void SetAppScene(class IGameScene* appScene) { appScene_ = appScene; }

protected:
	/** ���� ���� ���� Ÿ�̸��Դϴ�. */
	Timer loopTimer_;

	/** ���� ���� ���� ���� �����Դϴ�. */
	bool bIsDoneLoop_ = false;

	/** ���� ���� ���� ���� �̺�Ʈ�Դϴ�. */
	std::function<void()> doneLoopEvent_ = nullptr;
	
	/** ���� ���ø����̼��� ���Դϴ�. */
	class IGameScene* appScene_ = nullptr;

	/** ���ø����̼� ���� �Ŵ��� �������Դϴ�. */
	class AudioManager* audioManager_ = nullptr;
	class CrashManager* crashManager_ = nullptr;
	class EntityManager* entityManager_ = nullptr;
	class GameManager* gameManager_ = nullptr;
	class GLManager* glManager_ = nullptr;
	class RenderManager2D* renderManager_ = nullptr;
	class GLFWManager* glfwManager_ = nullptr;
	class SceneManager* sceneManager_ = nullptr;
};