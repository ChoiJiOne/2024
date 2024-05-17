#include <algorithm>

#include "GameModule.h"

#include "Camera.h"
#include "Control.h"
#include "Sphere3D.h"

Control::Control(Camera* camera, std::list<Sphere3D*>& spheres)
	: camera_(camera)
	, location_(ImVec2(10.0f, 10.0f))
	, size_(ImVec2(350.0f, 200.0f))
	, flags_(ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse)
	, spheres_(spheres)
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
	float frameRate = ImGui::GetIO().Framerate;
	calculateFPSs_[currentFPS_] = frameRate;
	currentFPS_ = (currentFPS_ + 1) % calculateFPSs_.size();

	averageFPS_ = 0.0f;
	std::for_each(calculateFPSs_.begin(), calculateFPSs_.end(), [&](float fps) { averageFPS_ += fps; });
	averageFPS_ = averageFPS_ / static_cast<float>(calculateFPSs_.size());

	ImGui::Begin("Control", nullptr, flags_);
	ImGui::SetWindowPos(location_);
	ImGui::SetWindowSize(size_);
	ImGui::Text("FPS: %3d AVERAGE: %3d", static_cast<int32_t>(frameRate), static_cast<int32_t>(averageFPS_));
	ImGui::PlotLines("##FPS", calculateFPSs_.data(), calculateFPSs_.size(), 0, nullptr, 0.0f, 100.0f, ImVec2(0, 80));
	ImGui::Separator();

	ImGui::Text("Sphere : %d", spheres_.size());
	if (ImGui::Button("Create"))
	{
		if (spheres_.size() < MAX_CREATE_ENTITY)
		{
			Sphere3D* sphere = GameModule::CreateEntity<Sphere3D>();
			spheres_.push_back(sphere);
		}
	}

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