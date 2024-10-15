#pragma once

#include "Macro.h"

class Camera2D;

/** UI �Ŵ����� �̱����Դϴ�. */
class UIManager
{
public:
	DISALLOW_COPY_AND_ASSIGN(UIManager);

	static UIManager& Get();

private:
	friend class IApp;

	UIManager() = default;
	virtual ~UIManager() {}

	void Startup(); /** IApp ���ο����� ȣ���ؾ� �մϴ�. */
	void Shutdown(); /** IApp ���ο����� ȣ���ؾ� �մϴ�. */

private:
	Camera2D* uiCamera_ = nullptr;
};