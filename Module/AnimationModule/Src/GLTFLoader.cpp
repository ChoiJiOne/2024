#pragma warning(push)
#pragma warning(disable: 26812)
#pragma warning(disable: 26451)

#include "Assertion.h"
#include "MathModule.h"

#include "GLTFLoader.h"

template <typename T, uint32_t N>
void GLTFLoader::TrackFromChannel(Track<T, N>& inOutTrack, const cgltf_animation_channel* channel)
{
	cgltf_animation_sampler sampler = channel->sampler;

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

	uint32_t numKeyframes = static_cast<uint32_t>(sampler->input->count);
	uint32_t numberOfValuesPerKeyframe = valueFloats.size() / timelineFloats.size();
	inOutTrack.Resize(numKeyframes);

	for (uint32_t index = 0; index < numKeyframes; ++index)
	{
		Keyframe<T>& keyframe = inOutTrack[index];

		int32_t baseIndex = index * numberOfValuesPerKeyframe;
		int32_t offset = 0;

		keyframe.time = timelineFloats[index];

		for (int32_t component = 0; component < N; ++component)
		{
			keyframe.in[component] = isSamplerCubic ? valueFloats[baseIndex + offset++] : 0.0f;
		}

		for (int32_t component = 0; component < N; ++component)
		{
			keyframe.value[component] = valueFloats[baseIndex + offset++];
		}

		for (int32_t component = 0; component < N; ++component)
		{
			keyframe.out[component] = isSamplerCubic ? valueFloats[baseIndex + offset++] : 0.0f;
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

Pose GLTFLoader::LoadRestPose(cgltf_data* data)
{
	uint32_t numJoints = static_cast<uint32_t>(data->nodes_count);
	Pose restPose(numJoints);

	for (uint32_t index = 0; index < numJoints; ++index)
	{
		cgltf_node* node = &(data->nodes[index]);

		Transform transform = GetLocalTransform(node);
		restPose.SetLocalTransform(index, transform);

		int32_t parent = GetNodeIndex(node->parent, data->nodes, numJoints);
		restPose.SetParent(index, parent);
	}

	return restPose;
}

std::vector<std::string> GLTFLoader::LoadJointNames(cgltf_data* data)
{
	uint32_t numJoints = static_cast<uint32_t>(data->nodes_count);
	std::vector<std::string> jointNames(numJoints, "EMPTY NODE");

	for (uint32_t index = 0; index < numJoints; ++index)
	{
		cgltf_node* node = &(data->nodes[index]);

		if (node->name)
		{
			jointNames[index] = node->name;
		}
	}

	return jointNames;
}

Transform GLTFLoader::GetLocalTransform(cgltf_node* node)
{
	Transform transform;

	if (node->has_matrix)
	{
		Mat4x4 m(
			 node->matrix[0],  node->matrix[1],  node->matrix[2],  node->matrix[3],
			 node->matrix[4],  node->matrix[5],  node->matrix[6],  node->matrix[7],
			 node->matrix[8],  node->matrix[9], node->matrix[10], node->matrix[11],
			node->matrix[12], node->matrix[13], node->matrix[14], node->matrix[15]
		);

		transform = Transform::ToTransform(m);
	}

	if (node->has_translation)
	{
		transform.position = Vec3f(node->translation[0], node->translation[1], node->translation[2]);
	}

	if (node->has_rotation)
	{
		transform.rotate = Quat(node->rotation[0], node->rotation[1], node->rotation[2], node->rotation[3]);
	}

	if (node->has_scale)
	{
		transform.scale = Vec3f(node->scale[0], node->scale[1], node->scale[2]);
	}

	return transform;
}

int32_t GLTFLoader::GetNodeIndex(cgltf_node* target, cgltf_node* nodes, uint32_t numModes)
{
	if (target == nullptr)
	{
		return -1;
	}

	for (uint32_t index = 0; index < numModes; ++index)
	{
		if (target == &nodes[index])
		{
			return static_cast<int32_t>(index);
		}
	}

	return -1;
}

void GLTFLoader::GetScalarValues(std::vector<float>& outScalars, uint32_t componentCount, const cgltf_accessor* accessor)
{
	outScalars.resize(accessor->count * componentCount);

	for (cgltf_size index = 0; index < accessor->count; ++index)
	{
		cgltf_accessor_read_float(accessor, index, &outScalars[index * componentCount], componentCount);
	}
}

#pragma warning(pop)