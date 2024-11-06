#pragma once

#include <string>

#include <glfw/glfw3.h>

#include "Utils/Macro.h"

/**
 * GLFW ���� ó���� �����ϴ� �Ŵ����Դϴ�.
 * �̶�, �� �Ŵ��� Ŭ������ �̱����Դϴ�.
 */
class GLFWManager
{
public:
	DISALLOW_COPY_AND_ASSIGN(GLFWManager);

	/** GLFW �Ŵ����� �̱��� ��ü �����ڸ� ����ϴ�. */
	static GLFWManager& GetRef();
	
	/** GLFW �Ŵ����� �̱��� ��ü �����͸� ����ϴ�. */
	static GLFWManager* GetPtr();

	/** �ֱٿ� �߻��� GLFW ������ �����մϴ�. */
	void SetLsatError(int32_t code, const char* description);

	/** ���� �߻� ���θ� Ȯ���մϴ�. */
	bool IsDetectError() const { return bIsDetectError_; }

	/** GLFW ������ ���� �ڵ� ���� ����ϴ�. */
	const int32_t GetErrorCode() const { return errorCode_; }

	/** GLFW ������ ���� ������ C ��Ÿ�� ���ڿ��� ����ϴ�. */
	const char* GetErrorDescription() const { return errorDescription_.c_str(); }

	/** GLFW ������ ���� �޽����� C ��Ÿ�� ���ڿ��� ����ϴ�. */
	const char* GetErrorMessage() const { return errorMessage_.c_str(); }

	/** �� �������� �����մϴ�. */
	void Tick();

private:
	/** GameApp���� GLFWManager�� ���ο� ������ �� �ֵ��� ����. */
	friend class GameApp;

	/** GLManager���� GLFWManager�� ���ο� ������ �� �ֵ��� ����. */
	friend class GLManager;
	
	/**
	 * GLFW �Ŵ����� �⺻ �����ڿ� �� ���� �Ҹ����Դϴ�. 
	 * �̱������� �����ϱ� ���� private���� ������ϴ�.
	 */
	GLFWManager() = default;
	virtual ~GLFWManager() {}

	/** GLFW �Ŵ����� �ʱ�ȭ �� ������ GameApp ���ο����� ����˴ϴ�. */
	void Startup(int32_t width, int32_t height, const char* title);
	void Shutdown();
	
private:
	/** GLFW �Ŵ����� �̱��� ��ü�Դϴ�. */
	static GLFWManager singleton_;

	/** GLFW �Ŵ����� �����ϴ� ���� �������Դϴ�. */
	GLFWwindow* mainWindow_ = nullptr;

	/** GLFW �Ŵ����� �����ϴ� ���� �������� ����/���� ũ���Դϴ�. */
	int32_t mainWindowWidth_ = 0;
	int32_t mainWindowHeight_ = 0;

	/** GLFW ���� �߻� �����Դϴ�. */
	bool bIsDetectError_ = false;

	/**
	 * GLFW ���� �ڵ��Դϴ�.
	 * ����: https://www.glfw.org/docs/3.3/group__errors.html
	 */
	int32_t errorCode_ = 0;

	/** GLFW ������ ���� ���� �Դϴ�. */
	std::string errorDescription_;

	/** GLFW ���� �޽����Դϴ�. */
	std::string errorMessage_;
};