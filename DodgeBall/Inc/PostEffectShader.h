#pragma once

#include <array>

#include "Shader.h"

class Framebuffer; // ������ ���� ���ҽ��� ����ϱ� ���� ���� �����Դϴ�.


/**
 * @brief ��ó�� ȿ���� �����ϴ� ���̴��Դϴ�.
 */
class PostEffectShader : public Shader
{
public:
	/**
	 * @brief ��ó�� ȿ�� ���̴��� ����Ʈ �������Դϴ�.
	 *
	 * @note ������ �̿��� �޼��忡�� ������ �ʱ�ȭ�� �����ؾ� �մϴ�.
	 */
	PostEffectShader() = default;


	/**
	 * @brief ��ó�� ȿ�� ���̴��� ���� �Ҹ����Դϴ�.
	 *
	 * @note ��ó�� ȿ�� ���̴��� ���ο��� �Ҵ�� ��Ҹ� �����ϱ� ���ؼ��� �ݵ�� Release�� ȣ���ؾ� �մϴ�.
	 */
	virtual ~PostEffectShader();


	/**
	 * @brief ��ó�� ȿ�� ���̴��� ���� �����ڿ� ���� �����ڸ� ��������� �����մϴ�.
	 */
	DISALLOW_COPY_AND_ASSIGN(PostEffectShader);


	/**
	 * @brief GLSL ���̴� �ҽ� ������ �������ϰ� ���̴� ���α׷��� �����մϴ�.
	 *
	 * @param vsFile ���ؽ� ���̴��� Ȯ����(.vert)�� ������ ����Դϴ�.
	 * @param fsFile �����׸�Ʈ ���̴��� Ȯ����(.frag)�� ������ ����Դϴ�.
	 */
	virtual void Initialize(const std::wstring& vsPath, const std::wstring& fsPath) override;


	/**
	 * @brief ��ó�� ȿ�� ���̴��� ���� ���ҽ��� �Ҵ� �����մϴ�.
	 */
	virtual void Release() override;


	/**
	 * @brief ��ó�� ȿ���� ������ �� ���ε��� ������ ���ۿ� �����մϴ�.
	 * 
	 * @param framebuffer ��ó�� ȿ���� ������ ������ �����Դϴ�.
	 */
	void BlitEffect(Framebuffer* framebuffer);


protected:
	/**
	 * @brief ��ó�� ���̴� ���ο��� ����ϴ� �����Դϴ�.
	 */
	struct VertexPositionTexture
	{
		/**
		 * @brief ��ġ�� �ؽ�ó ������ ���� ������ �⺻ �������Դϴ�.
		 */
		VertexPositionTexture() noexcept
			: position_(0.0f, 0.0f, 0.0f)
			, uv_(0.0f, 0.0f) {}


		/**
		 * @brief ��ġ�� �ؽ�ó ������ ���� ������ �������Դϴ�.
		 *
		 * @param position ������ ��ġ�Դϴ�.
		 * @param uv ������ �ؽ�ó ��ġ�Դϴ�.
		 */
		VertexPositionTexture(Vector3f&& position, Vector2f&& uv) noexcept
			: position_(position)
			, uv_(uv) {}


		/**
		 * @brief ��ġ�� �ؽ�ó ������ ���� ������ �������Դϴ�.
		 *
		 * @param position ������ ��ġ�Դϴ�.
		 * @param st ������ �ؽ�ó ��ġ�Դϴ�.
		 */
		VertexPositionTexture(const Vector3f& position, const Vector2f& uv) noexcept
			: position_(position)
			, uv_(uv) {}


		/**
		 * @brief ��ġ�� �ؽ�ó ������ ���� ������ �������Դϴ�.
		 *
		 * @param x ��ġ�� X��ǥ�Դϴ�.
		 * @param y ��ġ�� Y��ǥ�Դϴ�.
		 * @param z ��ġ�� Z��ǥ�Դϴ�.
		 * @param u �ؽ�ó ��ġ�� U��ǥ�Դϴ�.
		 * @param v �ؽ�ó ��ġ�� V��ǥ�Դϴ�.
		 */
		VertexPositionTexture(
			float x, float y, float z,
			float u, float v
		) noexcept
			: position_(x, y, z)
			, uv_(u, v) {}


		/**
		 * @brief ��ġ�� �ؽ�ó ������ ���� ������ �������Դϴ�.
		 *
		 * @param instance ������ ���� �ν��Ͻ��Դϴ�.
		 */
		VertexPositionTexture(VertexPositionTexture&& instance) noexcept
			: position_(instance.position_)
			, uv_(instance.uv_) {}


		/**
		 * @brief ��ġ�� �ؽ�ó ������ ���� ������ �������Դϴ�.
		 *
		 * @param instance ������ ���� �ν��Ͻ��Դϴ�.
		 */
		VertexPositionTexture(const VertexPositionTexture& instance) noexcept
			: position_(instance.position_)
			, uv_(instance.uv_) {}


		/**
		 * @brief ��ġ�� �ؽ�ó ������ ���� ������ ���� �������Դϴ�.
		 *
		 * @param instance ������ ���� �ν��Ͻ��Դϴ�.
		 *
		 * @return ������ ��ü�� �����ڸ� ��ȯ�մϴ�.
		 */
		VertexPositionTexture& operator=(VertexPositionTexture&& instance) noexcept
		{
			if (this == &instance) return *this;

			position_ = instance.position_;
			uv_ = instance.uv_;

			return *this;
		}


		/**
		 * @brief ��ġ�� �ؽ�ó ������ ���� ������ ���� �������Դϴ�.
		 *
		 * @param instance ������ ���� �ν��Ͻ��Դϴ�.
		 *
		 * @return ������ ��ü�� �����ڸ� ��ȯ�մϴ�.
		 */
		VertexPositionTexture& operator=(const VertexPositionTexture& instance) noexcept
		{
			if (this == &instance) return *this;

			position_ = instance.position_;
			uv_ = instance.uv_;

			return *this;
		}


		/**
		 * @brief ������ ����Ʈ ���� ���� ����ϴ�.
		 *
		 * @return ������ ����Ʈ ����(Stride) ���� ��ȯ�մϴ�.
		 */
		static uint32_t GetStride()
		{
			return sizeof(VertexPositionTexture);
		}


		/**
		 * @brief ������ ��ġ�Դϴ�.
		 */
		Vector3f position_;


		/**
		 * @brief ������ �ؽ�ó ��ǥ�Դϴ�.
		 */
		Vector2f uv_;
	};


protected:
	/**
	 * @brief ������ ���� ���� ����� �ִ� ũ���Դϴ�.
	 */
	static const int32_t MAX_VERTEX_SIZE = 6;


	/**
	 * @brief ������ ������ ���� ����Դϴ�.
	 */
	std::array<VertexPositionTexture, MAX_VERTEX_SIZE> vertices_;


	/**
	 * @brief ���� ������ ������Ʈ�Դϴ�.
	 */
	uint32_t vertexBufferObject_ = 0;


	/**
	 * @brief ���� ���� ����� ������Ʈ�Դϴ�.
	 */
	uint32_t vertexArrayObject_ = 0;
};