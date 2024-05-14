#include <cstdint>
#include <Windows.h>

#include "Assertion.h"
#include "CrashModule.h"
#include "GameModule.h"
#include "PlatformModule.h"

#include "GeometryRenderer3D.h"
#include "RenderModule.h"

#include "Camera.h"

int32_t WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR pCmdLine, _In_ int32_t nCmdShow)
{
#if defined(DEBUG_MODE) || defined(RELEASE_MODE) || defined(DEVELOPMENT_MODE)
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

	PlatformModule::WindowConstructParams windowParam{ L"Picking3D", 100, 100, 1000, 800, false, false };

	CrashModule::Init();
	PlatformModule::Init(windowParam);
	HWND windowHandle = PlatformModule::GetWindowHandle();

	RenderModule::Init(windowHandle);
	GameModule::Init();

	GeometryRenderer3D* renderer = RenderModule::CreateResource<GeometryRenderer3D>();
	Camera* camera = GameModule::CreateEntity<Camera>();
	
	renderer->SetView(camera->GetView());
	renderer->SetProjection(camera->GetProjection());

	PlatformModule::SetEndLoopCallback([&]() { RenderModule::Uninit(); });

	PlatformModule::RunLoop(
		[&](float deltaSeconds)
		{
			camera->Tick(deltaSeconds);
			renderer->SetView(camera->GetView());
			renderer->SetProjection(camera->GetProjection());

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