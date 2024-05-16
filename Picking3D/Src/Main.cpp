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

#include <DirectXMath.h>
#include <DirectXCollision.h>

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
	
	std::vector<Sphere> spheres;
	for (float x = -3.0f; x <= 3.0f; x += 3.0f)
	{
		for (float z = -3.0f; z <= 3.0f; z += 3.0f)
		{
			spheres.push_back(Sphere(Vec3f(x, 0.0f, z), 0.3f));
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

			Ray ray;
			{
				int32_t screenWidth = 0;
				int32_t screenHeight = 0;
				RenderModule::GetScreenSize(screenWidth, screenHeight);
				CursorPos pos = InputController::GetCurrCursorPos();

				// Step1. 3d Normalised Device Coordinates
				float x = (2.0f * static_cast<float>(pos.x)) / static_cast<float>(screenWidth) - 1.0f;
				float y = 1.0f - (2.0f * static_cast<float>(pos.y)) / static_cast<float>(screenHeight);
				float z = 1.0f;
				Vec3f direction(x, y, z);

				// Step2. 4d Homogeneous Clip Coordinates
				Vec4f rayClip = Vec4f(direction.x, direction.y, -1.0f, 1.0f);

				// Step3. 4d Eye (Camera) Coordinates
				Mat4x4 projectInv = Mat4x4::Inverse(camera->GetProjection());
				Vec4f rayEye = Vec4f(
					rayClip.x * projectInv.e00 + rayClip.y * projectInv.e10 + rayClip.z * projectInv.e20 + rayClip.w * projectInv.e30,
					rayClip.x * projectInv.e01 + rayClip.y * projectInv.e11 + rayClip.z * projectInv.e21 + rayClip.w * projectInv.e31,
					rayClip.x * projectInv.e02 + rayClip.y * projectInv.e12 + rayClip.z * projectInv.e22 + rayClip.w * projectInv.e32,
					rayClip.x * projectInv.e03 + rayClip.y * projectInv.e13 + rayClip.z * projectInv.e23 + rayClip.w * projectInv.e33
				);

				rayEye = Vec4f(rayEye.x, rayEye.y, -1.0f, 1.0f);

				// Step 4: 4d World Coordinates
				Mat4x4 viewInv = Mat4x4::Inverse(camera->GetView());
				Vec4f rayWorld4 = Vec4f(
					rayEye.x * viewInv.e00 + rayEye.y * viewInv.e10 + rayEye.z * viewInv.e20 + rayEye.w * viewInv.e30,
					rayEye.x * viewInv.e01 + rayEye.y * viewInv.e11 + rayEye.z * viewInv.e21 + rayEye.w * viewInv.e31,
					rayEye.x * viewInv.e02 + rayEye.y * viewInv.e12 + rayEye.z * viewInv.e22 + rayEye.w * viewInv.e32,
					rayEye.x * viewInv.e03 + rayEye.y * viewInv.e13 + rayEye.z * viewInv.e23 + rayEye.w * viewInv.e33
				);

				Vec3f rayWorld = Vec3f(rayWorld4.x, rayWorld4.y, rayWorld4.z);
				rayWorld = Vec3f::Normalize(rayWorld);
				ray.direction = rayWorld;

				ImGui::Begin("Collision", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse);
				ImGui::SetWindowPos(ImVec2(600.0f, 10.0f));
				ImGui::SetWindowSize(ImVec2(400.0f, 200.0f));
				ImGui::Text("direction : %f, %f, %f", direction.x, direction.y, direction.z);
				ImGui::Text("ray eye : %f, %f, %f", rayEye.x, rayEye.y, rayEye.z);
				ImGui::Text("ray world : %f, %f, %f", rayWorld.x, rayWorld.y, rayWorld.z);
				ImGui::End();
			}

			RenderModule::BeginFrame(0.0f, 0.0f, 0.0f, 1.0f);

			geometryRenderer->DrawGrid3D(Vec3f(100.0f, 100.0f, 100.0f), 1.0f);
			
			ray.origin = camera->eyePosition_;

			for (const auto& sphere : spheres)
			{
				if (Collision::Raycast(ray, sphere))
				{
					geometryRenderer->DrawSphere3D(Mat4x4::Translation(sphere.center), sphere.radius, Vec4f(1.0f, 0.0f, 0.0f, 1.0f));
				}
				else
				{
					geometryRenderer->DrawSphere3D(Mat4x4::Translation(sphere.center), sphere.radius, Vec4f(0.0f, 0.0f, 1.0f, 1.0f));
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