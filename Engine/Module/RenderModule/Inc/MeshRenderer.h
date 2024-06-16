#pragma once

#include <vector>

#include "Mat.h"

#include "IResource.h"

class ITexture;
class Shader;
class StaticMesh;
class SkinnedMesh;
class ShadowMap;


/**
 * @brief �޽ø� �������ϴ� �������Դϴ�.
 */
class MeshRenderer : public IResource
{
public:
	/**
	 * @brief �޽��� �׸��� �������� ����Ʈ �������Դϴ�.
	 */
	explicit MeshRenderer();


	/**
	 * @brief �޽��� �׸��� �������� ���� �Ҹ����Դϴ�.
	 *
	 * @note ������ ���ο��� �Ҵ�� ��Ҹ� �����ϱ� ���ؼ��� �ݵ�� Release�� ȣ���ؾ� �մϴ�.
	 */
	virtual ~MeshRenderer();


	/**
	 * @brief �޽��� �׸��� �������� ���� �����ڿ� ���� �����ڸ� ��������� �����մϴ�.
	 */
	DISALLOW_COPY_AND_ASSIGN(MeshRenderer);


	/**
	 * @brief ������ ���� ���ҽ��� �Ҵ� �����մϴ�.
	 */
	virtual void Release() override;


	/**
	 * @brief �������� �Ķ���͸� �����մϴ�.
	 *
	 * @param view ������ �� ����Դϴ�.
	 */
	void SetView(const Mat4x4& view) { view_ = view; }


	/**
	 * @brief �������� ���� ���� ����� �����մϴ�.
	 *
	 * @param projection ������ ���� ����Դϴ�.
	 */
	void SetProjection(const Mat4x4& projection) { projection_ = projection; }


	/**
	 * @brief �������� �ε��� ���� �����մϴ�.
	 * 
	 * @param shadowMap ������ �ε��� ���Դϴ�.
	 */
	void SetShadowMap(ShadowMap* shadowMap) { shadowMap_ = shadowMap; }


	/**
	 * @brief �������� ����Ʈ ��ġ ���� �����մϴ�.
	 * 
	 * @param lightPosition ������ ����Ʈ ��ġ ���Դϴ�.
	 */
	void SetLightPosition(const Vec3f& lightPosition) { lightPosition_ = lightPosition; }


	/**
	 * @brief �������� ����Ʈ ���� ����� �����մϴ�.
	 * 
	 * @param lightSpaceMatrix ������ ����Ʈ ���� ��� ���Դϴ�.
	 */
	void SetLightSpaceMatrix(Mat4x4 lightSpaceMatrix) { lightSpaceMatrix_ = lightSpaceMatrix; }


	/**
	 * @brief �������� ī�޶� ��ġ ���� �����մϴ�.
	 * 
	 * @param cameraPosition ������ ī�޶� ��ġ ���Դϴ�.
	 */
	void SetCameraPosition(const Vec3f& cameraPosition) { cameraPosition_ = cameraPosition; }


	/**
	 * @brief ���� �޽ø� �������մϴ�.
	 *
	 * @param world ���� �޽��� ���� ����Դϴ�.
	 * @param mesh ���� �޽� ���ҽ��Դϴ�.
	 * @param material ���� �޽��� �����Դϴ�.
	 */
	void DrawStaticMesh(const Mat4x4& world, const StaticMesh* mesh, const ITexture* material);


	/**
	 * @brief ��Ű�� �޽ø� �������մϴ�.
	 *
	 * @param world ���� �޽��� ���� ����Դϴ�.
	 * @param bindPose ���ε� ���� ����Դϴ�.
	 * @param invBindPose �� ���ε� ���� ����Դϴ�.
	 * @param mesh ��Ű�� �޽� ���ҽ��Դϴ�.
	 * @param material ��Ű�� �޽��� �����Դϴ�.
	 */
	void DrawSkinnedMesh(const Mat4x4& world, const std::vector<Mat4x4>& bindPose, const std::vector<Mat4x4>& invBindPose, const SkinnedMesh* mesh, const ITexture* material);


private:
	/**
	 * @brief �������� �� ����Դϴ�.
	 */
	Mat4x4 view_;


	/**
	 * @brief �������� ���� ���� ����Դϴ�.
	 */
	Mat4x4 projection_;


	/**
	 * @brief ����Ʈ�� ��ġ�Դϴ�.
	 */
	Vec3f lightPosition_;


	/**
	 * @brief ����Ʈ�� ������ ����Դϴ�.
	 */
	Mat4x4 lightSpaceMatrix_;


	/**
	 * @brief ī�޶��� ���� ��ġ�Դϴ�.
	 */
	Vec3f cameraPosition_;


	/**
	 * @brief �ε��� ���� �� ������ �ε��� ���Դϴ�. 
	 */
	ShadowMap* shadowMap_ = nullptr;


	/**
	 * @brief ���� �޽��� ���� ���� �������� ���̴��Դϴ�.
	 */
	Shader* staticMeshShader_ = nullptr;


	/**
	 * @brief ��Ű�� �޽��� ���� ���� �������� ���̴��Դϴ�.
	 */
	Shader* skinnedMeshShader_ = nullptr;


	/**
	 * @brief �ε��� ���� ���ε� �����Դϴ�.
	 */
	static const uint32_t SHADOW_MAP_BIND_SLOT = 0;


	/**
	 * @brief �޽� ���� ���� ���ε� �����Դϴ�.
	 */
	static const uint32_t MATERIAL_MAP_BIND_SLOT = 1;
};
