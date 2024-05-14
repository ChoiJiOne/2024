#include <cstdint>
#include <Windows.h>

#include "Assertion.h"
#include "CrashModule.h"
#include "GameModule.h"
#include "PlatformModule.h"

#include "GeometryRenderer3D.h"
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
	GameModule::Init();

	GeometryRenderer3D* renderer = RenderModule::CreateResource<GeometryRenderer3D>();

	int32_t screenWidth = 0;
	int32_t screenHeight = 0;
	RenderModule::GetScreenSize(screenWidth, screenHeight);
	float aspect = static_cast<float>(screenWidth) / static_cast<float>(screenHeight);

	renderer->SetView(Mat4x4::LookAt(Vec3f(10.0f, 10.0f, 10.0f), Vec3f(0.0f, 0.0f, 0.0f), Vec3f(0.0f, 1.0f, 0.0f)));
	renderer->SetProjection(Mat4x4::Perspective(MathModule::ToRadian(45.0f), aspect, 0.01f, 100.0f));

	PlatformModule::SetEndLoopCallback([&]() { RenderModule::Uninit(); });

	PlatformModule::RunLoop(
		[&](float deltaSeconds)
		{
			RenderModule::BeginFrame(0.0f, 0.0f, 0.0f, 1.0f);

			renderer->DrawGrid3D(Vec3f(100.0f, 100.0f, 100.0f), 1.0f);
			RenderModule::EndFrame();
		}
	);

	GameModule::Uninit();
	PlatformModule::Uninit();
	CrashModule::Uninit();

#if defined(DEBUG_MODE) || defined(RELEASE_MODE) || defined(DEVELOPMENT_MODE)
	CHECK(_CrtCheckMemory());
#endif

	return 0;
}