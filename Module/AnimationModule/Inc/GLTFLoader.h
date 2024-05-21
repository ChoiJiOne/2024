#pragma once

#include <string>
#include <vector>

#include <cgltf.h>

#include "Vec.h"

#include "Clip.h"
#include "Pose.h"
#include "Skeleton.h"


/**
 * @brief GLTF 파일과 파일 내의 데이터 로딩을 수행합니다.
 *
 * @note 이 클래스의 멤버 변수와 메서드는 모두 static 입니다.
 */
class GLTFLoader
{
public:
	/**
	 * @brief GLTF 메시 데이터입니다.
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


	/**
	 * @brief GLTF 데이터로부터 스키닝 메시 데이터를 로딩합니다.
	 *
	 * @param data 메시 데이터를 로딩할 GLTF 데이터입니다.
	 *
	 * @return GLTF 데이터 내의 메시 데이터 목록을 반환합니다.
	 */
	static std::vector<MeshData> LoadMeshData(cgltf_data* data);



	/**
	 * @brief GLTF 데이터로부터 리셋 포즈 데이터를 로딩합니다.
	 *
	 * @param data 대기 포즈 데이터를 로딩할 GLTF 데이터입니다.
	 *
	 * @return 대기 포즈 데이터를 반환합니다.
	 */
	static Pose LoadRestPose(cgltf_data* data);


	/**
	 * @brief GLTF 데이터로부터 바인드 포즈 데이터를 로딩합니다.
	 *
	 * @param data 바인드 포즈 데이터를 로딩할 GLTF 데이터입니다.
	 *
	 * @return 바인드 포즈 데이터를 반환합니다.
	 */
	static Pose LoadBindPose(cgltf_data* data);


	/**
	 * @brief GLTF 데이터로부터 조인트 이름 목록을 얻습니다.
	 *
	 * @param data 조인트 이름 목록을 로딩할 GLTF 데이터입니다.
	 *
	 * @return 조인트 이름 목록을 반환합니다.
	 */
	static std::vector<std::string> LoadJointNames(cgltf_data* data);


	/**
	 * @brief GLTF 데이터로부터 스켈레톤 데이터를 얻습니다.
	 *
	 * @param data 스켈레톤 데이터를 로딩할 GLTF 데이터입니다.
	 *
	 * @return 스켈레톤을 반환합니다.
	 */
	static Skeleton LoadSkeleton(cgltf_data* data);


	/**
	 * @brief GLTF 데이터로부터 애니메이션 클립 목록을 로딩합니다.
	 *
	 * @param data 애니메이션 클립 데이터를 로딩할 GLTF 데이터입니다.
	 *
	 * @return 애니메이션 클립 목록을 반환합니다.
	 */
	static std::vector<Clip> LoadAnimationClip(cgltf_data* data);


private:
	/**
	 * @brief 전체 노드 목록으로부터 타겟 노드의 인덱스를 얻습니다.
	 *
	 * @param target 인덱스를 얻을 노드입니다.
	 * @param nodes 전체 노드의 목록입니다.
	 * @param numNodes 전체 노드의 수입니다.
	 */
	static int32_t GetNodeIndex(cgltf_node* target, cgltf_node* nodes, uint32_t numNodes);


	/**
	 * @brief 노드의 로컬 트랜스폼을 얻습니다.
	 *
	 * @param node 트랜스폼 값을 얻을 노드입니다.
	 *
	 * @return 노드의 로컬 트랜스폼을 반환합니다.
	 */
	static Transform GetLocalTransform(cgltf_node* node);
};