#pragma warning(push)
#pragma warning(disable: 26812)
#pragma warning(disable: 26451)

#include <mimalloc.h>

#include "Assertion.h"
#include "GLTFUtils.h"

void* MallocGLTF(void* user, size_t sz)
{
	(void)(user); /** ����. ������� ���� */
	return mi_malloc(sz);
}

void FreeGLTF(void* user, void* ptr)
{
	(void)(user); /** ����. ������� ���� */
	mi_free(ptr);
}

cgltf_data* GLTFUtils::Load(const std::string& path)
{
	cgltf_result result = cgltf_result_success;
	cgltf_options options = {};
	options.memory.alloc_func = MallocGLTF;
	options.memory.free_func = FreeGLTF;
	options.memory.user_data = nullptr;

	cgltf_data* data = nullptr;

	result = cgltf_parse_file(&options, path.c_str(), &data);
	ASSERT(result == cgltf_result_success, "Failed to parse '%s' file", path.c_str());

	result = cgltf_load_buffers(&options, data, path.c_str());
	ASSERT(result == cgltf_result_success, "Failed to load '%s' file", path.c_str());

	result = cgltf_validate(data);
	ASSERT(result == cgltf_result_success, "Invalid '%s' file", path.c_str());

	return data;
}

void GLTFUtils::Free(cgltf_data* data)
{
	if (data)
	{
		cgltf_free(data);
		data = nullptr;
	}
}

std::vector<std::string> GLTFUtils::GetAllNodeNames(cgltf_data* data)
{
	uint32_t count = data->nodes_count;
	std::vector<std::string> names(count);

	for (uint32_t index = 0; index < count; ++index)
	{
		cgltf_node* node = &data->nodes[index];
		names[index] = node->name ? node->name : "EMPTY";
	}

	return names;
}

#pragma warning(pop)