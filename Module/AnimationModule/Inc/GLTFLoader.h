#pragma once

#include <string>
#include <vector>

#include <cgltf.h>

#include "Mat.h"
#include "Transform.h"
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


private:
	/**
	 * @brief GLTF ���κ��� ���� Ʈ�������� ����ϴ�.
	 * 
	 * @param node ���� Ʈ�������� ���� GLTF ����Դϴ�.
	 * 
	 * @return GLTF ����� ���� Ʈ������ ���� ��ȯ�մϴ�.
	 */
	static Transform GetLocalTransform(cgltf_node* node);
};