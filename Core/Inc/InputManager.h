#pragma once

#include "GameMath.h"
#include "Macro.h"

/** �Է� ó���� �����ϴ� �Ŵ����� �̱����Դϴ�. */
class InputManager
{
public:
	DISALLOW_COPY_AND_ASSIGN(InputManager);

	static InputManager& GetRef();
	static InputManager* GetPtr();

private:
	friend class IApp;

	InputManager() = default;
	virtual ~InputManager() {}

	void Startup(); /** IApp ���ο����� ����ϴ� �޼����Դϴ�. */

private:
	static InputManager instance_;
};