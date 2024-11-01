#pragma once

#include <map>

#include <glfw/glfw3.h>

#include "Macro.h"

/**
 * OpenGL �� ������ ���� ó���� �����ϴ� �Ŵ����Դϴ�.
 * �̶�, �� �Ŵ��� Ŭ������ �̱����Դϴ�.
 */
class GLManager
{
public:
	DISALLOW_COPY_AND_ASSIGN(GLManager);

	/** GL �Ŵ����� �̱��� ��ü �����ڸ� ����ϴ�. */
	static GLManager& GetRef();

	/** GL �Ŵ����� �̱��� ��ü �����͸� ����ϴ�. */
	static GLManager* GetPtr();

	/** ������ �������� �����մϴ�. */
	void BeginFrame(float red, float green, float blue, float alpha, float depth = 1.0f, uint8_t stencil = 0);

	/** ������ �������� �����մϴ�. */
	void EndFrame();

	/** ���� �ڵ忡 �����ϴ� ���� �޽����� C ��Ÿ�Ϸ� ����ϴ�. */
	const char* GetErrorMessage(uint32_t code) const;

private:
	/** GameApp���� GLManager�� ���ο� ������ �� �ֵ��� ����. */
	friend class GameApp;

	/**
	 * GL �Ŵ����� �⺻ �����ڿ� �� ���� �Ҹ����Դϴ�.
	 * �̱������� �����ϱ� ���� private���� ������ϴ�.
	 */
	GLManager() = default;
	virtual ~GLManager() {}

	/** GL �Ŵ����� �ʱ�ȭ �� ������ GameApp ���ο����� ����˴ϴ�. */
	void Startup(GLFWwindow* renderTargetWindow);
	void Shutdown();

private:
	/** GL �Ŵ����� �̱��� ��ü�Դϴ�. */
	static GLManager singleton_;

	/** ������ ����� �Ǵ� �������Դϴ�. */
	GLFWwindow* renderTargetWindow_ = nullptr;

	/** OpenGL ���� �ڵ忡 �����ϴ� ���� �޽����Դϴ�. */
	std::map<uint32_t, std::string> errorMessages_;
};