#pragma once

#include <vector>

#include "Mat.h"

#include "IResource.h"

class Shader;
class StaticMesh;
class SkinnedMesh;


/**
 * @brief �޽��� ���� ���� �������ϴ� �������Դϴ�.
 */
class DepthRenderer : public IResource
{
public:
	/**
	 * @brief ���� ���� �������ϴ� �������� ����Ʈ �������Դϴ�.
	 */
	explicit DepthRenderer();


	/**
	 * @brief ���� ���� �������ϴ� �������� ���� �Ҹ����Դϴ�.
	 *
	 * @note ������ ���ο��� �Ҵ�� ��Ҹ� �����ϱ� ���ؼ��� �ݵ�� Release�� ȣ���ؾ� �մϴ�.
	 */
	virtual ~DepthRenderer();


	/**
	 * @brief ���� ���� �������ϴ� �������� ���� �����ڿ� ���� �����ڸ� ��������� �����մϴ�.
	 */
	DISALLOW_COPY_AND_ASSIGN(DepthRenderer);


	/**
	 * @brief ������ ���� ���ҽ��� �Ҵ� �����մϴ�.
	 */
	virtual void Release() override;


	/**
	 * @brief ����Ʈ ������ ����� �����մϴ�.
	 *
	 * @param lightSpaceMatrix ������ ����Ʈ ������ ����Դϴ�.
	 */
	void SetLightSpaceMatrix(const Mat4x4& lightSpaceMatrix) { lightSpaceMatrix_ = lightSpaceMatrix; }


	/**
	 * @brief ���� �޽��� ���� ���� �������մϴ�.
	 * 
	 * @param world ���� �޽��� ���� ����Դϴ�.
	 * @param mesh ���� �޽� ���ҽ��Դϴ�.
	 */
	void DrawStaticMesh(const Mat4x4& world, const StaticMesh* mesh);


	/**
	 * @brief ��Ű�� �޽��� ���� ���� �������մϴ�.
	 *
	 * @param world ���� �޽��� ���� ����Դϴ�.
	 * @param bindPose ���ε� ���� ����Դϴ�.
	 * @param invBindPose �� ���ε� ���� ����Դϴ�.
	 * @param mesh ��Ű�� �޽� ���ҽ��Դϴ�.
	 */
	void DrawSkinnedMesh(const Mat4x4& world, const std::vector<Mat4x4>& bindPose, const std::vector<Mat4x4>& invBindPose, const SkinnedMesh* mesh);


private:
	/**
	 * @brief ����Ʈ ������ ����Դϴ�.
	 */
	Mat4x4 lightSpaceMatrix_;


	/**
	 * @brief ���� �޽��� ���� ���� �������� ���̴��Դϴ�.
	 */
	Shader* staticMeshShader_ = nullptr;


	/**
	 * @brief ��Ű�� �޽��� ���� ���� �������� ���̴��Դϴ�.
	 */
	Shader* skinnedMeshShader_ = nullptr;
};