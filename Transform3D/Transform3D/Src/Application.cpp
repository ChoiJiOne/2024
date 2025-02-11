#include "GeometryRenderer3D.h"
#include "MeshRenderer.h"

#include "Application.h"
#include "Camera.h"
#include "EntityManager.h"
#include "Grid.h"
#include "Sphere.h"

Application::Application()
{
	PlatformModule::WindowConstructParams windowParam{ L"Transform3D", 100, 100, 1000, 800, false, false };

	CrashModule::Init();
	PlatformModule::Init(windowParam);

	HWND hwnd = PlatformModule::GetWindowHandle();
	RenderModule::Init(hwnd);

	PlatformModule::SetEndLoopCallback([&]() { RenderModule::Uninit(); });
	RenderModule::SetPointSizeMode(true);
	RenderModule::SetAlphaBlendMode(true);
	RenderModule::SetDepthMode(true);
}

Application::~Application()
{
	EntityManager::Get().Shutdown();

	PlatformModule::Uninit();
	CrashModule::Uninit();
}

void Application::Init()
{
	geometryRenderer_ = RenderModule::CreateResource<GeometryRenderer3D>();
	meshRenderer_ = RenderModule::CreateResource<MeshRenderer>();

	EntityManager::Get().Startup();

	camera_ = EntityManager::Get().CreateEntity<Camera>();

	entities_ = 
	{
		camera_,
		EntityManager::Get().CreateEntity<Grid>(geometryRenderer_),
		EntityManager::Get().CreateEntity<Sphere>(meshRenderer_, camera_),
	};
}

void Application::Run()
{
	PlatformModule::RunLoop(
		[&](float deltaSeconds)
		{
			for (auto entity : entities_)
			{
				entity->Tick(deltaSeconds);
			}

			geometryRenderer_->SetView(camera_->GetView());
			geometryRenderer_->SetProjection(camera_->GetProjection());

			meshRenderer_->SetView(camera_->GetView());
			meshRenderer_->SetProjection(camera_->GetProjection());

			RenderModule::SetWindowViewport();
			RenderModule::BeginFrame(0.3f, 0.3f, 0.3f, 1.0f);

			for (auto entity : entities_)
			{
				entity->Render();
			}

			RenderModule::EndFrame();
		}
	);
}