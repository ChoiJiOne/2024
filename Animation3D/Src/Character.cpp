#include <cgltf.h>

#include "GLTFLoader.h"
#include "RenderModule.h"
#include "Texture2D.h"

#include "Camera.h"
#include "Character.h"
#include "StringUtils.h"

Character::Character(Camera* camera)
	: camera_(camera)
	, location_(ImVec2(10.0f, 10.0f))
	, size_(ImVec2(200.0f, 310.0f))
	, flags_(ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse)
{
	static bool bIsInitMesh = false;
	if (!bIsInitMesh)
	{
		cgltf_data* data = GLTFLoader::Load("Resource/Model/Michelle.gltf");

		std::vector<GLTFLoader::MeshData> meshData = GLTFLoader::LoadMeshData(data);
		skeleton_ = GLTFLoader::LoadSkeleton(data);
		clips_ = GLTFLoader::LoadAnimationClips(data);

		GLTFLoader::Free(data);

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

			meshes_.push_back(RenderModule::CreateResource<SkinnedMesh>(vertices, indices, false));
		}

		bIsInitMesh = true;
	}

	static Texture2D* material = nullptr;
	if (!material)
	{
		material = RenderModule::CreateResource<Texture2D>("Resource/Texture/Michelle.png", false);
	}

	material_ = material;

	crossFadeController_.SetSkeleton(skeleton_);
	crossFadeController_.Play(&clips_[currentClip_]);
	crossFadeController_.Update(0.0f);
}

Character::~Character()
{
	if (bIsInitialized_)
	{
		Release();
	}
}

void Character::Tick(float deltaSeconds)
{
	crossFadeController_.Update(deltaSeconds);

	ImGui::Begin("Animation", nullptr, flags_);
	{
		ImGui::SetWindowPos(location_);
		ImGui::SetWindowSize(size_);
		
		for (uint32_t index = 0; index < clips_.size(); ++index)
		{
			const std::string& clipName = clips_[index].GetName();
			std::string label = StringUtils::PrintF("%s", clipName.c_str(), clips_[index].GetStartTime(), clips_[index].GetEndTime());

			if (ImGui::RadioButton(label.c_str(), currentClip_ == index))
			{
				currentClip_ = index;
				crossFadeController_.FadeTo(&clips_[currentClip_], 0.5f);
			}
		}

		ImGui::Separator();

		float startTime = crossFadeController_.GetCurrentClip()->GetStartTime();
		float endTime = crossFadeController_.GetCurrentClip()->GetEndTime();
		float currentTime = crossFadeController_.GetTime();
		float progress = (currentTime - startTime) / (endTime - startTime);

		ImGui::Text("Start/End: %.1f - %.1f", startTime, endTime);
		ImGui::Text("Current: %.1f", currentTime);
		ImGui::ProgressBar(progress, ImVec2(0.0f, 0.0f), "");

		camera_->SetActive(!ImGui::IsWindowFocused());
	}
	ImGui::End();
}

void Character::Release()
{
	if (bIsInitialized_)
	{
		bIsInitialized_ = false;
	}
}
