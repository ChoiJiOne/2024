#pragma once

#include <array>

#include "RenderModule.h"
#include "VertexBuffer.h"

class Shader;
class TTFont;


/**
 * @brief 2D �������� �����ϴ� �������Դϴ�.
 * 
 * @note ��ǥ�� ������ ������ �����ϴ�.
 *     +y
 *     ��
 * ������������������x+
 *     ��
 */
class Renderer2D : public IResource
{
public:
	/**
	 * @brief 2D �������� �������Դϴ�.
	 */
	explicit Renderer2D();


	/**
	 * @brief 2D �������� ���� �Ҹ����Դϴ�.
	 */
	virtual ~Renderer2D();


	/**
	 * @brief 2D �������� ���� ������ �� ���� �����ڸ� ��������� �����մϴ�.
	 */
	DISALLOW_COPY_AND_ASSIGN(Renderer2D);


	/**
	 * @brief ������ ���� ���ҽ��� �Ҵ� �����մϴ�.
	 */
	virtual void Release() override;


	/**
	 * @brief �������� ���� ���� ����� �����մϴ�.
	 *
	 * @param ortho ������ ���� ���� ����Դϴ�.
	 */
	void SetOrtho(const Mat4x4& ortho) { ortho_ = ortho; }


	/**
	 * @brief 2D ���� �׸��ϴ�.
	 *
	 * @param positions ���� �迭 �������Դϴ�.
	 * @param size ���� �����Դϴ�.
	 * @param color ���� �����Դϴ�.
	 * @param pointSize ���� ũ���Դϴ�. �⺻ ���� 1.0f �Դϴ�.
	 */
	void DrawPoint(const Vec2f* positions, uint32_t size, const Vec4f& color, float pointSize = 1.0f);


	/**
	 * @brief 2D ���� �׸��ϴ�.
	 * 
	 * @param positions ���� �迭 �������Դϴ�.
	 * @param colors ���� �迭 �������Դϴ�. �̶�, ���� ������ ���� ���ƾ� �մϴ�.
	 * @param size ���� �����Դϴ�.
	 * @param pointSize ���� ũ���Դϴ�. �⺻ ���� 1.0f �Դϴ�.
	 */
	void DrawPoint(const Vec2f* positions, const Vec4f* colors, uint32_t size, float pointSize = 1.0f);


	/**
	 * @brief 2D ������ ������ ���� �׸��ϴ�.
	 * 
	 * @param positions ���� �迭 �������Դϴ�.
	 * @param colors ���� �迭 �������Դϴ�. �̶�, ���� ������ ���� ���ƾ� �մϴ�.
	 * @param size ���� �����Դϴ�.
	 */
	void DrawLine(const Vec2f* positions, const Vec4f* colors, uint32_t size);


	/**
	 * @brief 2D ���� �׸��ϴ�.
	 *
	 * @param startPos ���� �������Դϴ�.
	 * @param endPos ���� �����Դϴ�.
	 * @param color ���� �����Դϴ�.
	 */
	void DrawLine(const Vec2f& startPos, const Vec2f& endPos, const Vec4f& color);


	/**
	 * @brief 2D ���� �׸��ϴ�.
	 * 
	 * @param startPos ���� �������Դϴ�.
	 * @param startColor ���� ������ �����Դϴ�.
	 * @param endPos ���� �����Դϴ�.
	 * @param endColor ���� ���� �����Դϴ�.
	 */
	void DrawLine(const Vec2f& startPos, const Vec4f& startColor, const Vec2f& endPos, const Vec4f& endColor);


	/**
	 * @brief 2D ������ �׸��ϴ�.
	 * 
	 * @param positions ������� ���� ���� �� ���� ����Դϴ�.
	 * @param size ������� ���� ���� �� ���� ����� ���Դϴ�.
	 * @param color ���� �����Դϴ�.
	 */
	void DrawLines(const Vec2f* positions, uint32_t size, const Vec4f& color);


	/**
	 * @brief 2D ������ �׸��ϴ�.
	 *
	 * @param positions ������� ���� ���� �� ���� ����Դϴ�.
	 * @param colors ���� �迭 �������Դϴ�. �̶�, ���� �� ���� ���� ������ ���� ���ƾ� �մϴ�.
	 * @param size ������� ���� ���� �� ���� ����� ���Դϴ�.
	 */
	void DrawLines(const Vec2f* positions, const Vec4f* colors, uint32_t size);


	/**
	 * @brief 2D �ﰢ���� �׸��ϴ�.
	 * 
	 * @param fromPos �ﰢ�� ���� ���Դϴ�.
	 * @param byPos �ﰢ�� �߰� ���Դϴ�.
	 * @param toPos �ﰢ�� �� ���Դϴ�.
	 * @param color �ﰢ���� �����Դϴ�.
	 */
	void DrawTriangle(const Vec2f& fromPos, const Vec2f& byPos, const Vec2f& toPos, const Vec4f& color);


	/**
	 * @brief 2D �ﰢ���� �׸��ϴ�.
	 * 
	 * @param fromPos �ﰢ�� ���� ���Դϴ�.
	 * @param fromColor �ﰢ�� ���� ���� �����Դϴ�.
	 * @param byPos �ﰢ�� �߰� ���Դϴ�.
	 * @param byColor �ﰢ�� �߰� ���� �����Դϴ�.
	 * @param toPos �ﰢ�� �� ���Դϴ�.
	 * @param toColor �ﰢ�� �� ���� �����Դϴ�.
	 */
	void DrawTriangle(const Vec2f& fromPos, const Vec4f& fromColor, const Vec2f& byPos, const Vec4f& byColor, const Vec2f& toPos, const Vec4f& toColor);


	/**
	 * @brief 2D ���̾� ������ �ﰢ���� �׸��ϴ�.
	 *
	 * @param fromPos �ﰢ�� ���� ���Դϴ�.
	 * @param byPos �ﰢ�� �߰� ���Դϴ�.
	 * @param toPos �ﰢ�� �� ���Դϴ�.
	 * @param color �ﰢ���� �����Դϴ�.
	 */
	void DrawTriangleWireframe(const Vec2f& fromPos, const Vec2f& byPos, const Vec2f& toPos, const Vec4f& color);


	/**
	 * @brief 2D ���̾� ������ �ﰢ���� �׸��ϴ�.
	 *
	 * @param fromPos �ﰢ�� ���� ���Դϴ�.
	 * @param fromColor �ﰢ�� ���� ���� �����Դϴ�.
	 * @param byPos �ﰢ�� �߰� ���Դϴ�.
	 * @param byColor �ﰢ�� �߰� ���� �����Դϴ�.
	 * @param toPos �ﰢ�� �� ���Դϴ�.
	 * @param toColor �ﰢ�� �� ���� �����Դϴ�.
	 */
	void DrawTriangleWireframe(const Vec2f& fromPos, const Vec4f& fromColor, const Vec2f& byPos, const Vec4f& byColor, const Vec2f& toPos, const Vec4f& toColor);


	/**
	 * @brief 2D ���簢���� �׸��ϴ�.
	 * 
	 * @param center ���簢���� �߽� ��ǥ�Դϴ�.
	 * @param w ���簢���� ���� ũ���Դϴ�.
	 * @param h ���簢���� ���� ũ���Դϴ�.
	 * @param color ���簢���� �����Դϴ�.
	 * @param rotate ���簢���� ȸ�� �����Դϴ�. �⺻ ���� 0.0�Դϴ�.
	 */
	void DrawRect(const Vec2f& center, float w, float h, const Vec4f& color, float rotate = 0.0f);


	/**
	 * @brief 2D ���̾������� ���簢���� �׸��ϴ�.
	 * 
	 * @param center ���簢���� �߽� ��ǥ�Դϴ�.
	 * @param w ���簢���� ���� ũ���Դϴ�.
	 * @param h ���簢���� ���� ũ���Դϴ�.
	 * @param color ���簢���� �����Դϴ�.
	 * @param rotate ���簢���� ȸ�� �����Դϴ�. �⺻ ���� 0.0�Դϴ�.
	 */
	void DrawRectWireframe(const Vec2f& center, float w, float h, const Vec4f& color, float rotate = 0.0f);


	/**
	 * @brief 2D �𼭸��� �ձ� ���簢���� �׸��ϴ�.
	 * 
	 * @param center ���簢���� �߽� ��ǥ�Դϴ�.
	 * @param w ���簢���� ���� ũ���Դϴ�.
	 * @param h ���簢���� ���� ũ���Դϴ�.
	 * @param side �簢���� �ձ� �κ��� ũ���Դϴ�.
	 * @param color ���簢���� �����Դϴ�.
	 * @param rotate ���簢���� ���� ȸ�� �����Դϴ�. �⺻ ���� 0.0�Դϴ�.
	 */
	void DrawRoundRect(const Vec2f& center, float w, float h, float side, const Vec4f& color, float rotate = 0.0f);


	/**
	 * @brief 2D �𼭸��� �ձ� ���̾� ������ ���簢���� �׸��ϴ�.
	 *
	 * @param center ���簢���� �߽� ��ǥ�Դϴ�.
	 * @param w ���簢���� ���� ũ���Դϴ�.
	 * @param h ���簢���� ���� ũ���Դϴ�.
	 * @param side �簢���� �ձ� �κ��� ũ���Դϴ�.
	 * @param color ���簢���� �����Դϴ�.
	 * @param rotate ���簢���� ���� ȸ�� �����Դϴ�. �⺻ ���� 0.0�Դϴ�.
	 */
	void DrawRoundRectWireframe(const Vec2f& center, float w, float h, float side, const Vec4f& color, float rotate = 0.0f);


	/**
	 * @brief 2D ���� �׸��ϴ�.
	 * 
	 * @param center ���� �߽� ��ǥ�Դϴ�.
	 * @param radius ���� ������ �����Դϴ�.
	 * @param color ���� �����Դϴ�.
	 * @param sliceCount ���� �ѷ� ���� Ƚ���Դϴ�. �⺻ ���� 300�Դϴ�.
	 */
	void DrawCircle(const Vec2f& center, float radius, const Vec4f& color, int32_t sliceCount = 300);


	/**
	 * @brief 2D ���̾� ������ ���� �׸��ϴ�.
	 *
	 * @param center ���� �߽� ��ǥ�Դϴ�.
	 * @param radius ���� ������ �����Դϴ�.
	 * @param color ���� �����Դϴ�.
	 * @param sliceCount ���� �ѷ� ���� Ƚ���Դϴ�. �⺻ ���� 300�Դϴ�.
	 */
	void DrawCircleWireframe(const Vec2f& center, float radius, const Vec4f& color, int32_t sliceCount = 300);


	/**
	 * @brief 2D Ÿ���� �׸��ϴ�.
	 *
	 * @param center Ÿ���� �߽� ��ǥ�Դϴ�.
	 * @param xAxis Ÿ���� x�� �����Դϴ�. ����, �� ���̰� y�� ���̺��� ũ�ٸ� ������ �ǰ�, �׷��� ������ ������ �˴ϴ�.
	 * @param yAxis Ÿ���� y�� �����Դϴ�. ����, �� ���̰� x�� ���̺��� ũ�ٸ� ������ �ǰ�, �׷��� ������ ������ �˴ϴ�.
	 * @param color Ÿ���� �����Դϴ�.
	 * @param rotate Ÿ���� ���� ȸ�� �����Դϴ�. �⺻ ���� 0.0�Դϴ�.
	 * @param sliceCount Ÿ�� �ѷ��� ���� Ƚ���Դϴ�. �⺻ ���� 300�Դϴ�.
	 */
	void DrawEllipse(const Vec2f& center, float xAxis, float yAxis, const Vec4f& color, float rotate = 0.0f, int32_t sliceCount = 300);


	/**
	 * @brief 2D ���̾� ������ Ÿ���� �׸��ϴ�.
	 *
	 * @param center Ÿ���� �߽� ��ǥ�Դϴ�.
	 * @param xAxis Ÿ���� x�� �����Դϴ�. ����, �� ���̰� y�� ���̺��� ũ�ٸ� ������ �ǰ�, �׷��� ������ ������ �˴ϴ�.
	 * @param yAxis Ÿ���� y�� �����Դϴ�. ����, �� ���̰� x�� ���̺��� ũ�ٸ� ������ �ǰ�, �׷��� ������ ������ �˴ϴ�.
	 * @param color Ÿ���� �����Դϴ�.
	 * @param rotate Ÿ���� ���� ȸ�� �����Դϴ�. �⺻ ���� 0.0�Դϴ�.
	 * @param sliceCount Ÿ�� �ѷ��� ���� Ƚ���Դϴ�. �⺻ ���� 300�Դϴ�.
	 */
	void DrawEllipseWireframe(const Vec2f& center, float xAxis, float yAxis, const Vec4f& color, float rotate = 0.0f, int32_t sliceCount = 300);


	/**
	 * @brief 2D ���ڿ��� �׸��ϴ�.
	 * 
	 * @param font ��Ʈ ���ҽ��Դϴ�.
	 * @param text �������� �ؽ�Ʈ�Դϴ�.
	 * @param pos �������� �ؽ�Ʈ�� ���� ��� ��ǥ�Դϴ�.
	 * @param color �ؽ�Ʈ�� RGBA �����Դϴ�.
	 */
	void DrawString(const TTFont* font, const std::wstring& text, const Vec2f& pos, const Vec4f& color);


private:
	/**
	 * @brief 2D ������ ���ο��� ����ϴ� �����Դϴ�.
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
		 * @param t ������ �ؽ�ó ��ǥ�Դϴ�.
		 * @param c ������ �����Դϴ�.
		 */
		Vertex(Vec2f&& p, Vec2f& t, Vec4f&& c) noexcept
			: position(p)
			, uv(t)
			, color(c) {}


		/**
		 * @brief ������ �������Դϴ�.
		 *
		 * @param p ������ ��ġ�Դϴ�.
		 * @param t ������ �ؽ�ó ��ǥ�Դϴ�.
		 * @param c ������ �����Դϴ�.
		 */
		Vertex(const Vec2f& p, const Vec2f& t, const Vec4f& c) noexcept
			: position(p)
			, uv(t)
			, color(c) {}


		/**
		 * @brief ������ �������Դϴ�.
		 *
		 * @param x ���� ��ġ�� X��ǥ�Դϴ�.
		 * @param y ���� ��ġ�� Y��ǥ�Դϴ�.
		 * @param u ���� �ؽ�ó�� U��ǥ�Դϴ�.
		 * @param v ���� �ؽ�ó�� V��ǥ�Դϴ�.
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
		 * @brief ������ �������Դϴ�.
		 *
		 * @param instance ������ ���� �ν��Ͻ��Դϴ�.
		 */
		Vertex(Vertex&& instance) noexcept
			: position(instance.position)
			, uv(instance.uv)
			, color(instance.color) {}


		/**
		 * @brief ������ �������Դϴ�.
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
	 * @brief �׸��� ����� �����Դϴ�.
	 */
	enum class EMode
	{
		GEOMETRY = 0x00,
		STRING   = 0x01,
	};


private:
	/**
	 * @brief �������� �ؽ�Ʈ�� �°� ���ؽ� ���۸� �����մϴ�.
	 * 
	 * @param font ��Ʈ ���ҽ��Դϴ�.
	 * @param text �������� �ؽ�Ʈ�Դϴ�.
	 * @param pos �ؽ�Ʈ ������ ���� ��� ��ǥ�Դϴ�.
	 * @param color �ؽ�Ʈ�� �����Դϴ�.
	 *
	 * @return �ؽ�Ʈ�� �´� ���ؽ��� ���� ��ȯ�մϴ�.
	 */
	uint32_t SetGlyphVertexBuffer(const TTFont* font, const std::wstring& text, const Vec2f& pos, const Vec4f& color);


	/**
	 * @brief �׸��⸦ �����մϴ�.
	 * 
	 * @param transform ��ȯ ����Դϴ�.
	 * @param drawMode �׸��� ����Դϴ�.
	 * @param vertexCount ���� ���Դϴ�.
	 * @param mode ���� �׸��� ����Դϴ�.
	 */
	void Draw(const Mat4x4& transform, const EDrawMode& drawMode, uint32_t vertexCount, const EMode& mode);


private:
	/**
	 * @brief ���� ���� ����� �ִ� ũ���Դϴ�.
	 */
	static const int32_t MAX_VERTEX_SIZE = 10000;


	/**
	 * @brief ������ � ��� �� �ִ� ���� Ƚ���Դϴ�.
	 */
	static const int32_t MAX_SLICE_SIZE = 20;


	/**
	 * @brief ������ ���� ����Դϴ�.
	 */
	std::array<Vertex, MAX_VERTEX_SIZE> vertices_;


	/**
	 * @brief �������� ���� ���� ����Դϴ�.
	 */
	Mat4x4 ortho_;


	/**
	 * @brief ���� ũ���Դϴ�.
	 */
	float pointSize_ = 1.0f;


	/**
	 * @brief ���� ���� ����� ������Ʈ�Դϴ�.
	 */
	uint32_t vertexArrayObject_ = 0;


	/**
	 * @brief ���� �����Դϴ�.
	 */
	VertexBuffer* vertexBuffer_ = nullptr;


	/**
	 * @brief ������ �� ����� ���̴��Դϴ�.
	 */
	Shader* shader_ = nullptr;
};
