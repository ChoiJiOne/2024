#include "GeometryGenerator.h"
#include "RenderModule.h"
#include "MeshRenderer.h"

#include "Camera.h"
#include "Sphere.h"

Sphere::Sphere(MeshRenderer* renderer, Camera* camera)
	: renderer_(renderer)
	, camera_(camera)
	, windowFlags_(static_cast<ImGuiWindowFlags_>(ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse))
{
	location_ = ImVec2(10.0f, 10.0f);
	size_ = ImVec2(400.0f, 200.0f);

	std::vector<VertexPositionNormalUv3D> vertices;
	std::vector<uint32_t> indices;
	GeometryGenerator::CreateSphere(1.0f, 40, vertices, indices);
	mesh_ = RenderModule::CreateResource<StaticMesh<VertexPositionNormalUv3D>>(vertices, indices);

	tileMap_ = RenderModule::CreateResource<TileMap>(TileMap::ESize::Size_512x512, TileMap::ESize::Size_64x64, Vec4f(1.0f, 0.0f, 0.0f, 1.0f), Vec4f(1.0f, 1.0f, 1.0f, 1.0f));
}

Sphere::~Sphere()
{
	if (bIsInitialized_)
	{
		Release();
	}
}

void Sphere::Tick(float deltaSeconds)
{
	ImGui::Begin("Transform", nullptr, windowFlags_);
	ImGui::SetWindowPos(location_);
	ImGui::SetWindowSize(size_);
	
	camera_->SetActive(!ImGui::IsWindowFocused());

	ImGui::Text("Position");
	ImGui::Text("position");
	ImGui::SameLine();
	ImGui::SliderFloat3("##position", position_.data, -10.0f, 10.0f);
	ImGui::SameLine();
	if (ImGui::Button("Reset##position"))
	{
		position_ = Vec3f(0.0f, 0.0f, 0.0f);
	}
	ImGui::Separator();

	ImGui::Text("Rotate");
	ImGui::Text("%-6s", "axis");
	ImGui::SameLine();
	ImGui::SliderFloat3("##axis", axis_.data, -1.0f, 1.0f);
	ImGui::SameLine();
	if (ImGui::Button("Reset##axis"))
	{
		axis_ = Vec3f(0.0f, 0.0f, 0.0f);
	}

	ImGui::Text("%-6s", "radian");
	ImGui::SameLine();
	ImGui::SliderFloat("##radian", &radian_, -TwoPi, TwoPi);
	ImGui::SameLine();
	if (ImGui::Button("Reset##radian"))
	{
		radian_ = 0.0f;
	}

	ImGui::Separator();

	ImGui::Text("Scale");
	ImGui::Text("scale");
	ImGui::SameLine();
	ImGui::SliderFloat3("##scale", scale_.data, 0.0f, 10.0f);
	ImGui::SameLine();
	if (ImGui::Button("Reset##scale"))
	{
		scale_ = Vec3f(1.0f, 1.0f, 1.0f);
	}

	ImGui::End();

	transform_.position = position_;
	transform_.rotate = Quat::AxisRadian(axis_, radian_);
	transform_.scale = scale_;
}

void Sphere::Render()
{
	renderer_->DrawMesh(mesh_, Transform::ToMat(transform_), tileMap_);
}

void Sphere::Release()
{
	if (bIsInitialized_)
	{
		bIsInitialized_ = false;
	}
}