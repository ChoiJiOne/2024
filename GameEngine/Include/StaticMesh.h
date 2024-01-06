#pragma once

#include <vector>

#include "IResource.h"
#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"


/**
 * @brief OpenGL ���������ο� ���ε� ������ ���� �޽� ���ҽ��Դϴ�.
 */
class StaticMesh : public IResource
{
public:
	/**
	 * @brief ����(Vertex)�Դϴ�.
	 */
	struct Vertex
	{
		/**
		 * @brief ��ġ ������ ���� ������ �⺻ �������Դϴ�.
		 */
		Vertex() noexcept
			: position(0.0f, 0.0f, 0.0f)
			, normal(0.0f, 0.0f, 0.0f)
			, texture(0.0f, 0.0f) {}


		/**
		 * @brief ��ġ ������ ���� ������ �������Դϴ�.
		 *
		 * @param p ������ ��ġ�Դϴ�.
		 * @param n ������ ���� �����Դϴ�.
		 * @param uv ������ �ؼ��Դϴ�.
		 */
		Vertex(Vector3f&& p, Vector3f&& n, Vector2f&& uv) noexcept
			: position(p)
			, normal(n)
			, texture(uv) {}

		
		/**
		 * @brief ��ġ ������ ���� ������ �������Դϴ�.
		 *
		 * @param p ������ ��ġ�Դϴ�.
		 * @param n ������ ���� �����Դϴ�.
		 * @param uv ������ �ؼ��Դϴ�.
		 */
		Vertex(const Vector3f& p, const Vector3f& n, const Vector2f& uv) noexcept
			: position(p)
			, normal(n)
			, texture(uv) {}
		

		/**
		 * @brief ��ġ ������ ���� ������ �������Դϴ�.
		 *
		 * @param instance ������ ���� �ν��Ͻ��Դϴ�.
		 */
		Vertex(Vertex&& instance) noexcept
			: position(instance.position)
			, normal(instance.normal)
			, texture(instance.texture) {}


		/**
		 * @brief ��ġ ������ ���� ������ �������Դϴ�.
		 *
		 * @param instance ������ ���� �ν��Ͻ��Դϴ�.
		 */
		Vertex(const Vertex& instance) noexcept
			: position(instance.position)
			, normal(instance.normal)
			, texture(instance.texture) {}


		/**
		 * @brief ��ġ ������ ���� ������ ���� �������Դϴ�.
		 *
		 * @param instance ������ ���� �ν��Ͻ��Դϴ�.
		 *
		 * @return ������ ��ü�� �����ڸ� ��ȯ�մϴ�.
		 */
		Vertex& operator=(Vertex&& instance) noexcept
		{
			if (this == &instance) return *this;

			position = instance.position;
			normal = instance.normal;
			texture = instance.texture;

			return *this;
		}


		/**
		 * @brief ��ġ ������ ���� ������ ���� �������Դϴ�.
		 *
		 * @param instance ������ ���� �ν��Ͻ��Դϴ�.
		 *
		 * @return ������ ��ü�� �����ڸ� ��ȯ�մϴ�.
		 */
		Vertex& operator=(const Vertex& instance) noexcept
		{
			if (this == &instance) return *this;

			position = instance.position;
			normal = instance.normal;
			texture = instance.texture;

			return *this;
		}


		/**
		 * @brief ������ ����Ʈ ���� ���� ����ϴ�.
		 *
		 * @return ������ ����Ʈ ����(Stride) ���� ��ȯ�մϴ�.
		 */
		static uint32_t GetStride()
		{
			return sizeof(Vertex);
		}


		/**
		 * @brief ������ ��ġ�Դϴ�.
		 */
		Vector3f position;


		/**
		 * @brief ������ ���� �����Դϴ�.
		 */
		Vector3f normal;


		/**
		 * @brief ������ �ؼ��Դϴ�.
		 */
		Vector2f texture;
	};


public:
	/**
	 * @brief �޽��� ����Ʈ �������Դϴ�.
	 * 
	 * @note ������ �̿��� �޼��忡�� ������ �ʱ�ȭ�� �����ؾ� �մϴ�.
	 */
	StaticMesh() = default;


	/**
	 * @brief �޽��� ���� �Ҹ����Դϴ�.
	 * 
	 * @note �޽� ���ο��� �Ҵ�� ��Ҹ� �����ϱ� ���ؼ��� �ݵ�� Release�� ȣ���ؾ� �մϴ�.
	 */
	virtual ~StaticMesh();


	/**
	 * @brief �޽��� ���� �����ڿ� ���� �����ڸ� ��������� �����մϴ�.
	 */
	DISALLOW_COPY_AND_ASSIGN(StaticMesh);


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
	void SetupMesh(const void* vertexBufferPtr, uint32_t vertexBufferSize, const void* indexBufferPtr, uint32_t indexBufferSize);


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