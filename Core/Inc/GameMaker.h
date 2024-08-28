#pragma once

#include <functional>

#include "GameError.h"
#include "GameMath.h"

namespace GameMaker
{

/**  �������� ũ�� ����� Ǯ ��ũ�� ������ �⺻ ���� false�Դϴ�.  */
GameError Startup(const char* title, int32_t x, int32_t y, int32_t w, int32_t h, bool bIsResizble = false, bool bIsFullscreen = false);
GameError Shutdown();

void RunLoop(const std::function<void(float)>& frameCallback);

int32_t GetNumVideoDisplay();
GameError GetVideoDisplaySize(int32_t index, GameMath::Vec2i& outSize);

template <typename T>
void GetScreenSize(T& outWidth, T& outHeight);

}