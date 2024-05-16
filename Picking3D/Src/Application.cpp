#include "Assertion.h"
#include "Assertion.h"
#include "Collision.h"
#include "CrashModule.h"
#include "GeometryGenerator.h"
#include "GeometryRenderer3D.h"
#include "PlatformModule.h"
#include "InputController.h"
#include "Mat.h"
#include "MeshRenderer.h"

#include "Application.h"
#include "Camera.h"
#include "Control.h"

Application::Application()
{
	CrashModule::Init();
	PlatformModule::Init(PlatformModule::WindowConstructParams{ L"Picking3D", 100, 100, 1000, 800, false, false });
	RenderModule::Init(PlatformModule::GetWindowHandle());
	GameModule::Init();

	RenderModule::SetVsyncMode(false);
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
	meshRenderer_ = RenderModule::CreateResource<MeshRenderer>();

	camera_ = GameModule::CreateEntity<Camera>();
	control_ = GameModule::CreateEntity<Control>(camera_);

	geometryRenderer_->SetView(camera_->GetView());
	geometryRenderer_->SetProjection(camera_->GetProjection());
	meshRenderer_->SetView(camera_->GetView());
	meshRenderer_->SetProjection(camera_->GetProjection());
}

void Application::Run()
{
	PlatformModule::RunLoop(
		[&](float deltaSeconds)
		{
			control_->Tick(deltaSeconds);
			camera_->Tick(deltaSeconds);

			
			PrepareForRendering();
			RenderModule::BeginFrame(0.0f, 0.0f, 0.0f, 1.0f);

			geometryRenderer_->DrawGrid3D(Vec3f(100.0f, 100.0f, 100.0f), 1.0f);

			RenderModule::EndFrame();
		}
	);
}

void Application::PrepareForRendering()
{
	geometryRenderer_->SetView(camera_->GetView());
	geometryRenderer_->SetProjection(camera_->GetProjection());

	meshRenderer_->SetView(camera_->GetView());
	meshRenderer_->SetProjection(camera_->GetProjection());
}
