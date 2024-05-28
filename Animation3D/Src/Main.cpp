#include <cstdint>
#include <Windows.h>

#if defined(DEBUG_MODE) || defined(RELEASE_MODE) || defined(DEVELOPMENT_MODE)
#include <crtdbg.h>
#endif

#include "CrashModule.h"
#include "GameModule.h"
#include "PlatformModule.h"
#include "RenderModule.h"
#include "GeometryRenderer3D.h"
#include "GLTFLoader.h"
#include "Camera.h"
#include "Pose.h"
#include "SkinnedMesh.h"
#include "Checkboard.h"
#include "Texture2D.h"
#include "MeshRenderer3D.h"
#include "CrossFadeController.h"
#include "Character.h"

void RunApplication()
{
	Camera* camera = GameModule::CreateEntity<Camera>();
	Character* character = GameModule::CreateEntity<Character>();

	GeometryRenderer3D* geometryRenderer = RenderModule::CreateResource<GeometryRenderer3D>();
	MeshRenderer3D* meshRenderer = RenderModule::CreateResource<MeshRenderer3D>();
	
	PlatformModule::RunLoop(
		[&](float deltaSeconds)
		{
			character->Tick(deltaSeconds);
			camera->Tick(deltaSeconds);

			geometryRenderer->SetView(camera->GetView());
			geometryRenderer->SetProjection(camera->GetProjection());
			meshRenderer->SetView(camera->GetView());
			meshRenderer->SetProjection(camera->GetProjection());

			RenderModule::BeginFrame(0.0f, 0.0f, 0.0f, 1.0f);

			geometryRenderer->DrawGrid3D(Vec3f(100.0f, 100.0f, 100.0f), 1.0f);

			std::vector<SkinnedMesh*> meshes = character->GetMeshes();

			for (const auto& mesh : meshes)
			{
				mesh->Skin(&character->GetCrossFadeController().GetSkeleton(), &character->GetCrossFadeController().GetCurrentPose());
				const std::vector<Mat4x4>& bindPose = mesh->GetPosePalette();
				const std::vector<Mat4x4>& invBindPose = character->GetCrossFadeController().GetSkeleton().GetInvBindPose();

				meshRenderer->DrawSkinnedMesh3D(Mat4x4::Identity(), mesh, bindPose, invBindPose, character->GetMaterial());
			}
			
			RenderModule::EndFrame();
		}
	);
}

int32_t WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR pCmdLine, _In_ int32_t nCmdShow)
{
#if defined(DEBUG_MODE) || defined(RELEASE_MODE) || defined(DEVELOPMENT_MODE)
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

	CrashModule::Init();
	PlatformModule::Init(PlatformModule::WindowConstructParams{ L"Animation3D", 100, 100, 1000, 800, false, false });
	RenderModule::Init(PlatformModule::GetWindowHandle());
	GameModule::Init();

	PlatformModule::SetEndLoopCallback([&]() { RenderModule::Uninit(); });

	RenderModule::SetAlphaBlendMode(true);
	RenderModule::SetDepthMode(true);

	RunApplication();

	GameModule::Uninit();
	PlatformModule::Uninit();
	CrashModule::Uninit();
	return 0;
}