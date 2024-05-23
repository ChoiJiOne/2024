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

void RunApplication()
{
	cgltf_data* data = GLTFLoader::Load("Resource/Model/Kachujin.gltf");
	Pose restPose = GLTFLoader::LoadRestPose(data);
	Pose currentPose = restPose;
	std::vector<Clip> clips = GLTFLoader::LoadAnimationClips(data);
	GLTFLoader::Free(data);

	Camera* camera = GameModule::CreateEntity<Camera>();

	GeometryRenderer3D* geometryRenderer = RenderModule::CreateResource<GeometryRenderer3D>();
	geometryRenderer->SetView(camera->GetView());
	geometryRenderer->SetProjection(camera->GetProjection());

	float playbackTime = 0.0f;

	PlatformModule::RunLoop(
		[&](float deltaSeconds)
		{
			playbackTime = clips[1].Sample(currentPose, playbackTime + deltaSeconds);

			camera->Tick(deltaSeconds);

			geometryRenderer->SetView(camera->GetView());
			geometryRenderer->SetProjection(camera->GetProjection());

			RenderModule::BeginFrame(0.0f, 0.0f, 0.0f, 1.0f);

			geometryRenderer->DrawGrid3D(Vec3f(100.0f, 100.0f, 100.0f), 1.0f);

			for (uint32_t index = 0; index < currentPose.Size(); ++index)
			{
				if (currentPose.GetParent(index) < 0)
				{
					continue;
				}

				Vec3f pos0 = currentPose.GetGlobalTransform(index).position;
				Vec3f pos1 = currentPose.GetGlobalTransform(currentPose.GetParent(index)).position;
				geometryRenderer->DrawLine3D(pos0, pos1, Vec4f(1.0f, 0.0f, 0.0f, 1.0f));
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