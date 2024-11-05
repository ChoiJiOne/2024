#pragma once

#include <string>

#include <glfw/glfw3.h>

#include "Utils/Macro.h"

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

	/** 최근에 발생한 GLFW 에러를 설정합니다. */
	void SetLsatError(int32_t code, const char* description);

	/** 에러 발생 여부를 확인합니다. */
	bool IsDetectError() const { return bIsDetectError_; }

	/** GLFW 에러에 대한 코드 값을 얻습니다. */
	const int32_t GetErrorCode() const { return errorCode_; }

	/** GLFW 에러에 대한 설명을 C 스타일 문자열로 얻습니다. */
	const char* GetErrorDescription() const { return errorDescription_.c_str(); }

	/** GLFW 에러에 대한 메시지를 C 스타일 문자열로 얻습니다. */
	const char* GetErrorMessage() const { return errorMessage_.c_str(); }

	/** 한 프레임을 시작합니다. */
	void Tick();

private:
	/** GameApp에서 GLFWManager의 내부에 접근할 수 있도록 설정. */
	friend class GameApp;

	/** GLManager에서 GLFWManager의 내부에 접근할 수 있도록 설정. */
	friend class GLManager;
	
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

	/** GLFW 매니저가 관리하는 메인 윈도우의 가로/세로 크기입니다. */
	int32_t mainWindowWidth_ = 0;
	int32_t mainWindowHeight_ = 0;

	/** GLFW 에러 발생 여부입니다. */
	bool bIsDetectError_ = false;

	/**
	 * GLFW 에러 코드입니다.
	 * 참조: https://www.glfw.org/docs/3.3/group__errors.html
	 */
	int32_t errorCode_ = 0;

	/** GLFW 에러에 대한 설명 입니다. */
	std::string errorDescription_;

	/** GLFW 에러 메시지입니다. */
	std::string errorMessage_;
};