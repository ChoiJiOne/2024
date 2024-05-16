#include <cstdint>
#include <Windows.h>

#include <glad/glad.h>
#include <imgui.h>

#include "Assertion.h"
#include "CrashModule.h"
#include "GameModule.h"
#include "PlatformModule.h"
#include "InputController.h"

#include "Collision.h"

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

	CrashModule::Init();
	PlatformModule::Init(PlatformModule::WindowConstructParams{ L"Picking3D", 100, 100, 1000, 800, false, false });
	RenderModule::Init(PlatformModule::GetWindowHandle());
	GameModule::Init();

	RenderModule::SetVsyncMode(false);
	RenderModule::SetDepthMode(true);

	std::vector<VertexPositionNormalUv3D> vertices;
	std::vector<uint32_t> indices;
	GeometryGenerator::CreateSphere(1.0f, 40, vertices, indices);

	StaticMesh<VertexPositionNormalUv3D>* mesh = RenderModule::CreateResource<StaticMesh<VertexPositionNormalUv3D>>(vertices, indices);
	Checkboard* checkboard = RenderModule::CreateResource<Checkboard>(Checkboard::ESize::Size_1024x1024, Checkboard::ESize::Size_64x64, Vec4f(1.0f, 1.0f, 1.0f, 1.0f), Vec4f(1.0f, 0.0f, 0.0f, 1.0f));
	GeometryRenderer3D* geometryRenderer = RenderModule::CreateResource<GeometryRenderer3D>();
	MeshRenderer* meshRenderer = RenderModule::CreateResource<MeshRenderer>();
	
	Camera* camera = GameModule::CreateEntity<Camera>();
	Control* control = GameModule::CreateEntity<Control>(camera);

	geometryRenderer->SetView(camera->GetView());
	geometryRenderer->SetProjection(camera->GetProjection());
	meshRenderer->SetView(camera->GetView());
	meshRenderer->SetProjection(camera->GetProjection());

	PlatformModule::SetEndLoopCallback([&]() { RenderModule::Uninit(); });
	
	std::vector<AABB> aabbs;
	for (float x = -3.0f; x <= 3.0f; x += 3.0f)
	{
		for (float z = -3.0f; z <= 3.0f; z += 3.0f)
		{
			aabbs.push_back(AABB(Vec3f(x, 0.0f, z), Vec3f(0.5f, 0.5f, 0.5f)));
		}
	}

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
			
			for (const auto& aabb : aabbs)
			{
				if (Collision::Raycast(camera->GetMouseRay(), aabb))
				{
					geometryRenderer->DrawCube3D(Mat4x4::Translation(aabb.center), aabb.extents, Vec4f(1.0f, 0.0f, 0.0f, 1.0f));
				}
				else
				{
					geometryRenderer->DrawCube3D(Mat4x4::Translation(aabb.center), aabb.extents, Vec4f(0.0f, 0.0f, 1.0f, 1.0f));
				}
			}

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