/** ���� ��Ƽ ���̺귯�� */
#include <imgui.h>
#include <imgui_impl_sdl2.h>
#include <imgui_impl_opengl3.h>

#include <SDL2/SDL.h>

#include <mimalloc-new-delete.h>
/** ���� ��Ƽ ���̺귯�� */

#include "GameMaker.h"

GameError GameMaker::Startup()
{
	return GameError(ErrorCode::OK, "");
}

GameError GameMaker::Shutdown()
{
	return GameError(ErrorCode::OK, "");
}

GameError GameMaker::RunLoop(const std::function<void(float)>& callback)
{
	return GameError(ErrorCode::OK, "");
}
