#pragma once
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
	 * @param bIsUploadedToGPU ��Ű�׵� CPU ���� ���� ����� GPU�� ������ �� �����Դϴ�.
	 */
	explicit SkinnedMesh(const std::vector<VertexPositionNormalUvSkin3D>& vertices, const std::vector<uint32_t>& indices, bool bIsUploadedToGPU = false);


	/**
	 * @brief �޽��� ���� �Ҹ����Դϴ�.
	 *
	 * @note �޽� ���ο��� �Ҵ�� ��Ҹ� �����ϱ� ���ؼ��� �ݵ�� Release�� ȣ���ؾ� �մϴ�.
	 */
	virtual ~SkinnedMesh();


	/**
	 * @brief �޽��� ���� �����ڿ� ���� �����ڸ� ��������� �����մϴ�.
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


	/**
	 * @brief ��Ű�׵� ���� ����� ����ϴ�.
	 *
	 * @return ��Ű�׵� ���� ��� ��� �����ڸ� ��ȯ�մϴ�.
	 */
	const std::vector<VertexPositionNormalUvSkin3D>& GetSkinnedVertices() const { return skinnedVertices_; }


	/**
	 * @brief CPU ��Ű���� �����մϴ�.
	 *
	 * @param posePalette ���� ��Ű���� ������ �� ������ �����Դϴ�.
	 * @param invPosePalette ���� ��Ű���� ������ �� ������ �����Դϴ�.
	 * 
	 * @param posePalette ���� ��� ����Դϴ�.
	 * @param invPosePalette �� ���ε� ���� ��� ����Դϴ�.
	 */
	void Skin(const std::vector<Mat4x4>& posePalette, const std::vector<Mat4x4>& invPosePalette);


private:
	/**
	 * @brief ���� ���� ����Դϴ�.
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
	 * @brief ��Ű�׵� CPU ���� ���� �����͸� GPU�� ������ Ȯ���մϴ�.
	 */
	bool bIsUploadedToGPU_ = false;
};