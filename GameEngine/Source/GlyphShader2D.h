#pragma once

#include <array>

#include "Shader.h"
#include "Vertex.h"

class TTFont; // TTFont�� ����ϱ� ���� ���� �����Դϴ�.


/**
 * @brief �۸����� �̿��ؼ� �ؽ�Ʈ�� �������ϴ� ���̴��Դϴ�.
 *
 * @note
 * - 2D �ؽ�Ʈ ������ �� ������ �Ǵ� ��ǥ��� ������ ��ǥ���Դϴ�.
 */
class GlyphShader2D : public Shader
{
public:
	/**
	 * @brief 2D �ؽ�Ʈ�� �������ϴ� ���̴��� ����Ʈ �������Դϴ�.
	 *
	 * @note ������ �̿��� �޼��忡�� ������ �ʱ�ȭ�� �����ؾ� �մϴ�.
	 */
	GlyphShader2D() = default;


	/**
	 * @brief 2D �ؽ�Ʈ�� �������ϴ� ���̴��� ���� �Ҹ����Դϴ�.
	 *
	 * @note ���̴��� ���ο��� �Ҵ�� ��Ҹ� �����ϱ� ���ؼ��� �ݵ�� Release�� ȣ���ؾ� �մϴ�.
	 */
	virtual ~GlyphShader2D();


	/**
	 * @brief 2D �ؽ�Ʈ�� �������ϴ� ���̴��� ���� �����ڿ� ���� �����ڸ� ��������� �����մϴ�.
	 */
	DISALLOW_COPY_AND_ASSIGN(GlyphShader2D);


	/**
	 * @brief GLSL ���̴� �ҽ� ������ �������ϰ� ���̴� ���α׷��� �����մϴ�.
	 *
	 * @param vsFile ���ؽ� ���̴��� Ȯ����(.vert)�� ������ ����Դϴ�.
	 * @param fsFile �����׸�Ʈ ���̴��� Ȯ����(.frag)�� ������ ����Դϴ�.
	 * @param bCheckValid ���̴� ������ ��ȿ�� �˻� �����Դϴ�. �⺻ ���� true�Դϴ�.
	 */
	virtual void Initialize(const std::wstring& vsPath, const std::wstring& fsPath) override;


	/**
	 * @brief ���̴��� ���� ���ҽ��� �Ҵ� �����մϴ�.
	 */
	virtual void Release() override;


	/**
	 * @brief 2D �ؽ�Ʈ�� ȭ�鿡 �׸��ϴ�.
	 *
	 * @param ortho ���� ���� ����Դϴ�.
	 * @param font ��Ʈ ���ҽ��Դϴ�.
	 * @param text �������� �ؽ�Ʈ�Դϴ�.
	 * @param center �ؽ�Ʈ�� �߽� ��ǥ�Դϴ�.
	 * @param color �ؽ�Ʈ�� RGBA �����Դϴ�.
	 */
	void DrawText2D(const Matrix4x4f& ortho, const TTFont* font, const std::wstring& text, const Vector2f& center, const Vector4f& color);


private:
	/**
	 * @brief �ؽ�Ʈ �׸��⸦ �����ϴ� ���̴� ���ο��� ����ϴ� �����Դϴ�.
	 */
	struct VertexPositionTexture
	{
		/**
		 * @brief ��ġ�� �ؽ�ó ������ ���� ������ �⺻ �������Դϴ�.
		 */
		VertexPositionTexture() noexcept
			: position(0.0f, 0.0f, 0.0f)
			, texture(0.0f, 0.0f) {}


		/**
		 * @brief ��ġ�� �ؽ�ó ������ ���� ������ �������Դϴ�.
		 *
		 * @param position ������ ��ġ�Դϴ�.
		 * @param st ������ �ؽ�ó ��ġ�Դϴ�.
		 */
		VertexPositionTexture(Vector3f&& position, Vector2f&& st) noexcept
			: position(position)
			, texture(st) {}


		/**
		 * @brief ��ġ�� �ؽ�ó ������ ���� ������ �������Դϴ�.
		 *
		 * @param position ������ ��ġ�Դϴ�.
		 * @param st ������ �ؽ�ó ��ġ�Դϴ�.
		 */
		VertexPositionTexture(const Vector3f& position, const Vector2f& st) noexcept
			: position(position)
			, texture(st) {}


		/**
		 * @brief ��ġ�� �ؽ�ó ������ ���� ������ �������Դϴ�.
		 *
		 * @param x ��ġ�� X��ǥ�Դϴ�.
		 * @param y ��ġ�� Y��ǥ�Դϴ�.
		 * @param z ��ġ�� Z��ǥ�Դϴ�.
		 * @param s �ؽ�ó ��ġ�� S��ǥ�Դϴ�.
		 * @param t �ؽ�ó ��ġ�� T��ǥ�Դϴ�.
		 */
		VertexPositionTexture(
			float x, float y, float z,
			float s, float t
		) noexcept
			: position(x, y, z)
			, texture(s, t) {}


		/**
		 * @brief ��ġ�� �ؽ�ó ������ ���� ������ �������Դϴ�.
		 *
		 * @param instance ������ ���� �ν��Ͻ��Դϴ�.
		 */
		VertexPositionTexture(VertexPositionTexture&& instance) noexcept
			: position(instance.position)
			, texture(instance.texture) {}


		/**
		 * @brief ��ġ�� �ؽ�ó ������ ���� ������ �������Դϴ�.
		 *
		 * @param instance ������ ���� �ν��Ͻ��Դϴ�.
		 */
		VertexPositionTexture(const VertexPositionTexture& instance) noexcept
			: position(instance.position)
			, texture(instance.texture) {}


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

			position = instance.position;
			texture = instance.texture;

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

			position = instance.position;
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
			return sizeof(VertexPositionTexture);
		}


		/**
		 * @brief ������ ��ġ�Դϴ�.
		 */
		Vector3f position;


		/**
		 * @brief ������ �ؽ�ó ��ǥ�Դϴ�.
		 */
		Vector2f texture;
	};


	/**
	 * @brief �ؽ�Ʈ�� �°� ���ؽ� ���۸� ������Ʈ�մϴ�.
	 *
	 * @param font ��Ʈ ���ҽ��Դϴ�.
	 * @param text �������� �ؽ�Ʈ�Դϴ�.
	 * @param center �ؽ�Ʈ�� �߽� ��ǥ�Դϴ�.
	 *
	 * @return �ؽ�Ʈ�� �´� ���ؽ��� ���� ��ȯ�մϴ�.
	 */
	uint32_t UpdateGlyphVertexBuffer(const TTFont* font, const std::wstring& text, const Vector2f& center);


private:
	/**
	 * @brief �ִ� ���ڿ��� �����Դϴ�.
	 */
	static const int32_t MAX_STRING_LEN = 1000;


	/**
	 * @brief �۸��� ���� ����� �ִ� ũ���Դϴ�.
	 *
	 * @note
	 * - ���� �ϳ� �׸��� �� �ʿ��� ������ �� : 6��
	 * - ����, �ִ� ���ڿ��� ���̰� 1000�̶��, �ʿ��� ������ �� : 6 X 1000 = 6000��
	 * - ��, �� �۸��� ���̴��� �����ϴ� �ִ� ���ڿ��� ���̴� 1000�̴�.
	 */
	static const int32_t MAX_VERTEX_SIZE = MAX_STRING_LEN * 6;


	/**
	 * @brief ���� ����Դϴ�.
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


	/**
	 * @brief ��ũ�� ���� ���� ����� ��Ÿ���� ������ ������ ��ġ�Դϴ�.
	 */
	int32_t orthoLocation_ = -1;


	/**
	 * @brief �۸����� ������ ��Ÿ���� ������ ������ ��ġ�Դϴ�.
	 */
	int32_t glyphColorLocation_ = -1;
};