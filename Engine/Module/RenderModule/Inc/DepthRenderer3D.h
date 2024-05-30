#pragma once

#include <vector>

#include "Mat.h"

#include "IResource.h"

class Shader;
class IMesh;


/**
 * @brief 3D �޽��� ���� ���� �������ϴ� �������Դϴ�.
 */
class DepthRenderer3D : public IResource
{
public:
	/**
	 * @brief 3D �޽��� ���� ���� �������ϴ� �������� �������Դϴ�.
	 */
	DepthRenderer3D();


	/**
	 * @brief 3D �޽��� ���� ���� �������ϴ� �������� ���� �Ҹ����Դϴ�.
	 */
	virtual ~DepthRenderer3D();


	/**
	 * @brief 3D �޽��� ���� ���� �������ϴ� �������� ���� ������ �� ���� �����ڸ� ��������� �����մϴ�.
	 */
	DISALLOW_COPY_AND_ASSIGN(DepthRenderer3D);


	/**
	 * @brief 3D �޽��� ���� ���� �������ϴ� �������� ���� ���ҽ��� �Ҵ� �����մϴ�.
	 */
	virtual void Release() override;


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
	 * @brief ���� �޽ø� �׸��ϴ�.
	 *
	 * @param world ���� ����Դϴ�.
	 * @param mesh ���� �޽� ���ҽ��Դϴ�.
	 */
	void DrawStaticMesh3D(const Mat4x4& world, IMesh* mesh);


	/**
	 * @brief ��Ű�� �޽ø� �׸��ϴ�.
	 *
	 * @param world ���� ����Դϴ�.
	 * @param mesh ���� �޽� ���ҽ��Դϴ�.
	 * @param bindPose ���ε� ���� ��� ����Դϴ�.
	 * @param invBindPose �� ���ε� ���� ��� ����Դϴ�.
	 */
	void DrawSkinnedMesh3D(const Mat4x4& world, IMesh* mesh, const std::vector<Mat4x4>& bindPose, const std::vector<Mat4x4>& invBindPose);


private:
	/**
	 * @brief ����Ʈ ������ �þ� ����Դϴ�.
	 */
	Mat4x4 lightView_;


	/**
	 * @brief ����Ʈ ������ ���� ����Դϴ�.
	 */
	Mat4x4 lightProjection_;


	/**
	 * @brief ���� �޽ø� �������ϴ� ���̴��Դϴ�.
	 */
	Shader* staticMeshDepth_ = nullptr;


	/**
	 * @brief ��Ű�� �޽ø� �������ϴ� ���̴��Դϴ�.
	 */
	Shader* skinnedMeshDepth_ = nullptr;
};