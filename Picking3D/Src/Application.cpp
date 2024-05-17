#include <glad/glad.h>

#include "Assertion.h"
#include "GLAssertion.h"
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
#include "Sphere3D.h"

Application::Application()
{
	CrashModule::Init();
	PlatformModule::Init(PlatformModule::WindowConstructParams{ L"Picking3D", 100, 100, 1000, 800, false, false });
	RenderModule::Init(PlatformModule::GetWindowHandle());
	GameModule::Init();

	RenderModule::SetVsyncMode(false);
	RenderModule::SetDepthMode(true);
	RenderModule::SetStencilMode(true);

	GL_FAILED(glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE));

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
	outlineRenderer_ = RenderModule::CreateResource<Shader>("Resource/Shader/MeshRenderer.vert", "Resource/Shader/Outline.frag");

	camera_ = GameModule::CreateEntity<Camera>();
	control_ = GameModule::CreateEntity<Control>(camera_, spheres_);

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
			Update(deltaSeconds);
			Render();
		}
	);
}

void Application::Update(float deltaSeconds)
{
	control_->Tick(deltaSeconds);
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
	PrepareForRendering();
	RenderModule::BeginFrame(0.0f, 0.0f, 0.0f, 1.0f);

	GL_FAILED(glStencilFunc(GL_NOTEQUAL, 1, 0xFF));
	GL_FAILED(glStencilMask(0x00));
	geometryRenderer_->DrawGrid3D(Vec3f(100.0f, 100.0f, 100.0f), 1.0f);

	GL_FAILED(glStencilFunc(GL_ALWAYS, 1, 0xFF));
	GL_FAILED(glStencilMask(0xFF));
	for (auto sphere : spheres_)
	{
		meshRenderer_->DrawMesh(sphere->GetMesh(), Transform::ToMat(sphere->GetTransform()), sphere->GetMaterial());
	}

	Sphere3D* pickSphere = control_->GetPickSphere();
	if (pickSphere)
	{
		GL_FAILED(glStencilFunc(GL_NOTEQUAL, 1, 0xFF));
		GL_FAILED(glStencilMask(0x00));
		RenderModule::SetDepthMode(false);
		{
			outlineRenderer_->Bind();
			outlineRenderer_->SetUniform("view", camera_->GetView());
			outlineRenderer_->SetUniform("projection", camera_->GetProjection());
			outlineRenderer_->SetUniform("outlineColor", Vec4f(1.0f, 0.5f, 0.0f, 1.0f));

			Transform t = pickSphere->GetTransform();
			t.scale = Vec3f(1.05f, 1.05f, 1.05f);

			outlineRenderer_->SetUniform("world", Transform::ToMat(t));

			pickSphere->GetMesh()->Bind();
			RenderModule::ExecuteDrawIndex(pickSphere->GetMesh()->GetIndexCount(), EDrawMode::Triangles);
			pickSphere->GetMesh()->Unbind();

			outlineRenderer_->Unbind();
		}
		RenderModule::SetDepthMode(true);
		GL_FAILED(glStencilFunc(GL_ALWAYS, 1, 0xFF));
		GL_FAILED(glStencilMask(0xFF));
	}

	RenderModule::EndFrame();
}