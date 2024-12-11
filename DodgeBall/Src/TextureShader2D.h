#pragma once

#include <array>

#include "Shader.h"

class Texture2D; // Texture2D�� ����ϱ� ���� ���� �����Դϴ�.


/**
 * @brief 2D �ؽ�ó�� �������ϴ� ���̴��Դϴ�.
 *
 * @note
 * - 2D �ؽ�ó ������ �� ������ �Ǵ� ��ǥ��� ������ ��ǥ���Դϴ�.
 * - ��ġ�� ũ�� ���� ���ڸ� ���� �ʰ� �������ϴ� �޼���� ������ ȭ�� ��ü�� �������� �մϴ�.
 */
class TextureShader2D : public Shader
{
public:
	/**
	 * @brief 2D �ؽ�ó�� �������ϴ� ���̴��� ����Ʈ �������Դϴ�.
	 *
	 * @note ������ �̿��� �޼��忡�� ������ �ʱ�ȭ�� �����ؾ� �մϴ�.
	 */
	TextureShader2D() = default;


	/**
	 * @brief 2D �ؽ�ó�� �������ϴ� ���̴��� ���� �Ҹ����Դϴ�.
	 *
	 * @note ���̴��� ���ο��� �Ҵ�� ��Ҹ� �����ϱ� ���ؼ��� �ݵ�� Release�� ȣ���ؾ� �մϴ�.
	 */
	virtual ~TextureShader2D();


	/**
	 * @brief 2D �ؽ�ó�� �������ϴ� ���̴��� ���� �����ڿ� ���� �����ڸ� ��������� �����մϴ�.
	 */
	DISALLOW_COPY_AND_ASSIGN(TextureShader2D);


	/**
	 * @brief GLSL ���̴� �ҽ� ������ �������ϰ� ���̴� ���α׷��� �����մϴ�.
	 *
	 * @param vsFile ���ؽ� ���̴��� Ȯ����(.vert)�� ������ ����Դϴ�.
	 * @param fsFile �����׸�Ʈ ���̴��� Ȯ����(.frag)�� ������ ����Դϴ�.
	 */
	virtual void Initialize(const std::wstring& vsPath, const std::wstring& fsPath) override;


	/**
	 * @brief ���̴��� ���� ���ҽ��� �Ҵ� �����մϴ�.
	 */
	virtual void Release() override;


	/**
	 * @brief 2D �ؽ�ó�� ȭ�鿡 �׸��ϴ�.
	 *
	 * @param ortho ���� ���� ����Դϴ�.
	 * @param texture �ؽ�ó ���ҽ��Դϴ�.
	 * @param center �ؽ�ó�� �߽� ��ǥ�Դϴ�.
	 * @param width �ؽ�ó�� ���� ũ���Դϴ�.
	 * @param height �ؽ�ó�� ���� ũ���Դϴ�.
	 * @param rotate �ؽ�ó�� ���� ȸ�� �����Դϴ�.
	 * @param transparent �ؽ�ó�� �����Դϴ�. �⺻ ���� 1.0f(������)�Դϴ�.
	 */
	void DrawTexture2D(
		const Matrix4x4f& ortho,
		const Texture2D* texture,
		const Vector2f& center,
		float width,
		float height,
		float rotate,
		float transparent = 1.0f
	);


	/**
	 * @brief 2D �ؽ�ó�� ȭ�鿡 �׸��ϴ�.
	 *
	 * @note 2D �ؽ�ó�� ������ ��ü�� ä�������� �׸��ϴ�.
	 *
	 * @param texture �ؽ�ó ���ҽ��Դϴ�.
	 * @param transparent �ؽ�ó�� �����Դϴ�. �⺻ ���� 1.0f(������)�Դϴ�.
	 */
	void DrawTexture2D(const Texture2D* texture, float transparent = 1.0f);


	/**
	 * @brief ���η� ��ũ�ѵ� 2D �ؽ�ó�� �׸��ϴ�.
	 *
	 * @note
	 * - 2D �ؽ�ó�� ������ ��ü�� ä�������� �׸��ϴ�.
	 * - �ؽ�ó ���� ������ ������ �����ϴ�.
	 * ������������������������������������������������������������������
	 * ��            ��                  ��
	 * ��            ��                  ��
	 * ��            ��                  ��
	 * ��            ��                  ��
	 * �� 1.0f - rate��       rate       ��
	 * ��            ��                  ��
	 * ��            ��                  ��
	 * ��            ��                  ��
	 * ������������������������������������������������������������������
	 *
	 * @param texture �ؽ�ó ���ҽ��Դϴ�.
	 * @param rate ���� �����Դϴ�. ���� ������ 0.0f ~ 1.0f �Դϴ�.
	 * @param transparent �ؽ�ó�� �����Դϴ�. �⺻ ���� 1.0f(������)�Դϴ�.
	 */
	void DrawHorizonScrollTexture2D(const Texture2D* texture, float rate, float transparent = 1.0f);


	/**
	 * @brief ���η� ��ũ�ѵ� 2D �ؽ�ó�� �׸��ϴ�.
	 *
	 * @note
	 * - �ؽ�ó ���� ������ ������ �����ϴ�.
	 * ������������������������������������������������������������������
	 * ��            ��                  ��
	 * ��            ��                  ��
	 * ��            ��                  ��
	 * ��            ��                  ��
	 * �� 1.0f - rate��       rate       ��
	 * ��            ��                  ��
	 * ��            ��                  ��
	 * ��            ��                  ��
	 * ������������������������������������������������������������������
	 *
	 * @param ortho ���� ���� ����Դϴ�.
	 * @param texture �ؽ�ó ���ҽ��Դϴ�.
	 * @param center �ؽ�ó�� �߽� ��ǥ�Դϴ�.
	 * @param width �ؽ�ó�� ���� ũ���Դϴ�.
	 * @param height �ؽ�ó�� ���� ũ���Դϴ�.
	 * @param rotate �ؽ�ó�� ȸ�� �����Դϴ�. ������ �����Դϴ�.
	 * @param rate ���� �����Դϴ�. ���� ������ 0.0f ~ 1.0f �Դϴ�.
	 * @param transparent �ؽ�ó�� �����Դϴ�. �⺻ ���� 1.0f(������)�Դϴ�.
	 */
	void DrawHorizonScrollTexture2D(
		const Matrix4x4f& ortho,
		const Texture2D* texture,
		const Vector2f& center,
		float width,
		float height,
		float rotate,
		float rate,
		float transparent = 1.0f
	);


	/**
	 * @brief ���η� ��ũ�ѵ� 2D �ؽ�ó�� �׸��ϴ�.
	 *
	 * @note
	 * - 2D �ؽ�ó�� ������ ��ü�� ä�������� �׸��ϴ�.
	 * - �ؽ�ó ���� ������ ������ �����ϴ�.
	 * ��������������������������������������������������������������
	 * ��                             ��
	 * ��                             ��
	 * ��              rate           ��
	 * ��                             ��
	 * ��������������������������������������������������������������
	 * ��                             ��
	 * ��          1.0f - rate        ��
	 * ��                             ��
	 * ��������������������������������������������������������������
	 *
	 * @param texture �ؽ�ó ���ҽ��Դϴ�.
	 * @param rate ���� �����Դϴ�. ���� ������ 0.0f ~ 1.0f �Դϴ�.
	 * @param transparent �ؽ�ó�� �����Դϴ�. �⺻ ���� 1.0f(������)�Դϴ�.
	 */
	void DrawVerticalScrollTexture2D(const Texture2D* texture, float rate, float transparent = 1.0f);


	/**
	 * @brief ���η� ��ũ�ѵ� 2D �ؽ�ó�� �׸��ϴ�.
	 *
	 * @note
	 * - �ؽ�ó ���� ������ ������ �����ϴ�.
	 * ��������������������������������������������������������������
	 * ��                             ��
	 * ��                             ��
	 * ��              rate           ��
	 * ��                             ��
	 * ��������������������������������������������������������������
	 * ��                             ��
	 * ��          1.0f - rate        ��
	 * ��                             ��
	 * ��������������������������������������������������������������
	 *
	 * @param ortho ���� ���� ����Դϴ�.
	 * @param texture �ؽ�ó ���ҽ��Դϴ�.
	 * @param center �ؽ�ó�� �߽� ��ǥ�Դϴ�.
	 * @param width �ؽ�ó�� ���� ũ���Դϴ�.
	 * @param height �ؽ�ó�� ���� ũ���Դϴ�.
	 * @param rotate �ؽ�ó�� ȸ�� �����Դϴ�. ������ �����Դϴ�.
	 * @param rate ���� �����Դϴ�. ���� ������ 0.0f ~ 1.0f �Դϴ�.
	 * @param transparent �ؽ�ó�� �����Դϴ�. �⺻ ���� 1.0f(������)�Դϴ�.
	 */
	void DrawVerticalScrollTexture2D(
		const Matrix4x4f& ortho,
		const Texture2D* texture,
		const Vector2f& center,
		float width,
		float height,
		float rotate,
		float rate,
		float transparent = 1.0f
	);


	/**
	 * @brief 2D �ؽ�ó�� �ܰ����� ȭ�鿡 �׸��ϴ�.
	 *
	 * @param ortho ���� ���� ����Դϴ�.
	 * @param texture �ؽ�ó ���ҽ��Դϴ�.
	 * @param center �ؽ�ó�� �߽� ��ǥ�Դϴ�.
	 * @param width �ؽ�ó�� ���� ũ���Դϴ�.
	 * @param height �ؽ�ó�� ���� ũ���Դϴ�.
	 * @param rotate �ؽ�ó�� ���� ȸ�� �����Դϴ�.
	 * @param silhouetteRGB �ؽ�ó �Ƿ翧�� �����Դϴ�.
	 * @param transparent �ؽ�ó�� �����Դϴ�. �⺻ ���� 1.0f �Դϴ�.
	 * 
	 * @see https://github.com/gdquest-demos/godot-shaders/blob/master/godot/Shaders/outline2D_outer.shader
	 */
	void DrawOutlineTexture2D(
		const Matrix4x4f& ortho,
		const Texture2D* texture,
		const Vector2f& center,
		float width,
		float height,
		float rotate,
		const Vector4f& outline,
		float transparent = 1.0f
	);


private:
	/**
	 * @brief 2D �ؽ�ó �׸��⸦ �����ϴ� ���̴� ���ο��� ����ϴ� �����Դϴ�.
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


	/**
	 * @brief �ؽ�ó �׸��⸦ �����մϴ�.
	 *
	 * @param transform ��ȯ ����Դϴ�.
	 * @param ortho ���� ����Դϴ�.
	 * @param texture �ؽ�ó ���ҽ��Դϴ�.
	 * @param vertexCount ���� ���Դϴ�.
	 * @param bIsActiveOutline �ؽ�ó�� �ܰ��� Ȱ��ȭ �����Դϴ�.
	 * @param transparent �ؽ�ó�� �����Դϴ�.
	 * @param outline �ؽ�ó�� �ܰ��� �����Դϴ�. �⺻ ���� ����Դϴ�.
	 */
	void DrawTexture2D(const Matrix4x4f& transform, const Matrix4x4f& ortho, uint32_t vertexCount, const Texture2D* texture, bool bIsActiveOutline, float transparent, const Vector4f& outline = Vector4f(1.0f, 1.0f, 1.0f, 1.0f));


private:
	/**
	 * @brief �ؽ�ó ���� ����� �ִ� ũ���Դϴ�.
	 */
	static const int32_t MAX_VERTEX_SIZE = 12;


	/**
	 * @brief �ؽ�ó�� ���� ����Դϴ�.
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