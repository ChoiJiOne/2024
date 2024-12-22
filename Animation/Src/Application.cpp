#include "Application.h"
#include "Camera.h"
#include "Character.h"
#include "GeometryRenderer3D.h"
#include "MeshRenderer3D.h"

Application::Application()
{
	CrashModule::Init();
	PlatformModule::Init(PlatformModule::WindowConstructParams{ L"Animation3D", 100, 100, 1000, 800, false, false });
	RenderModule::Init(PlatformModule::GetWindowHandle());
	GameModule::Init();

	RenderModule::SetVsyncMode(false);
	RenderModule::SetAlphaBlendMode(true);
	RenderModule::SetDepthMode(true);

	PlatformModule::SetEndLoopCallback([&]() { RenderModule::Uninit(); });
}

Application::~Application()
{
	GameModule::Uninit();
	PlatformModule::Uninit();
	CrashModule::Uninit();
}

void Application::Init()
{
	geometryRenderer_ = RenderModule::CreateResource<GeometryRenderer3D>();
	meshRenderer_ = RenderModule::CreateResource<MeshRenderer3D>();

	camera_ = GameModule::CreateEntity<Camera>();
	character_ = GameModule::CreateEntity<Character>(camera_);
}

void Application::Run()
{
	PlatformModule::RunLoop(
		[&](float deltaSeconds)
		{
			Update(deltaSeconds);
			PrepareForRendering();
			Render();
		}
	);
}

void Application::Update(float deltaSeconds)
{
	character_->Tick(deltaSeconds);
	camera_->Tick(deltaSeconds);
}

void Application::PrepareForRendering()
{
	geometryRenderer_->SetView(camera_->GetView());
	geometryRenderer_->SetProjection(camera_->GetProjection());
	meshRenderer_->SetView(camera_->GetView());
	meshRenderer_->SetProjection(camera_->GetProjection());
}

void Application::Render()
{
	RenderModule::BeginFrame(0.0f, 0.0f, 0.0f, 1.0f);

	geometryRenderer_->DrawGrid3D(Vec3f(100.0f, 100.0f, 100.0f), 1.0f);

	std::vector<SkinnedMesh*> meshes = character_->GetMeshes();

	for (const auto& mesh : meshes)
	{
		mesh->Skin(&character_->GetCrossFadeController().GetSkeleton(), &character_->GetCrossFadeController().GetCurrentPose());
		const std::vector<Mat4x4>& bindPose = mesh->GetPosePalette();
		const std::vector<Mat4x4>& invBindPose = character_->GetCrossFadeController().GetSkeleton().GetInvBindPose();
		meshRenderer_->DrawSkinnedMesh3D(Mat4x4::Identity(), mesh, bindPose, invBindPose, character_->GetMaterial());
	}

	RenderModule::EndFrame();
}