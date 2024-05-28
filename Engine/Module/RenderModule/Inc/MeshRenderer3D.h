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
	 * @brief ���� �޽ø� �������ϴ� ���̴��Դϴ�.
	 */
	Shader* staticMeshShader_ = nullptr;


	/**
	 * @brief ��Ű�� �޽ø� �������ϴ� ���̴��Դϴ�.
	 */
	Shader* skinnedMeshShader_ = nullptr;
};