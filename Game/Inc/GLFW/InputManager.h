#pragma once

#include <array>

#include "Utils/Macro.h"

/**
 * Ű����, ���콺, ������ �̺�Ʈ �� �Է� ó���� �����ϴ� �Ŵ����Դϴ�.
 * �̶�, �� �Ŵ��� Ŭ������ �̱����Դϴ�.
 */
class InputManager
{
public:
	DISALLOW_COPY_AND_ASSIGN(InputManager);

	/** �Է� ó�� �Ŵ����� �̱��� ��ü �����ڸ� ����ϴ�. */
	static InputManager& GetRef();

	/** �Է� ó�� �Ŵ����� �̱��� ��ü �����͸� ����ϴ�. */
	static InputManager* GetPtr();

private:
	/** GameApp���� �Է� ó�� �Ŵ����� ���ο� ������ �� �ֵ��� ����.  */
	friend class GameApp;

	/** GLFW �Ŵ������� �Է� ó�� �Ŵ����� ���ο� ������ �� �ֵ��� ����. */
	friend class GLFWManager;

	/** 
	 * �Է� ó�� �Ŵ����� �⺻ �����ڿ� ���� �Ҹ����Դϴ�. 
	 * �̱������� �����ϱ� ���� private���� ������ϴ�.
	 */
	InputManager() = default;
	virtual ~InputManager() {}

private:
	/** �Է� ó�� �Ŵ����� �̱��� ��ü�Դϴ�. */
	static InputManager singleton_;
};