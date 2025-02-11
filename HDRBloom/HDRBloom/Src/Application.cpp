#include <imgui.h>

#include "Application.h"

Application::Application()
{
	PlatformModule::WindowConstructParams windowParam{ L"HDRBloom", 100, 100, 1000, 800, false, false };

	CrashModule::Init();
	PlatformModule::Init(windowParam);

	HWND hwnd = PlatformModule::GetWindowHandle();
	RenderModule::Init(hwnd);

	PlatformModule::SetEndLoopCallback([&]() { RenderModule::Uninit(); });
	RenderModule::SetPointSizeMode(true);
	RenderModule::SetAlphaBlendMode(true);
}

Application::~Application()
{
	PlatformModule::Uninit();
	CrashModule::Uninit();
}

void Application::Init()
{
	int32_t screenWidth = 0;
	int32_t screenHeight = 0;
	RenderModule::GetScreenSize(screenWidth, screenHeight);

	multisampleScene_ = RenderModule::CreateResource<FrameBuffer>(screenWidth, screenHeight, 16);
	scene_ = RenderModule::CreateResource<FrameBuffer>(screenWidth, screenHeight);
	pingpong_[0] = RenderModule::CreateResource<ColorFrameBuffer>(screenWidth, screenHeight);
	pingpong_[1] = RenderModule::CreateResource<ColorFrameBuffer>(screenWidth, screenHeight);

	geometryRenderer_ = RenderModule::CreateResource<GeometryRenderer2D>();
	textRenderer_ = RenderModule::CreateResource<TextRenderer2D>();
	frameRenderer_ = RenderModule::CreateResource<FrameRenderer>();

	gaussianBlurEffector_ = RenderModule::CreateResource<GaussianBlurEffector>();
	bloomEffector_ = RenderModule::CreateResource<BloomEffector>();

	font_ = RenderModule::CreateResource<TTFont>("Resource/Font/SeoulNamsanEB.ttf", 0x00, 0x127, 128.0f);

	geometryRenderer_->SetOrtho(RenderModule::GetScreenOrtho());
	textRenderer_->SetOrtho(RenderModule::GetScreenOrtho());
}

void Application::Run()
{
	PlatformModule::RunLoop(
		[&](float deltaSeconds)
		{
			ImGui::Begin("Bloom", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse);
			ImGui::SetWindowPos(ImVec2(10.0f, 10.0f));
			ImGui::SetWindowSize(ImVec2(300.0f, 100.0f));
			ImGui::Checkbox("Active", &bIsActiveBloom_);
			ImGui::ColorEdit4("Text Color", textColor_.data, ImGuiColorEditFlags_HDR);
			ImGui::ColorEdit4("Outline Color", outlineColor_.data, ImGuiColorEditFlags_HDR);
			ImGui::End();

			RenderModule::SetWindowViewport();
			RenderModule::BeginFrame(0.0f, 0.0f, 0.0f, 1.0f);

			multisampleScene_->Bind();
			{
				multisampleScene_->Clear(0.0f, 0.0f, 0.0f, 0.0f);

				geometryRenderer_->DrawWireframeRoundRectangle2D(Vec2f(500.0f, 400.0f), 500.0f, 200.0f, 10.0f, 0.0f, outlineColor_);
				textRenderer_->DrawText2D(font_, L"Bloom!", Vec2f(500.0f, 400.0f), textColor_);
			}
			multisampleScene_->Unbind();

			FrameBuffer::Blit(multisampleScene_, scene_);

			if (bIsActiveBloom_)
			{
				gaussianBlurEffector_->Execute(scene_, pingpong_);
				bloomEffector_->Execute(scene_, pingpong_[0]);
			}
			else
			{
				frameRenderer_->DrawFrameBuffer(scene_, 0);
			}

			RenderModule::EndFrame();
		}
	);
}