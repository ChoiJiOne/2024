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

void DrawWireframePose(GeometryRenderer3D* geometryRenderer, Pose& pose, float bias)
{
	for (uint32_t index = 0; index < pose.Size(); ++index)
	{
		if (pose.GetParent(index) < 0)
		{
			continue;
		}

		Vec3f pos0 = pose.GetGlobalTransform(index).position;
		Vec3f pos1 = pose.GetGlobalTransform(pose.GetParent(index)).position;
		pos0.x += bias;
		pos1.x += bias;
		geometryRenderer->DrawLine3D(pos0, pos1, Vec4f(1.0f, 0.0f, 0.0f, 1.0f));
	}
}

void RunApplication()
{
	// GLTF 데이터 로딩...
	cgltf_data* data = GLTFLoader::Load("Resource/Model/Kachujin.gltf");
	Skeleton skeleton = GLTFLoader::LoadSkeleton(data);
	std::vector<Clip> clips = GLTFLoader::LoadAnimationClips(data);
	std::vector<GLTFLoader::MeshData> meshData = GLTFLoader::LoadMeshData(data);
	GLTFLoader::Free(data);

	// 메시 리소스 로딩
	std::vector<SkinnedMesh*> meshes;
	for (const auto& mesh : meshData)
	{
		uint32_t size = mesh.positions.size();

		std::vector<VertexPositionNormalUvSkin3D> vertices(size);
		std::vector<uint32_t> indices = mesh.indices;

		for (uint32_t index = 0; index < size; ++index)
		{
			vertices[index].position = mesh.positions[index];
			vertices[index].normal = mesh.normals[index];
			vertices[index].uv = mesh.texcoords[index];
			vertices[index].weight = mesh.weights[index];
			vertices[index].joints = mesh.joints[index];
		}

		meshes.push_back(RenderModule::CreateResource<SkinnedMesh>(vertices, indices, false));
	}

	// 매터리얼 로딩
	//Checkboard* material = RenderModule::CreateResource<Checkboard>(Checkboard::ESize::Size_1024x1024, Checkboard::ESize::Size_32x32, Vec4f(1.0f, 1.0f, 1.0f, 1.0f), Vec4f(1.0f, 0.0f, 0.0f, 1.0f));
	Texture2D* material = RenderModule::CreateResource<Texture2D>("Resource/Texture/Kachujin.png", false);

	// 카메라 엔티티 생성
	Camera* camera = GameModule::CreateEntity<Camera>();

	GeometryRenderer3D* geometryRenderer = RenderModule::CreateResource<GeometryRenderer3D>();
	MeshRenderer3D* meshRenderer = RenderModule::CreateResource<MeshRenderer3D>();

	Pose currentPose = skeleton.GetBindPose();
	float playbackTime = 0.0f;

	PlatformModule::RunLoop(
		[&](float deltaSeconds)
		{
			playbackTime = clips[2].Sample(currentPose, playbackTime + deltaSeconds);

			camera->Tick(deltaSeconds);

			geometryRenderer->SetView(camera->GetView());
			geometryRenderer->SetProjection(camera->GetProjection());
			meshRenderer->SetView(camera->GetView());
			meshRenderer->SetProjection(camera->GetProjection());

			RenderModule::BeginFrame(0.0f, 0.0f, 0.0f, 1.0f);

			geometryRenderer->DrawGrid3D(Vec3f(100.0f, 100.0f, 100.0f), 1.0f);

			for (const auto& mesh : meshes)
			{
				mesh->Skin(&skeleton, &currentPose);
				const std::vector<Mat4x4>& bindPose = mesh->GetPosePalette();
				const std::vector<Mat4x4>& invBindPose = skeleton.GetInvBindPose();

				meshRenderer->DrawSkinnedMesh3D(Mat4x4::Identity(), mesh, bindPose, invBindPose, material);
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