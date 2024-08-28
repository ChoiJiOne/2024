#pragma once

#include <functional>

#include "GameError.h"

namespace GameMaker
{
	/**  �������� ũ�� ����� Ǯ ��ũ�� ������ �⺻ ���� false�Դϴ�.  */
	GameError Startup(const char* title, int32_t x, int32_t y, int32_t w, int32_t h, bool bIsResizble = false, bool bIsFullscreen = false);
	GameError Shutdown();

	void RunLoop(const std::function<void(float)>& frameCallback);
}