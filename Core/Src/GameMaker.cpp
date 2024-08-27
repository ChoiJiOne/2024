/** ���� ��Ƽ ���̺귯�� ����� ���� ��� ���� ���� */
#include <imgui.h>
#include <imgui_impl_sdl2.h>
#include <imgui_impl_opengl3.h>

#include <SDL2/SDL.h>

#include <mimalloc-new-delete.h>
/** ���� ��Ƽ ���̺귯�� ����� ���� ��� ���� ����*/

#include "GameMaker.h"

bool bIsStartup = false;

GameError GameMaker::Startup()
{
	if (bIsStartup)
	{
		return GameError(ErrorCode::FAILED_STARTUP, "Already startup GameMaker.");
	}

	return GameError(ErrorCode::OK, "Succeed startup GameMaker.");
}

GameError GameMaker::Shutdown()
{
	if (!bIsStartup)
	{
		return GameError(ErrorCode::FAILED_SHUTDOWN, "Startup has not called, or Shutdown has already been invoked.");
	}

	return GameError(ErrorCode::OK, "Succeed shutdown GameMaker.");
}

void GameMaker::RunLoop(const std::function<void(float)>& callback)
{
}
