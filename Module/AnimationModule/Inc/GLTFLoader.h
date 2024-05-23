#pragma once

#include <string>
#include <vector>

#include <cgltf.h>

#include "Mat.h"
#include "Transform.h"
#include "Vec.h"

#include "Clip.h"


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


	/**
	 * @brief GLTF �����ͷκ��� Rest ��� �ε��մϴ�.
	 * 
	 * @param data GLTF �������Դϴ�.
	 * 
	 * @return GLTF�κ��� ����� Rest ��� ��ȯ�մϴ�.
	 */
	static Pose LoadRestPose(cgltf_data* data);


	/**
	 * @brief GLTF �����ͷκ��� Bind ��� �ε��մϴ�.
	 * 
	 * @param data GLTF �������Դϴ�.
	 *
	 * @return GLTF�κ��� ����� Bind ��� ��ȯ�մϴ�.
	 */
	static Pose LoadBindPose(cgltf_data* data);


	/**
	 * @brief GLTF �����ͷκ��� ����(Joint)�� �̸� ����� �ε��մϴ�.
	 * 
	 * @param data GLTF �������Դϴ�.
	 * 
	 * @return GLTF�κ��� ����� ����(Joint)�� �̸� ����� ��ȯ�մϴ�.
	 */
	static std::vector<std::string> LoadJointNames(cgltf_data* data);


	/**
	 * @brief GLTF �����ͷκ��� �ִϸ��̼� Ŭ�� ����� �ε��մϴ�.
	 * 
	 * @param data GLTF �������Դϴ�.
	 * 
	 * @return GLTF�κ��� ����� �ִϸ��̼� Ŭ�� ����� ��ȯ�մϴ�.
	 */
	static std::vector<Clip> LoadAnimationClips(cgltf_data* data);


private:
	/**
	 * @brief GLTF ���κ��� ���� Ʈ�������� ����ϴ�.
	 * 
	 * @param node ���� Ʈ�������� ���� GLTF ����Դϴ�.
	 * 
	 * @return GLTF ����� ���� Ʈ������ ���� ��ȯ�մϴ�.
	 */
	static Transform GetLocalTransform(cgltf_node* node);


	/**
	 * @brief GLTF ����� �ε����� ����ϴ�.
	 * 
	 * @param target �ε����� ���� Ÿ�� ����Դϴ�.
	 * @param nodes ��� ����Դϴ�.
	 * @param numNodes ��� ����� ���Դϴ�.
	 * 
	 * @return GLTF ����� �ε��� ���� ��ȯ�մϴ�
	 */
	static int32_t GetNodeIndex(cgltf_node* target, cgltf_node* nodes, uint32_t numModes);


	/**
	 * @brief GLTF�� ��Į�� ���� ����ϴ�.
	 * 
	 * @param outScalars GLTF�� ��Į�� ���Դϴ�.
	 * @param componentCount ��Į�� ���� ������Ʈ ���Դϴ�.
	 * @param accessor ��Į�� �������� �����Դϴ�.
	 */
	static void GetScalarValues(std::vector<float>& outScalars, uint32_t componentCount, const cgltf_accessor* accessor);



	/**
	 * @brief GLTF�� ä�ηκ��� Ʈ�� ���� ����ϴ�.
	 * 
	 * @param inOutTrack GLTF�� ä�ηκ��� Ʈ�� ���� ������ �������Դϴ�. 
	 * @param channel GLTF �ִϸ��̼� ä���Դϴ�.
	 */
	template <typename T, uint32_t N>
	static void TrackFromChannel(Track<T, N>& inOutTrack, const cgltf_animation_channel* channel);
};