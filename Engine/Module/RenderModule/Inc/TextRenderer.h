#pragma once

#include <array>

#include "RenderModule.h"
#include "VertexBuffer.h"

class Shader;
class TTFont;


/**
 * @brief �ؽ�Ʈ�� ���� ��ġ �����Դϴ�.
 */
enum class EStartPivot
{
	LEFT_TOP     = 0x00,
	LEFT_BOTTOM  = 0x01,
	RIGHT_TOP    = 0x02,
	RIGHT_BOTTOM = 0x03,
	CENTER       = 0x04,
};


/**
 * @brief �۸����� �̿��ؼ� �ؽ�Ʈ�� �������ϴ� �������Դϴ�.
 */
class TextRenderer : public IResource
{
public:
	/**
	 * @brief �ؽ�Ʈ�� �׸��� �������� ����Ʈ �������Դϴ�.
	 */
	explicit TextRenderer();


	/**
	 * @brief �ؽ�Ʈ�� �������ϴ� �������� ���� �Ҹ����Դϴ�.
	 *
	 * @note �������� ���ο��� �Ҵ�� ��Ҹ� �����ϱ� ���ؼ��� �ݵ�� Release�� ȣ���ؾ� �մϴ�.
	 */
	virtual ~TextRenderer();


	/**
	 * @brief 2D �ؽ�Ʈ�� �������ϴ� �������� ���� �����ڿ� ���� �����ڸ� ��������� �����մϴ�.
	 */
	DISALLOW_COPY_AND_ASSIGN(TextRenderer);


	/**
	 * @brief ������ ���� ���ҽ��� �Ҵ� �����մϴ�.
	 */
	virtual void Release() override;


	/**
	 * @brief ���� ���� ����� �����մϴ�.
	 *
	 * @param ortho ������ ���� ���� ����Դϴ�.
	 */
	void SetOrtho(const Mat4x4& ortho) { ortho_ = ortho; }


	/**
	 * @brief 2D �ؽ�Ʈ�� �׸��ϴ�.
	 *
	 * @param font ��Ʈ ���ҽ��Դϴ�.
	 * @param text �������� �ؽ�Ʈ�Դϴ�.
	 * @param position �ؽ�Ʈ�� ��ǥ�Դϴ�.
	 * @param startPivot �ؽ�Ʈ ���� ��ǥ�� �����Դϴ�.
	 * @param color �ؽ�Ʈ�� RGBA �����Դϴ�.
	 */
	void DrawText2D(const TTFont* font, const std::wstring& text, const Vec2f& position, const EStartPivot& startPivot, Vec4f& color);


private:
	/**
	 * @brief �ؽ�Ʈ �������� �����ϴ� ������ ���ο����� ����ϴ� �����Դϴ�.
	 */
	struct Vertex
	{
		/**
		 * @brief ������ �⺻ �������Դϴ�.
		 */
		Vertex() noexcept
			: position(0.0f, 0.0f)
			, uv(0.0f, 0.0f)
			, color(0.0f, 0.0f, 0.0f, 0.0f) {}


		/**
		 * @brief ������ �������Դϴ�.
		 *
		 * @param p ������ ��ġ�Դϴ�.
		 * @param tex ������ �ؽ�ó ��ǥ�Դϴ�.
		 * @param c ������ �����Դϴ�
		 */
		Vertex(Vec2f&& p, Vec2f&& tex, Vec4f&& c) noexcept
			: position(p)
			, uv(tex)
			, color(c) {}


		/**
		 * @brief ������ �������Դϴ�.
		 *
		 * @param p ������ ��ġ�Դϴ�.
		 * @param tex ������ �ؽ�ó ��ǥ�Դϴ�.
		 * @param c ������ �����Դϴ�
		 */
		Vertex(const Vec2f& p, const Vec2f& tex, const Vec4f& c) noexcept
			: position(p)
			, uv(tex)
			, color(c) {}


		/**
		 * @brief ������ �������Դϴ�.
		 *
		 * @param x ��ġ�� X��ǥ�Դϴ�.
		 * @param y ��ġ�� Y��ǥ�Դϴ�.
		 * @param u �ؽ�ó ��ġ�� U��ǥ�Դϴ�.
		 * @param v �ؽ�ó ��ġ�� V��ǥ�Դϴ�.
		 * @param r ���� ������ R�Դϴ�.
		 * @param g ���� ������ G�Դϴ�.
		 * @param b ���� ������ B�Դϴ�.
		 * @param a ���� ������ A�Դϴ�.
		 */
		Vertex(
			float x, float y,
			float u, float v,
			float r, float g, float b, float a
		) noexcept
			: position(x, y)
			, uv(u, v)
			, color(r, g, b, a) {}


		/**
		 * @brief ������ ���� �������Դϴ�.
		 *
		 * @param instance ������ ���� �ν��Ͻ��Դϴ�.
		 */
		Vertex(Vertex&& instance) noexcept
			: position(instance.position)
			, uv(instance.uv)
			, color(instance.color) {}


		/**
		 * @brief ������ ���� �������Դϴ�.
		 *
		 * @param instance ������ ���� �ν��Ͻ��Դϴ�.
		 */
		Vertex(const Vertex& instance) noexcept
			: position(instance.position)
			, uv(instance.uv)
			, color(instance.color) {}


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
			uv = instance.uv;
			color = instance.color;

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
			uv = instance.uv;
			color = instance.color;

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


		/**
		 * @brief ������ �ؽ�ó ��ǥ�Դϴ�.
		 */
		Vec2f uv;


		/**
		 * @brief ������ �����Դϴ�.
		 */
		Vec4f color;
	};


	/**
	 * @brief 2D �ؽ�Ʈ�� �׸��ϴ�.
	 *
	 * @param font ��Ʈ ���ҽ��Դϴ�.
	 * @param text �������� �ؽ�Ʈ�Դϴ�.
	 * @param alignment �ؽ�Ʈ ��ǥ�� ���� �����Դϴ�.
	 * @param position �ؽ�Ʈ�� ��ǥ�Դϴ�.
	 * @param color �ؽ�Ʈ�� RGBA �����Դϴ�.
	 */
	void DrawText2D(const TTFont* font, const std::wstring& text, const Vec2f& position, const Vec4f& color);


	/**
	 * @brief �ؽ�Ʈ�� �°� ���ؽ� ���۸� ������Ʈ�մϴ�.
	 *
	 * @param font ��Ʈ ���ҽ��Դϴ�.
	 * @param text �������� �ؽ�Ʈ�Դϴ�.
	 * @param startPosition �ؽ�Ʈ ������ ���� ��� ��ǥ�Դϴ�.
	 * @param color �ؽ�Ʈ�� �����Դϴ�.
	 *
	 * @return �ؽ�Ʈ�� �´� ���ؽ��� ���� ��ȯ�մϴ�.
	 */
	uint32_t UpdateGlyphVertexBuffer(const TTFont* font, const std::wstring& text, const Vec2f& startPosition, const Vec4f& color);


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
	std::array<Vertex, MAX_VERTEX_SIZE> vertices_;

	
	/**
	 * @brief ���� ���� ����Դϴ�.
	 */
	Mat4x4 ortho_;


	/**
	 * @brief ���� ���� ����� ������Ʈ�Դϴ�.
	 */
	uint32_t vertexArrayObject_ = 0;


	/**
	 * @brief ���� �����Դϴ�.
	 */
	VertexBuffer* vertexBuffer_;


	/**
	 * @brief ������ �� ����� ���̴��Դϴ�.
	 */
	Shader* shader_ = nullptr;
};