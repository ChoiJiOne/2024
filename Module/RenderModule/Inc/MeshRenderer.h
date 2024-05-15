#pragma once

#include <array>
#include <vector>

#include "ITexture2D.h"
#include "Shader.h"
#include "Vertex3D.h"
#include "StaticMesh.h"


/**
 * @brief �޽ø� �������ϴ� �������Դϴ�.
 */
class MeshRenderer : public Shader
{
public:
	/**
	 * @brief �޽ø� �������ϴ� �������� ����Ʈ �������Դϴ�.
	 */
	explicit MeshRenderer();


	/**
	 * @brief �޽ø� �������ϴ� �������� ���� �Ҹ����Դϴ�.
	 *
	 * @note ������ ���ο��� �Ҵ�� ��Ҹ� �����ϱ� ���ؼ��� �ݵ�� Release�� ȣ���ؾ� �մϴ�.
	 */
	virtual ~MeshRenderer();


	/**
	 * @brief �޽ø� �������ϴ� �������� ���� �����ڿ� ���� �����ڸ� ��������� �����մϴ�.
	 */
	DISALLOW_COPY_AND_ASSIGN(MeshRenderer);


	/**
	 * @brief ������ ���� ���ҽ��� �Ҵ� �����մϴ�.
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
	 * @brief 3D �޽ø� �׸��ϴ�.
	 *
	 * @param mesh �׸��⸦ ������ 3D �޽��Դϴ�.
	 * @param world ���� ����Դϴ�.
	 * @param material �޽ÿ� ���ε� ���� �ؽ�ó�Դϴ�.
	 */
	void DrawMesh(StaticMesh<VertexPositionNormalUv3D>* mesh, const Mat4x4& world, ITexture2D* material);


private:
	/**
	 * @brief �������� �� ����Դϴ�.
	 */
	Mat4x4 view_;


	/**
	 * @brief �������� ���� ����Դϴ�.
	 */
	Mat4x4 projection_;
};