#pragma once

#include <string>

#include <glfw/glfw3.h>

#include "Macro.h"

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
	void SetLsatError(int32_t code, const char* message);

	/** ���� �߻� ���θ� Ȯ���մϴ�. */
	bool IsDetectError() const { return bIsDetectError_; }

private:
	/** GameApp���� GLFWManager�� ���ο� ������ �� �ֵ��� ����. */
	friend class GameApp;
	
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

	/** GLFW ���� �߻� �����Դϴ�. */
	bool bIsDetectError_ = false;

	/**
	 * GLFW ���� �ڵ��Դϴ�.
	 * ����: https://www.glfw.org/docs/3.3/group__errors.html
	 */
	int32_t errorCode_ = 0;

	/** GLFW ���� �޽����Դϴ�. */
	std::string errorMessage_;
};