#include <cstdint>
#include <Windows.h>

#if defined(DEBUG_MODE) || defined(RELEASE_MODE) || defined(DEVELOPMENT_MODE)
#include <crtdbg.h>
#endif

#include <SDL2/SDL.h>

#include "GameEngine.h"
#include "GameTimer.h"
#include "GameMath.h"
#include "InputManager.h"
#include "RenderManager.h"
#include "FileUtils.h"

int32_t WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR pCmdLine, _In_ int32_t nCmdShow)
{
#if defined(DEBUG_MODE) || defined(RELEASE_MODE) || defined(DEVELOPMENT_MODE)
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

	GameMaker::InputManager& manager = GameMaker::InputManager::Get();

	manager.AddWindowEventAction(GameMaker::EWindowEvent::MOVED, [&]() { SDL_Log("MOVED"); });
	manager.AddWindowEventAction(GameMaker::EWindowEvent::FOCUS_LOST, [&]() { SDL_Log("FOCUS_LOST"); });
	manager.AddWindowEventAction(GameMaker::EWindowEvent::LEAVE, [&]() { SDL_Log("LEAVE"); });
	manager.AddWindowEventAction(GameMaker::EWindowEvent::RESIZED, [&]() { SDL_Log("RESIZED"); });
	manager.AddWindowEventAction(GameMaker::EWindowEvent::SIZE_CHANGED, [&]() { SDL_Log("SIZE_CHANGED"); });
	manager.AddWindowEventAction(GameMaker::EWindowEvent::CLOSE, [&]() { 
		SDL_Log("CLOSE"); 
		});

	GameMaker::FileUtils::MakeDirectory("Test");

	GameMaker::GameEngine::Init();
	GameMaker::GameEngine::RunLoop(
		[&](float deltaSeconds) 
		{
			GameMaker::RenderManager::Get().BeginFrame(1.0f, 0.0f, 0.0f, 1.0f);
			GameMaker::RenderManager::Get().EndFrame();

		}
	);
	GameMaker::GameEngine::Shutdown();

	return 0;
}