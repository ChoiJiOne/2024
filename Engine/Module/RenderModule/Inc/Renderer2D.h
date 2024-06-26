#pragma once

#include <array>

#include "RenderModule.h"
#include "VertexBuffer.h"

class Shader;


/**
 * @brief 2D �������� �����ϴ� �������Դϴ�.
 * 
 * @note ��ǥ�� ������ ������ ��ǥ�� �����Դϴ�.
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
	 * @param startPosition ���� �������Դϴ�.
	 * @param endPosition ���� �����Դϴ�.
	 * @param color ���� �����Դϴ�.
	 */
	void DrawLine(const Vec2f& startPosition, const Vec2f& endPosition, const Vec4f& color);


	/**
	 * @brief 2D ���� �׸��ϴ�.
	 * 
	 * @param startPosition ���� �������Դϴ�.
	 * @param startColor ���� ������ �����Դϴ�.
	 * @param endPosition ���� �����Դϴ�.
	 * @param endColor ���� ���� �����Դϴ�.
	 */
	void DrawLine(const Vec2f& startPosition, const Vec4f& startColor, const Vec2f& endPosition, const Vec4f& endColor);


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
	 * @param fromPosition �ﰢ�� ���� ���Դϴ�.
	 * @param byPosition �ﰢ�� �߰� ���Դϴ�.
	 * @param toPosition �ﰢ�� �� ���Դϴ�.
	 * @param color �ﰢ���� �����Դϴ�.
	 */
	void DrawTriangle(const Vec2f& fromPosition, const Vec2f& byPosition, const Vec2f& toPosition, const Vec4f& color);

	
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


private:
	/**
	 * @brief �׸��⸦ �����մϴ�.
	 * 
	 * @param transform ��ȯ ����Դϴ�.
	 * @param drawMode �׸��� ����Դϴ�.
	 * @param vertexCount ���� ���Դϴ�.
	 */
	void Draw(const Mat4x4& transform, const EDrawMode& drawMode, uint32_t vertexCount);


private:
	/**
	 * @brief ���� ���� ����� �ִ� ũ���Դϴ�.
	 */
	static const int32_t MAX_VERTEX_SIZE = 10000;


	/**
	 * @brief � ��� �� �ִ� ���� Ƚ���Դϴ�.
	 */
	static const int32_t MAX_SLICE_SIZE = 7;


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
