#include "Camera.h"
#include "Control.h"


Control::Control(Camera* camera)
	: camera_(camera)
	, location_(ImVec2(10.0f, 10.0f))
	, size_(ImVec2(400.0f, 200.0f))
	, flags_(ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse)
{
	bIsInitialized_ = true;
}

Control::~Control()
{
	if (bIsInitialized_)
	{
		Release();
	}
}

void Control::Tick(float deltaSeconds)
{
	ImGui::Begin("Control", nullptr, flags_);
	ImGui::SetWindowPos(location_);
	ImGui::SetWindowSize(size_);

	float frameRate = ImGui::GetIO().Framerate;
	calculateFPSs_[currentFPS_] = frameRate;
	currentFPS_ = (currentFPS_ + 1) % calculateFPSs_.size();

	ImGui::Text("FPS : %d", static_cast<int32_t>(frameRate));
	ImGui::PlotLines("##FPS", calculateFPSs_.data(), calculateFPSs_.size(), 0, nullptr, 0.0f, 100.0f, ImVec2(0, 80));

	camera_->SetActive(!ImGui::IsWindowFocused());

	ImGui::End();
}

void Control::Release()
{
	if (bIsInitialized_)
	{
		bIsInitialized_ = false;
	}
}