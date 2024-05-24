#pragma once

#include <vector>

#include "IMesh.h"
#include "IndexBuffer.h"
#include "Vertex3D.h"
#include "VertexBuffer.h"

class Skeleton;
class Pose;


/**
 * @brief ��Ű�� �޽� ���ҽ��Դϴ�.
 */
class SkinnedMesh : public IMesh
{
public:
	/**
	 * @brief �޽� ���ҽ��� �����մϴ�.
	 * 
	 * @param vertices �޽��� ���� ����Դϴ�.
	 * @param indices �޽��� �ε��� ����Դϴ�.
	 * @param ��Ű�׵� ���� ����� GPU�� ������ �� �����Դϴ�.
	 */
	explicit SkinnedMesh(const std::vector<VertexPositionNormalUvSkin3D>& vertices, const std::vector<uint32_t>& indices, bool bIsUploadGPU);


	/**
	 * @brief �޽��� ���� �Ҹ����Դϴ�.
	 */
	virtual ~SkinnedMesh();


	/**
	 * @brief �޽��� ���� ������ �� ���� �����ڸ� ��������� �����մϴ�.
	 */
	DISALLOW_COPY_AND_ASSIGN(SkinnedMesh);


	/**
	 * @brief �޽��� ���� ���ҽ��� �Ҵ� �����մϴ�.
	 */
	virtual void Release() override;


	/**
	 * @brief �޽� ���ҽ��� ���������ο� ���ε��մϴ�.
	 */
	virtual void Bind() override;


	/**
	 * @brief ���ε��� �޽� ���ҽ��� ���ε� �����մϴ�.
	 */
	virtual void Unbind() override;


	/**
	 * @brief �޽��� �ε��� ���� ����ϴ�.
	 *
	 * @return �޽��� �ε��� ���� ��ȯ�մϴ�.
	 */
	virtual uint32_t GetIndexCount() const override { return static_cast<uint32_t>(indices_.size()); }


	/**
	 * @brief �޽��� ���� ���� ����ϴ�.
	 *
	 * @return �޽��� ���� ���� ��ȯ�մϴ�.
	 */
	virtual uint32_t GetVertexCount() const override { return static_cast<uint32_t>(vertices_.size()); }


	/**
	 * @brief �޽��� ���� ����� ����ϴ�.
	 *
	 * @return �޽��� ���� ��� ��� �����ڸ� ��ȯ�մϴ�.
	 */
	const std::vector<VertexPositionNormalUvSkin3D>& GetVertices() const { return vertices_; }


	/**
	 * @brief �޽��� ��Ű�׵� ���� ����� ����ϴ�.
	 *
	 * @return �޽��� ���� ��� ��� �����ڸ� ��ȯ�մϴ�.
	 */
	const std::vector<VertexPositionNormalUvSkin3D>& GetSkinnedVertices() const { return skinnedVertices_; }


	/**
	 * @brief �޽� ��Ű���� �����մϴ�.
	 * 
	 * @param skeleton ��Ű�� ���� �� ������ �����Դϴ�. 
	 * @param pose ��Ű�� ���� �� ������ �����Դϴ�.
	 */
	void Skin(Skeleton* skeleton, Pose* pose);


private:
	/**
	 * @brief ���� ����Դϴ�.
	 */
	std::vector<VertexPositionNormalUvSkin3D> vertices_;


	/**
	 * @brief ��Ű�׵� ���� ����Դϴ�.
	 */
	std::vector<VertexPositionNormalUvSkin3D> skinnedVertices_;


	/**
	 * @brief GPU ���� ���� ���� ������Ʈ�Դϴ�.
	 */
	VertexBuffer* vertexBuffer_ = nullptr;


	/**
	 * @brief ���� ��Ͽ� �����ϴ� �ε��� ����Դϴ�.
	 */
	std::vector<uint32_t> indices_;


	/**
	 * @brief GPU ���� �ε��� ���� ������Ʈ�Դϴ�.
	 */
	IndexBuffer* indexBuffer_ = nullptr;


	/**
	 * @brief ���� �����͸� �����ϴ� �� �ʿ��� ��� �����Դϴ�.
	 *
	 * @see
	 * - https://www.khronos.org/opengl/wiki/Vertex_Specification#:~:text=has%20the%20details.-,Vertex%20Array%20Object,-Vertex%20Array%20Object
	 * - https://registry.khronos.org/OpenGL-Refpages/gl4/html/glGenVertexArrays.xhtml
	 */
	uint32_t vertexArrayObject_ = 0;


	/**
	 * @brief ���� ��� ����Դϴ�.
	 */
	std::vector<Mat4x4> posePalette_;


	/**
	 * @brief ��Ű�׵� ���� ����� GPU�� ������ �� �����Դϴ�.
	 */
	bool bIsUploadGPU_ = false;
};