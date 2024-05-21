#pragma warning(push)
#pragma warning(disable: 26812)

#include "Assertion.h"
#include "MathModule.h"

#include "GLTFLoader.h"
#include "TransformTrack.h"

void GetScalarValues(std::vector<float>& outScalars, uint32_t componentCount, const cgltf_accessor* accessor)
{
	outScalars.resize(accessor->count * componentCount);
	for (cgltf_size i = 0; i < accessor->count; ++i)
	{
		cgltf_accessor_read_float(accessor, i, &outScalars[i * componentCount], componentCount);
	}
}

template<typename T, int N>
void TrackFromChannel(Track<T, N>& inOutTrack, const cgltf_animation_channel* channel)
{
	cgltf_animation_sampler* sampler = channel->sampler;

	EInterpolation interpolation = EInterpolation::CONSTANT;
	if (channel->sampler->interpolation == cgltf_interpolation_type_linear)
	{
		interpolation = EInterpolation::LINEAR;
	}
	else if (channel->sampler->interpolation == cgltf_interpolation_type_cubic_spline)
	{
		interpolation = EInterpolation::CUBIC;
	}

	bool isSamplerCubic = (interpolation == EInterpolation::CUBIC);
	inOutTrack.SetInterpolation(interpolation);

	std::vector<float> timelineFloats;
	GetScalarValues(timelineFloats, 1, sampler->input);

	std::vector<float> valueFloats;
	GetScalarValues(valueFloats, N, sampler->output);

	uint32_t numFrames = (uint32_t)sampler->input->count;
	uint32_t numberOfValuesPerFrame = valueFloats.size() / timelineFloats.size();
	inOutTrack.Resize(numFrames);

	for (uint32_t i = 0; i < numFrames; ++i)
	{
		int32_t baseIndex = i * numberOfValuesPerFrame;
		Frame<N>& frame = inOutTrack[i];
		int32_t offset = 0;

		frame.time = timelineFloats[i];

		for (int32_t component = 0; component < N; ++component)
		{
			frame.in[component] = isSamplerCubic ? valueFloats[baseIndex + offset++] : 0.0f;
		}

		for (int32_t component = 0; component < N; ++component)
		{
			frame.value[component] = valueFloats[baseIndex + offset++];
		}

		for (int32_t component = 0; component < N; ++component)
		{
			frame.out[component] = isSamplerCubic ? valueFloats[baseIndex + offset++] : 0.0f;
		}
	}
}

cgltf_data* GLTFLoader::Load(const std::string& path)
{
	cgltf_result result = cgltf_result_success;
	cgltf_options options = {};
	cgltf_data* data = nullptr;

	result = cgltf_parse_file(&options, path.c_str(), &data);
	ASSERT(result == cgltf_result_success, "failed to parse %s file", path.c_str());

	result = cgltf_load_buffers(&options, data, path.c_str());
	ASSERT(result == cgltf_result_success, "failed to load %s file", path.c_str());

	result = cgltf_validate(data);
	ASSERT(result == cgltf_result_success, "invalid %s gltf file", path.c_str());

	return data;
}

void GLTFLoader::Free(cgltf_data* data)
{
	if (data)
	{
		cgltf_free(data);
		data = nullptr;
	}
}

std::vector<GLTFLoader::MeshData> GLTFLoader::LoadMeshData(cgltf_data* data)
{
	std::vector<GLTFLoader::MeshData> meshes;

	cgltf_node* begin = data->nodes;
	cgltf_node* end = data->nodes + data->nodes_count;

	for (cgltf_node* node = begin; node != end; ++node)
	{
		if (!node->mesh || !node->skin) continue;

		cgltf_primitive* beginPrimitive = node->mesh->primitives;
		cgltf_primitive* endPrimitive = node->mesh->primitives + node->mesh->primitives_count;

		for (cgltf_primitive* primitive = beginPrimitive; primitive != endPrimitive; ++primitive)
		{
			meshes.push_back(MeshData());
			MeshData& mesh = meshes.back();

			cgltf_attribute* beginAttribute = primitive->attributes;
			cgltf_attribute* endAttribute = primitive->attributes + primitive->attributes_count;

			for (cgltf_attribute* attribute = beginAttribute; attribute != endAttribute; ++attribute)
			{
				cgltf_attribute_type type = attribute->type;
				cgltf_accessor* accessor = attribute->data;
				uint32_t componentCount = static_cast<uint32_t>(accessor->type);

				std::vector<float> buffer(accessor->count * componentCount);
				for (cgltf_size index = 0; index < accessor->count; ++index)
				{
					cgltf_accessor_read_float(accessor, index, &buffer[index * componentCount], componentCount);
				}

				for (uint32_t i = 0; i < accessor->count; ++i)
				{
					int32_t index = i * componentCount;

					switch (type)
					{
					case cgltf_attribute_type_position:
					{
						Vec3f position = Vec3f(buffer[index + 0], buffer[index + 1], buffer[index + 2]);
						mesh.positions.push_back(position);
					}
					break;

					case cgltf_attribute_type_normal:
					{
						Vec3f normal = Vec3f(buffer[index + 0], buffer[index + 1], buffer[index + 2]);
						mesh.normals.push_back(Vec3f::Normalize(normal));
					}
					break;

					case cgltf_attribute_type_texcoord:
					{
						Vec2f texCoords = Vec2f(buffer[index + 0], buffer[index + 1]);
						mesh.texCoords.push_back(texCoords);
					}
					break;

					case cgltf_attribute_type_joints:
					{
						Vec4i joints(
							static_cast<int32_t>(buffer[index + 0] + 0.5f),
							static_cast<int32_t>(buffer[index + 1] + 0.5f),
							static_cast<int32_t>(buffer[index + 2] + 0.5f),
							static_cast<int32_t>(buffer[index + 3] + 0.5f)
						);

						joints.x = MathModule::Max<int32_t>(0, GetNodeIndex(node->skin->joints[joints.x], data->nodes, data->nodes_count));
						joints.y = MathModule::Max<int32_t>(0, GetNodeIndex(node->skin->joints[joints.y], data->nodes, data->nodes_count));
						joints.z = MathModule::Max<int32_t>(0, GetNodeIndex(node->skin->joints[joints.z], data->nodes, data->nodes_count));
						joints.w = MathModule::Max<int32_t>(0, GetNodeIndex(node->skin->joints[joints.w], data->nodes, data->nodes_count));

						mesh.joints.push_back(joints);
					}
					break;

					case cgltf_attribute_type_weights:
					{
						Vec4f weight = Vec4f(buffer[index + 0], buffer[index + 1], buffer[index + 2], buffer[index + 3]);
						mesh.weights.push_back(weight);
					}
					break;
					}
				}
			}

			if (primitive->indices)
			{
				uint32_t indexCount = static_cast<uint32_t>(primitive->indices->count);
				mesh.indices.resize(indexCount);

				for (uint32_t index = 0; index < indexCount; ++index)
				{
					mesh.indices[index] = static_cast<uint32_t>(cgltf_accessor_read_index(primitive->indices, index));
				}
			}
		}
	}

	return meshes;
}

Pose GLTFLoader::LoadRestPose(cgltf_data* data)
{
	cgltf_node* begin = data->nodes;
	cgltf_node* end = data->nodes + data->nodes_count;

	Pose result(static_cast<uint32_t>(data->nodes_count));
	uint32_t currentIndex = 0;

	for (cgltf_node* node = begin; node != end; ++node, ++currentIndex)
	{
		Transform transform = GetLocalTransform(node);
		result.SetLocalTransform(currentIndex, transform);

		int32_t parent = GetNodeIndex(node->parent, data->nodes, data->nodes_count);
		result.SetParent(currentIndex, parent);
	}

	return result;
}

Pose GLTFLoader::LoadBindPose(cgltf_data* data)
{
	Pose restPose = LoadRestPose(data);

	std::vector<Transform> worldBindPose(restPose.GetJointSize());
	for (uint32_t index = 0; index < worldBindPose.size(); ++index)
	{
		worldBindPose[index] = restPose.GetGlobalTransform(index);
	}

	cgltf_skin* begin = data->skins;
	cgltf_skin* end = data->skins + data->skins_count;

	for (cgltf_skin* skin = begin; skin != end; ++skin)
	{
		std::vector<float> invBindAccessor;
		GetScalarValues(invBindAccessor, 16, skin->inverse_bind_matrices);

		uint32_t numJoints = static_cast<uint32_t>(skin->joints_count);
		for (int32_t index = 0; index < numJoints; ++index)
		{
			float* matrix = &invBindAccessor[index * 16];
			Mat4x4 invBindMatrix(
				matrix[0], matrix[1], matrix[2], matrix[3],
				matrix[4], matrix[5], matrix[6], matrix[7],
				matrix[8], matrix[9], matrix[10], matrix[11],
				matrix[12], matrix[13], matrix[14], matrix[15]
			);
			Mat4x4 bindMatrix = Mat4x4::Inverse(invBindMatrix);
			Transform bindTransform = Transform::ToTransform(bindMatrix);

			cgltf_node* jointNode = skin->joints[index];
			int32_t jointIndex = GetNodeIndex(jointNode, data->nodes, restPose.GetJointSize());
			worldBindPose[jointIndex] = bindTransform;
		}
	}

	Pose bindPose = restPose;
	for (uint32_t index = 0; index < worldBindPose.size(); ++index)
	{
		Transform currentTransform = worldBindPose[index];
		int32_t parent = bindPose.GetParent(index);

		if (parent >= 0)
		{
			Transform parentTransform = worldBindPose[parent];
			currentTransform = Transform::Combine(Transform::Inverse(parentTransform), currentTransform);
		}

		bindPose.SetLocalTransform(index, currentTransform);
	}

	return bindPose;
}

std::vector<std::string> GLTFLoader::LoadJointNames(cgltf_data* data)
{
	std::vector<std::string> jointNames(data->nodes_count);

	for (uint32_t index = 0; index < jointNames.size(); ++index)
	{
		cgltf_node* node = &(data->nodes[index]);

		if (node->name != nullptr)
		{
			jointNames[index] = node->name;
		}
	}

	return jointNames;
}

Skeleton GLTFLoader::LoadSkeleton(cgltf_data* data)
{
	return Skeleton(LoadRestPose(data), LoadBindPose(data), LoadJointNames(data));
}

std::vector<Clip> GLTFLoader::LoadAnimationClip(cgltf_data* data)
{
	std::vector<Clip> clips(static_cast<uint32_t>(data->animations_count));

	for (uint32_t index = 0; index < clips.size(); ++index)
	{
		clips[index].SetName(data->animations[index].name);

		cgltf_animation_channel* begin = data->animations[index].channels;
		cgltf_animation_channel* end = data->animations[index].channels + data->animations[index].channels_count;

		for (cgltf_animation_channel* channel = begin; channel != end; ++channel)
		{
			cgltf_node* target = channel->target_node;

			int32_t nodeID = GetNodeIndex(target, data->nodes, data->nodes_count);

			switch (channel->target_path)
			{
			case cgltf_animation_path_type_translation:
			{
				VectorTrack& track = clips[index][nodeID].GetPositionTrack();
				TrackFromChannel<Vec3f, 3>(track, channel);
			}
			break;

			case cgltf_animation_path_type_scale:
			{
				VectorTrack& track = clips[index][nodeID].GetScaleTrack();
				TrackFromChannel<Vec3f, 3>(track, channel);
			}
			break;

			case cgltf_animation_path_type_rotation:
			{
				QuaternionTrack& track = clips[index][nodeID].GetRotateTrack();
				TrackFromChannel<Quat, 4>(track, channel);
			}
			break;
			}
		}

		clips[index].RecomputeDuration();
	}

	return clips;
}

int32_t GLTFLoader::GetNodeIndex(cgltf_node* target, cgltf_node* nodes, uint32_t numNodes)
{
	if (target == nullptr)
	{
		return -1;
	}

	int32_t index = 0;
	cgltf_node* begin = nodes;
	cgltf_node* end = nodes + numNodes;

	for (cgltf_node* node = begin; node != end; ++node, ++index)
	{
		if (target == node)
		{
			return index;
		}
	}

	return -1;
}

Transform GLTFLoader::GetLocalTransform(cgltf_node* node)
{
	Transform result;

	if (node->has_matrix)
	{
		Mat4x4 m(
			node->matrix[0], node->matrix[1], node->matrix[2], node->matrix[3],
			node->matrix[4], node->matrix[5], node->matrix[6], node->matrix[7],
			node->matrix[8], node->matrix[9], node->matrix[10], node->matrix[11],
			node->matrix[12], node->matrix[13], node->matrix[14], node->matrix[15]
		);

		result = Transform::ToTransform(m);
	}

	if (node->has_translation)
	{
		result.position = Vec3f(node->translation[0], node->translation[1], node->translation[2]);
	}

	if (node->has_rotation)
	{
		result.rotate = Quat(node->rotation[0], node->rotation[1], node->rotation[2], node->rotation[3]);
	}

	if (node->has_scale)
	{
		result.scale = Vec3f(node->scale[0], node->scale[1], node->scale[2]);
	}

	return result;
}

#pragma warning(pop)