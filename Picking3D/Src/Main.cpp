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

Vec3f Unproject(const Vec3f& viewportPosition, const Vec2f& viewportOrigin, const Vec2f& viewportSize, const Mat4x4& view, const Mat4x4& projection)
{
	float normalized[4] = 
	{
		(viewportPosition.x - viewportOrigin.x) / viewportSize.x,
		(viewportPosition.y - viewportOrigin.y) / viewportSize.y,
		viewportPosition.z,
		1.0f
	};

	float ndcSpace[4] = { normalized[0], normalized[1], normalized[2], normalized[3] };

	ndcSpace[0] = ndcSpace[0] * 2.0f - 1.0f;
	ndcSpace[1] = 1.0f - ndcSpace[1] * 2.0f;
	ndcSpace[2] = MathModule::Clamp<float>(ndcSpace[2], 0.0f, 1.0f);

	Mat4x4 projectInv = Mat4x4::Inverse(projection);
	Vec4f eyeSpace;
	eyeSpace.x = ndcSpace[0] * projectInv.e00 + ndcSpace[1] * projectInv.e10 + ndcSpace[2] * projectInv.e20 + ndcSpace[3] * projectInv.e30;
	eyeSpace.y = ndcSpace[0] * projectInv.e01 + ndcSpace[1] * projectInv.e11 + ndcSpace[2] * projectInv.e21 + ndcSpace[3] * projectInv.e31;
	eyeSpace.z = ndcSpace[0] * projectInv.e02 + ndcSpace[1] * projectInv.e12 + ndcSpace[2] * projectInv.e22 + ndcSpace[3] * projectInv.e32;
	eyeSpace.w = ndcSpace[0] * projectInv.e03 + ndcSpace[1] * projectInv.e13 + ndcSpace[2] * projectInv.e23 + ndcSpace[3] * projectInv.e33;

	Mat4x4 viewInv = Mat4x4::Inverse(view);
	Vec4f worldSpace;
	worldSpace.x = eyeSpace.x * viewInv.e00 + eyeSpace.y * viewInv.e10 + eyeSpace.z * viewInv.e20 + eyeSpace.w * viewInv.e30;
	worldSpace.y = eyeSpace.x * viewInv.e01 + eyeSpace.y * viewInv.e11 + eyeSpace.z * viewInv.e21 + eyeSpace.w * viewInv.e31;
	worldSpace.z = eyeSpace.x * viewInv.e02 + eyeSpace.y * viewInv.e12 + eyeSpace.z * viewInv.e22 + eyeSpace.w * viewInv.e32;
	worldSpace.w = eyeSpace.x * viewInv.e03 + eyeSpace.y * viewInv.e13 + eyeSpace.z * viewInv.e23 + eyeSpace.w * viewInv.e33;

	if (!MathModule::NearZero(worldSpace.w))
	{
		worldSpace.x /= worldSpace.w;
		worldSpace.y /= worldSpace.w;
		worldSpace.z /= worldSpace.w;
	}

	return Vec3f(worldSpace.x, worldSpace.y, worldSpace.z);
}

Ray GetMouseRay(const Vec2f& mousePos, const Vec2f& viewportOrigin, const Vec2f& viewportSize, const Mat4x4& view, const Mat4x4& projection)
{
	Vec3f nearPosition(mousePos.x, mousePos.y, 0.0f);
	Vec3f farPosition(mousePos.x, mousePos.y, 1.0f);

	Vec3f pNear = Unproject(nearPosition, viewportOrigin, viewportSize, view, projection);
	Vec3f pFar = Unproject(farPosition, viewportOrigin, viewportSize, view, projection);

	Vec3f origin = pNear;
	Vec3f direction = Vec3f::Normalize(pFar - pNear);

	return Ray(origin, direction);
}

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

			int32_t width = 0;
			int32_t height = 0;
			RenderModule::GetScreenSize(width, height);

			CursorPos pos = InputController::GetCurrCursorPos();

			Vec2f mousePos = Vec2f(static_cast<float>(pos.x), static_cast<float>(pos.y));
			Vec2f viewportSize = Vec2f(static_cast<float>(width), static_cast<float>(height));
			Ray ray = GetMouseRay(mousePos, Vec2f(0.0f, 0.0f), viewportSize, camera->GetView(), camera->GetProjection());

			RenderModule::BeginFrame(0.0f, 0.0f, 0.0f, 1.0f);

			geometryRenderer->DrawGrid3D(Vec3f(100.0f, 100.0f, 100.0f), 1.0f);
			
			for (const auto& aabb : aabbs)
			{
				if (Collision::Raycast(ray, aabb))
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