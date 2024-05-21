#pragma once

#include <string>
#include <vector>

#include <cgltf.h>

#include "Vec.h"


/**
 * @brief GLTF ���ϰ� ���� ���� ������ �ε��� �����մϴ�.
 *
 * @note �� Ŭ������ ��� ������ �޼���� ��� static �Դϴ�.
 */
class GLTFLoader
{
public:
	/**
	 * @brief GLTF �޽� �������Դϴ�.
	 */
	struct MeshData
	{
		std::vector<Vec3f> positions;
		std::vector<Vec3f> normals;
		std::vector<Vec2f> texCoords;
		std::vector<Vec4f> weights;
		std::vector<Vec4i> joints;
		std::vector<uint32_t> indices;
	};


public:
	/**
	 * @brief GLTF ������ �ε��մϴ�.
	 * 
	 * @param path GLTF ������ ����Դϴ�.
	 * 
	 * @return GLTF �������� �����͸� ��ȯ�մϴ�.
	 * 
	 * @note �� �޼��带 �̿��ؼ� ���� �����ʹ� �ݵ�� Free �޼��带 �̿��ؼ� �����ؾ� �մϴ�.
	 */
	static cgltf_data* Load(const std::string& path);


	/**
	 * @brief GLTF ������ �Ҵ��� �����մϴ�.
	 *
	 * @param data �Ҵ��� ������ GLTF �������Դϴ�.
	 */
	static void Free(cgltf_data* data);
};