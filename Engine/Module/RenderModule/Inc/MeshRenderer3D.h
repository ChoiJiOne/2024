#pragma once

#include <vector>

#include "Mat.h"

#include "IResource.h"
#include "ITexture2D.h"

class Shader;
class IMesh;


/**
 * @brief 3D �޽ø� �������ϴ� �������Դϴ�.
 */
class MeshRenderer3D : public IResource
{
public:
	/**
	 * @brief 3D �޽ø� �������ϴ� �������� �������Դϴ�.
	 */
	MeshRenderer3D();


	/**
	 * @brief 3D �޽ø� �������ϴ� �������� ���� �Ҹ����Դϴ�.
	 */
	virtual ~MeshRenderer3D();


	/**
	 * @brief 3D �޽ø� �������ϴ� �������� ���� ������ �� ���� �����ڸ� ��������� �����մϴ�.
	 */
	DISALLOW_COPY_AND_ASSIGN(MeshRenderer3D);


	/**
	 * @brief 3D �޽ø� �������ϴ� �������� ���� ���ҽ��� �Ҵ� �����մϴ�.
	 */
	virtual void Release() override;


	/**
	 * @brief �������� �� ����� �����մϴ�.
	 *
	 * @param view ������ �� ����Դϴ�.
	 */
	void SetView(const Mat4x4& view) { view_ = view; }


	/**
	 * @brief �������� ���� ����� �����մϴ�.
	 *
	 * @param projection ������ ���� ����Դϴ�.
	 */
	void SetProjection(const Mat4x4& projection) { projection_ = projection; }


	/**
	 * @brief �������� ����Ʈ �� ����� �����մϴ�.
	 *
	 * @param lightView ������ �� ����Դϴ�.
	 */
	void SetLightView(const Mat4x4& lightView) { lightView_ = lightView; }


	/**
	 * @brief �������� ����Ʈ ���� ����� �����մϴ�.
	 *
	 * @param lightProjection ������ ���� ����Դϴ�.
	 */
	void SetLightProjection(const Mat4x4& lightProjection) { lightProjection_ = lightProjection; }


	/**
	 * @brief ī�޶��� ��ġ�� �����մϴ�.
	 *
	 * @param viewPosition ������ ī�޶��� ��ġ�Դϴ�.
	 */
	void SetViewPosition(const Vec3f& viewPosition) { viewPosition_ = viewPosition; }


	/**
	 * @brief ����Ʈ�� �����Դϴ�.
	 *
	 * @param lightDirection ������ ����Ʈ�� ��ġ�Դϴ�.
	 */
	void SetLightDirection(const Vec3f& lightDirection) { lightDirection_ = lightDirection; }


	/**
	 * @brief ����Ʈ�� �����Դϴ�.
	 *
	 * @param lightColor ������ ����Ʈ�� RGB �����Դϴ�.
	 */
	void SetLightColor(const Vec3f& lightColor) { lightColor_ = lightColor; }


	/**
	 * @brief �׸��� ������ �� ������ �ε��� ���� �����մϴ�.
	 *
	 * @param shadowMap ������ �ε��� ���Դϴ�.
	 */
	void SetShadowMap(ITexture2D* shadowMap) { shadowMap_ = shadowMap; }

	
	/**
	 * @brief ���� �޽ø� �׸��ϴ�.
	 * 
	 * @param world ���� ����Դϴ�.
	 * @param mesh ���� �޽� ���ҽ��Դϴ�.
	 * @param material ���� �޽��� �����Դϴ�.
	 */
	void DrawStaticMesh3D(const Mat4x4& world, IMesh* mesh, ITexture2D* material);


	/**
	 * @brief ��Ű�� �޽ø� �׸��ϴ�.
	 * 
	 * @param world ���� ����Դϴ�.
	 * @param mesh ���� �޽� ���ҽ��Դϴ�.
	 * @param bindPose ���ε� ���� ��� ����Դϴ�.
	 * @param invBindPose �� ���ε� ���� ��� ����Դϴ�.
	 * @param material ���� �޽��� �����Դϴ�.
	 */
	void DrawSkinnedMesh3D(const Mat4x4& world, IMesh* mesh, const std::vector<Mat4x4>& bindPose, const std::vector<Mat4x4>& invBindPose, ITexture2D* material);


private:
	/**
	 * @brief �������� �� ����Դϴ�.
	 */
	Mat4x4 view_;


	/**
	 * @brief �������� ���� ����Դϴ�.
	 */
	Mat4x4 projection_;


	/**
	 * @brief ����Ʈ ������ �þ� ����Դϴ�.
	 */
	Mat4x4 lightView_;


	/**
	 * @brief ����Ʈ ������ ���� ����Դϴ�.
	 */
	Mat4x4 lightProjection_;


	/**
	 * @brief ī�޶��� ��ġ�Դϴ�.
	 */
	Vec3f viewPosition_ = Vec3f(0.0f, 0.0f, 0.0f);


	/**
	 * @brief ����Ʈ�� �����Դϴ�.
	 */
	Vec3f lightDirection_ = Vec3f(0.0f, 0.0f, 0.0f);


	/**
	 * @brief ����Ʈ�� �����Դϴ�.
	 */
	Vec3f lightColor_ = Vec3f(1.0f, 1.0f, 1.0f);


	/**
	 * @brief �׸��� ������ �� ������ ���� ���Դϴ�.
	 */
	ITexture2D* shadowMap_ = nullptr;


	/**
	 * @brief �ε��� ���� ���ε� �����Դϴ�.
	 */
	static const uint32_t SHADOW_MAP_BIND_SLOT = 0;


	/**
	 * @brief ���͸����� ���ε� �����Դϴ�.
	 */
	static const uint32_t MATERIAL_BIND_SLOT = 1;


	/**
	 * @brief ���� �޽ø� �������ϴ� ���̴��Դϴ�.
	 */
	Shader* staticMeshShader_ = nullptr;


	/**
	 * @brief ��Ű�� �޽ø� �������ϴ� ���̴��Դϴ�.
	 */
	Shader* skinnedMeshShader_ = nullptr;
};