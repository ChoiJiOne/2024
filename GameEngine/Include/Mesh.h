#pragma once

#include <vector>

#include "IResource.h"
#include "Vertex.h"


/**
 * @brief OpenGL ���������ο� ���ε� ������ �޽� ���ҽ��Դϴ�.
 */
class Mesh : public IResource
{
public:
	/**
	 * @brief �޽��� ����Ʈ �������Դϴ�.
	 * 
	 * @note ������ �̿��� �޼��忡�� ������ �ʱ�ȭ�� �����ؾ� �մϴ�.
	 */
	Mesh() = default;


	/**
	 * @brief �޽��� ���� �Ҹ����Դϴ�.
	 * 
	 * @note �޽� ���ο��� �Ҵ�� ��Ҹ� �����ϱ� ���ؼ��� �ݵ�� Release�� ȣ���ؾ� �մϴ�.
	 */
	virtual ~Mesh();


	/**
	 * @brief �޽��� ���� �����ڿ� ���� �����ڸ� ��������� �����մϴ�.
	 */
	DISALLOW_COPY_AND_ASSIGN(Mesh);


	/**
	 * @brief �޽� ���ҽ��� �����մϴ�.
	 * 
	 * @param vertices �޽��� ���� ����Դϴ�.
	 * @param indices �޽��� �ε��� ����Դϴ�.
	 */
	void Initialize(const std::vector<Vertex>& vertices, const std::vector<uint32_t>& indices);


	/**
	 * @brief �޽��� ���� ���ҽ��� �Ҵ� �����մϴ�.
	 */
	virtual void Release() override;

	
	/**
	 * @brief �޽��� �ε��� ���� ����ϴ�.
	 * 
	 * @return �޽��� �ε��� ���� ��ȯ�մϴ�.
	 */
	uint32_t GetIndexCount() const { return indexCount_; }


	/**
	 * @brief �޽��� ���� �迭 ������Ʈ�� ����ϴ�.
	 * 
	 * @return �޽��� ���� �迭 ������Ʈ�� ��ȯ�մϴ�.
	 */
	uint32_t GetVertexArrayObject() const { return vertexArrayObject_; }


private:
	/**
	 * @brief �޽� ���ҽ��� �ʱ�ȭ�մϴ�.
	 * 
	 * @param vertexBufferPtr ���� ������ �������Դϴ�.
	 * @param vertexBufferSize ���� ������ ũ���Դϴ�.
	 * @param indexBufferPtr �ε��� ������ �������Դϴ�.
	 * @param indexBufferSize �ε��� ������ ũ���Դϴ�.
	 */
	void Initialize(const void* vertexBufferPtr, uint32_t vertexBufferSize, const void* indexBufferPtr, uint32_t indexBufferSize);


private:
	/**
	 * @brief �ε��� ������ ���Դϴ�.
	 */
	uint32_t indexCount_ = 0;


	/**
	 * @brief ���� �����͸� �����ϴ� �� �ʿ��� ��� �����Դϴ�.
	 * 
	 * @see 
	 * - https://www.khronos.org/opengl/wiki/Vertex_Specification#:~:text=has%20the%20details.-,Vertex%20Array%20Object,-Vertex%20Array%20Object
	 * - https://registry.khronos.org/OpenGL-Refpages/gl4/html/glGenVertexArrays.xhtml
	 */
	uint32_t vertexArrayObject_ = 0;


	/**
	 * @brief GPU ���� ���� ���� ������Ʈ�Դϴ�.
	 */
	uint32_t vertexBufferObject_ = 0;


	/**
	 * @brief GPU ���� �ε��� ���� ������Ʈ�Դϴ�.
	 */
	uint32_t indexBufferObject_ = 0;
};