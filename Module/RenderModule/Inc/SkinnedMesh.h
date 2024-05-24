#pragma once

#include <vector>

#include "IndexBuffer.h"
#include "IResource.h"
#include "Vertex3D.h"
#include "VertexBuffer.h"


/**
 * @brief ��Ű�� �޽� ���ҽ��Դϴ�.
 */
class SkinnedMesh : public IResource
{
public:
	/**
	 * @brief �޽� ���ҽ��� �����մϴ�.
	 * 
	 * @param vertices �޽��� ���� ����Դϴ�.
	 * @param indices �޽��� �ε��� ����Դϴ�.
	 */
	explicit SkinnedMesh(const std::vector<VertexPositionNormalUvSkin3D>& vertices, const std::vector<uint32_t>& indices);


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
	void Bind();


	/**
	 * @brief ���ε��� �޽� ���ҽ��� ���ε� �����մϴ�.
	 */
	void Unbind();


	/**
	 * @brief �޽��� �ε��� ���� ����ϴ�.
	 *
	 * @return �޽��� �ε��� ���� ��ȯ�մϴ�.
	 */
	uint32_t GetIndexCount() const { return static_cast<uint32_t>(indices_.size()); }


	/**
	 * @brief �޽��� ���� ����� ����ϴ�.
	 *
	 * @return �޽��� ���� ��� ��� �����ڸ� ��ȯ�մϴ�.
	 */
	const std::vector<VertexPositionNormalUvSkin3D>& GetVertices() const { return vertices_; }


private:
	/**
	 * @brief ���� ����Դϴ�.
	 */
	std::vector<VertexPositionNormalUvSkin3D> vertices_;


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
};