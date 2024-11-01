#pragma once

#include <map>

#include <glfw/glfw3.h>

#include "Macro.h"

/**
 * OpenGL 및 렌더링 관련 처리를 수행하는 매니저입니다.
 * 이때, 이 매니저 클래스는 싱글턴입니다.
 */
class GLManager
{
public:
	DISALLOW_COPY_AND_ASSIGN(GLManager);

	/** GL 매니저의 싱글턴 객체 참조자를 얻습니다. */
	static GLManager& GetRef();

	/** GL 매니저의 싱글턴 객체 포인터를 얻습니다. */
	static GLManager* GetPtr();

	/** 프레임 렌더링을 시작합니다. */
	void BeginFrame(float red, float green, float blue, float alpha, float depth = 1.0f, uint8_t stencil = 0);

	/** 프레임 렌더링을 종료합니다. */
	void EndFrame();

	/** 에러 코드에 대응하는 에러 메시지를 C 스타일로 얻습니다. */
	const char* GetErrorMessage(uint32_t code) const;

private:
	/** GameApp에서 GLManager의 내부에 접근할 수 있도록 설정. */
	friend class GameApp;

	/**
	 * GL 매니저의 기본 생성자와 빈 가상 소멸자입니다.
	 * 싱글턴으로 구현하기 위해 private으로 숨겼습니다.
	 */
	GLManager() = default;
	virtual ~GLManager() {}

	/** GL 매니저의 초기화 및 해제는 GameApp 내부에서만 수행됩니다. */
	void Startup(GLFWwindow* renderTargetWindow);
	void Shutdown();

private:
	/** GL 매니저의 싱글턴 객체입니다. */
	static GLManager singleton_;

	/** 렌더링 대상이 되는 윈도우입니다. */
	GLFWwindow* renderTargetWindow_ = nullptr;

	/** OpenGL 에러 코드에 대응하는 에러 메시지입니다. */
	std::map<uint32_t, std::string> errorMessages_;
};