#include <cstdint>
#include <Windows.h>

#include "Assertion.h"
#include "CrashModule.h"
#include "PlatformModule.h"
#include "RenderModule.h"

int32_t WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR pCmdLine, _In_ int32_t nCmdShow)
{
#if defined(DEBUG_MODE) || defined(RELEASE_MODE) || defined(DEVELOPMENT_MODE)
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

	PlatformModule::WindowConstructParams windowParam{ L"Picking3D", 100, 100, 800, 600, false, false };

	CrashModule::Init();
	PlatformModule::Init(windowParam);
	HWND windowHandle = PlatformModule::GetWindowHandle();

	RenderModule::Init(windowHandle);

	PlatformModule::SetEndLoopCallback([&]() { RenderModule::Uninit(); });

	PlatformModule::RunLoop(
		[&](float deltaSeconds)
		{
			RenderModule::BeginFrame(1.0f, 0.0f, 0.0f, 1.0f);
			RenderModule::EndFrame();
		}
	);

	PlatformModule::Uninit();
	CrashModule::Uninit();

#if defined(DEBUG_MODE) || defined(RELEASE_MODE) || defined(DEVELOPMENT_MODE)
	CHECK(_CrtCheckMemory());
#endif

	return 0;
}