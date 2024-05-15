#include <cstdint>
#include <Windows.h>

#include <imgui.h>

#include "Assertion.h"
#include "CrashModule.h"
#include "GameModule.h"
#include "PlatformModule.h"

#include "Checkboard.h"
#include "GeometryGenerator.h"
#include "GeometryRenderer3D.h"
#include "MeshRenderer.h"
#include "RenderModule.h"

#include "Camera.h"
#include "Control.h"

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
	RenderModule::SetVsyncMode(false);
	GameModule::Init();

	Checkboard* checkboard = RenderModule::CreateResource<Checkboard>(Checkboard::ESize::Size_1024x1024, Checkboard::ESize::Size_64x64, Vec4f(1.0f, 1.0f, 1.0f, 1.0f), Vec4f(1.0f, 0.0f, 0.0f, 1.0f));
	GeometryRenderer3D* geometryRenderer = RenderModule::CreateResource<GeometryRenderer3D>();
	MeshRenderer* meshRenderer = RenderModule::CreateResource<MeshRenderer>();
	
	std::vector<VertexPositionNormalUv3D> vertices;
	std::vector<uint32_t> indices;
	GeometryGenerator::CreateSphere(1.0f, 40, vertices, indices);

	StaticMesh<VertexPositionNormalUv3D>* mesh = RenderModule::CreateResource<StaticMesh<VertexPositionNormalUv3D>>(vertices, indices);

	Camera* camera = GameModule::CreateEntity<Camera>();
	Control* control = GameModule::CreateEntity<Control>(camera);

	geometryRenderer->SetView(camera->GetView());
	geometryRenderer->SetProjection(camera->GetProjection());
	meshRenderer->SetView(camera->GetView());
	meshRenderer->SetProjection(camera->GetProjection());

	PlatformModule::SetEndLoopCallback([&]() { RenderModule::Uninit(); });
	
	PlatformModule::RunLoop(
		[&](float deltaSeconds)
		{
			control->Tick(deltaSeconds);
			camera->Tick(deltaSeconds);

			geometryRenderer->SetView(camera->GetView());
			geometryRenderer->SetProjection(camera->GetProjection());
			meshRenderer->SetView(camera->GetView());
			meshRenderer->SetProjection(camera->GetProjection());

			RenderModule::BeginFrame(0.0f, 0.0f, 0.0f, 1.0f);

			geometryRenderer->DrawGrid3D(Vec3f(100.0f, 100.0f, 100.0f), 1.0f);

			//for (float x = -50.0f; x <= 50.0f; x += 1.0f)
			//{
			//	for (float z = -50.0f; z <= 50.0f; z += 1.0f)
			//	{
			//		Mat4x4 world = Mat4x4::Translation(x, 0.0f, z) * Mat4x4::Scale(0.5f, 0.5f, 0.5f);
			//		meshRenderer->DrawMesh(mesh, world, checkboard);
			//	}
			//}

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