#pragma once

#include <array>

#include "IResource.h"
#include "RenderModule.h"
#include "VertexBuffer.h"

class FrameBuffer;
class Shader;


/**
 * @brief ������ ���ۿ� ��ó�� ȿ���� �����մϴ�.
 */
class PostEffectComposer : public IResource
{
public:
	/**
	 * @brief ������ ���ۿ� ��ó�� ȿ���� �����ϴ� ��ü�� ����Ʈ �������Դϴ�.
	 */
	explicit PostEffectComposer();


	/**
	 * @brief ������ ���ۿ� ��ó�� ȿ���� �����ϴ� ��ü�� ���� �Ҹ����Դϴ�.
	 *
	 * @note ���ο��� �Ҵ�� ��Ҹ� �����ϱ� ���ؼ��� �ݵ�� Release�� ȣ���ؾ� �մϴ�.
	 */
	virtual ~PostEffectComposer();


	/**
	 * @brief ������ ���ۿ� ��ó�� ȿ���� �����ϴ� ��ü�� ���� �����ڿ� ���� �����ڸ� ��������� �����մϴ�.
	 */
	DISALLOW_COPY_AND_ASSIGN(PostEffectComposer);


	/**
	 * @brief ���� ���ҽ��� �Ҵ� �����մϴ�.
	 */
	virtual void Release() override;


	/**
	 * @brief ������ ���� �������� �����մϴ�.
	 * 
	 * @param framebuffer ������ ������ �����Դϴ�.
	 * @param index ������ ������ �÷� ���� �ε����Դϴ�.
	 */
	void Blit(FrameBuffer* framebuffer, uint32_t index);


private:
	/**
	 * @brief ���ο����� ����ϴ� �����Դϴ�.
	 */
	struct Vertex
	{
		/**
		 * @brief ������ �⺻ �������Դϴ�.
		 */
		Vertex() noexcept : position(0.0f, 0.0f) {}


		/**
		 * @brief ������ �������Դϴ�.
		 *
		 * @param p ������ ��ġ�Դϴ�.
		 */
		Vertex(Vec2f&& p) noexcept : position(p) {}


		/**
		 * @brief ������ �������Դϴ�.
		 *
		 * @param p ������ ��ġ�Դϴ�.
		 */
		Vertex(const Vec2f& p) noexcept : position(p) {}


		/**
		 * @brief ������ �������Դϴ�.
		 *
		 * @param x ��ġ�� X��ǥ�Դϴ�.
		 * @param y ��ġ�� Y��ǥ�Դϴ�.
		 */
		Vertex(float x, float y) noexcept : position(x, y) {}


		/**
		 * @brief ������ �������Դϴ�.
		 *
		 * @param instance ������ ���� �ν��Ͻ��Դϴ�.
		 */
		Vertex(Vertex&& instance) noexcept
			: position(instance.position) {}


		/**
		 * @brief ������ �������Դϴ�.
		 *
		 * @param instance ������ ���� �ν��Ͻ��Դϴ�.
		 */
		Vertex(const Vertex& instance) noexcept
			: position(instance.position) {}


		/**
		 * @brief ������ ���� �������Դϴ�.
		 *
		 * @param instance ������ ���� �ν��Ͻ��Դϴ�.
		 *
		 * @return ������ ��ü�� �����ڸ� ��ȯ�մϴ�.
		 */
		Vertex& operator=(Vertex&& instance) noexcept
		{
			if (this == &instance) return *this;

			position = instance.position;

			return *this;
		}


		/**
		 * @brief ������ ���� �������Դϴ�.
		 *
		 * @param instance ������ ���� �ν��Ͻ��Դϴ�.
		 *
		 * @return ������ ��ü�� �����ڸ� ��ȯ�մϴ�.
		 */
		Vertex& operator=(const Vertex& instance) noexcept
		{
			if (this == &instance) return *this;

			position = instance.position;

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
		Vec2f position;
	};


private:
	/**
	 * @brief ���� ����� �ִ� ũ���Դϴ�.
	 */
	static const int32_t MAX_VERTEX_SIZE = 6;


	/**
	 * @brief ���� ���� ����� ������Ʈ�Դϴ�.
	 */
	uint32_t vertexArrayObject_ = 0;


	/**
	 * @brief ���ο��� ����� ���� �����Դϴ�.
	 */
	VertexBuffer* vertexBuffer_ = nullptr;


	/**
	 * @brief ������ ������ ���� �����ϴ� ���̴��Դϴ�.
	 */
	Shader* blit_ = nullptr;


	/**
	 * @brief ������ ������ ���ε� �����Դϴ�.
	 */
	static const uint32_t FRAME_BUFFER_BIND_SLOT = 0;
};