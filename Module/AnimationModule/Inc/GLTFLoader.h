#pragma once

#include <string>
#include <vector>

#include <cgltf.h>

#include "Mat.h"
#include "Transform.h"
#include "Vec.h"


/**
 * @brief GLTF 파일과 파일 내의 데이터 로딩을 수행합니다.
 *
 * @note 이 클래스의 멤버 변수와 메서드는 모두 static 입니다.
 */
class GLTFLoader
{
public:
	/**
	 * @brief GLTF 파일을 로딩합니다.
	 * 
	 * @param path GLTF 파일의 경로입니다.
	 * 
	 * @return GLTF 데이터의 포인터를 반환합니다.
	 * 
	 * @note 이 메서드를 이용해서 얻은 포인터는 반드시 Free 메서드를 이용해서 해제해야 합니다.
	 */
	static cgltf_data* Load(const std::string& path);


	/**
	 * @brief GLTF 데이터 할당을 해제합니다.
	 *
	 * @param data 할당을 해제할 GLTF 데이터입니다.
	 */
	static void Free(cgltf_data* data);


private:
	/**
	 * @brief GLTF 노드로부터 로컬 트랜스폼을 얻습니다.
	 * 
	 * @param node 로컬 트랜스폼을 얻을 GLTF 노드입니다.
	 * 
	 * @return GLTF 노드의 로컬 트랜스폼 값을 반환합니다.
	 */
	static Transform GetLocalTransform(cgltf_node* node);


	/**
	 * @brief GLTF 노드의 인덱스를 얻습니다.
	 * 
	 * @param target 인덱스를 얻을 타겟 노드입니다.
	 * @param nodes 노드 목록입니다.
	 * @param numNodes 노드 목록의 수입니다.
	 * 
	 * @return GLTF 노드의 인덱스 값을 반환합니다
	 */
	static int32_t GetNodeIndex(cgltf_node* target, cgltf_node* nodes, uint32_t numModes);
};