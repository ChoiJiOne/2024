#pragma once

#include <array>
#include <functional>
#include <memory>
#include <vector>

#include "Camera2D.h"
#include "GameMath.h"
#include "GameTimer.h"
#include "GameUtils.h"
#include "Macro.h"

class IApp
{
public:
	IApp(const char* title, int32_t x, int32_t y, int32_t w, int32_t h, bool bIsResizble, bool bIsFullscreen);
	virtual ~IApp();

	DISALLOW_COPY_AND_ASSIGN(IApp); /** ��������� ���� ������ �� ���� ������ ���� */

	virtual void Startup() = 0;
	virtual void Shutdown() = 0;
	virtual void Run() = 0;

	static IApp* Get();

protected:
	void RunLoop(const std::function<void(float)>& frameCallback);

protected:
	static IApp* instance_;

	void* window_ = nullptr;

	GameTimer timer_;
};