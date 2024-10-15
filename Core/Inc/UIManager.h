#pragma once

#include "Macro.h"

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
};