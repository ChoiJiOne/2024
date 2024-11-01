#pragma once

#include <cstdint>

#include <glfw/glfw3.h>

#include "Macro.h"

/**
 * GLFW 관련 처리를 수행하는 매니저입니다.
 * 이때, 이 매니저 클래스는 싱글턴입니다.
 */
class GLFWManager
{
public:
	DISALLOW_COPY_AND_ASSIGN(GLFWManager);

	/** GLFW 매니저의 싱글턴 객체 참조자를 얻습니다. */
	static GLFWManager& GetRef();
	
	/** GLFW 매니저의 싱글턴 객체 포인터를 얻습니다. */
	static GLFWManager* GetPtr();

private:
	/** GameApp에서 GLFWManager의 내부에 접근할 수 있도록 설정. */
	friend class GameApp;
	
	/**
	 * GLFW 매니저의 기본 생성자와 빈 가상 소멸자입니다. 
	 * 싱글턴으로 구현하기 위해 private으로 숨겼습니다.
	 */
	GLFWManager() = default;
	virtual ~GLFWManager() {}

	/** GLFW 매니저의 초기화 및 해제는 GameApp 내부에서만 수행됩니다. */
	void Startup(int32_t width, int32_t height, const char* title);
	void Shutdown();
	
private:
	/** GLFW 매니저의 싱글턴 객체입니다. */
	static GLFWManager singleton_;

	/** GLFW 매니저가 관리하는 메인 윈도우입니다. */
	GLFWwindow* mainWindow_ = nullptr;
};