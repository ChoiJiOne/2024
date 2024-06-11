#pragma once

#include <array>

#include "RenderModule.h"
#include "VertexBuffer.h"

class Shader;


/**
 * @brief 2D ���� ������ �������ϴ� �������Դϴ�.
 */
class GeometryRenderer2D : public IResource
{
public:
	/**
	 * @brief 2D ���� ������ �׸��� �������� ����Ʈ �������Դϴ�.
	 */
	explicit GeometryRenderer2D();


	/**
	 * @brief 2D ���� ������ �׸��� �������� ���� �Ҹ����Դϴ�.
	 *
	 * @note ������ ���ο��� �Ҵ�� ��Ҹ� �����ϱ� ���ؼ��� �ݵ�� Release�� ȣ���ؾ� �մϴ�.
	 */
	virtual ~GeometryRenderer2D();


	/**
	 * @brief 2D ���� ������ �׸��� �������� ���� �����ڿ� ���� �����ڸ� ��������� �����մϴ�.
	 */
	DISALLOW_COPY_AND_ASSIGN(GeometryRenderer2D);


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
	 * @brief 2D ������ �׸��ϴ�.
	 *
	 * @param positions 2D �����Դϴ�.
	 * @param color ������ �����Դϴ�.
	 * @param pointSize ���� ũ���Դϴ�. �⺻ ���� 1.0f�Դϴ�.
	 *
	 * @note 2D ������ ������ MAX_VERTEX_SIZE(10000)�� ũ�⸦ ���� �� �����ϴ�.
	 */
	void DrawPoints2D(const std::vector<Vec2f>& positions, const Vec4f& color, float pointSize = 1.0f);


	/**
	 * @brief ������ ������ 2D ���� �׸��ϴ�.
	 *
	 * @param positions 2D �����Դϴ�.
	 * @param color ������ �����Դϴ�.
	 *
	 * @note 2D ������ ������ MAX_VERTEX_SIZE(10000)�� ũ�⸦ ���� �� �����ϴ�.
	 */
	void DrawConnectPoints2D(const std::vector<Vec2f>& positions, const Vec4f& color);


	/**
	 * @brief 2D ���� �׸��ϴ�.
	 *
	 * @param fromPosition ���� �������Դϴ�.
	 * @param toPosition ���� �����Դϴ�.
	 * @param color ���� �����Դϴ�.
	 */
	void DrawLine2D(const Vec2f& fromPosition, const Vec2f& toPosition, const Vec4f& color);


	/**
	 * @brief 2D ���� �׸��ϴ�.
	 *
	 * @param ortho ���� ���� ����Դϴ�.
	 * @param fromPosition ���� �������Դϴ�.
	 * @param fromColor ���� ������ �����Դϴ�.
	 * @param toPosition ���� �����Դϴ�.
	 * @param toColor ���� ���� �����Դϴ�.
	 */
	void DrawLine2D(const Vec2f& fromPosition, const Vec4f& fromColor, const Vec2f& toPosition, const Vec4f& toColor);


	/**
	 * @brief 2D ������ �׸��ϴ�.
	 *
	 * @param positions ������� ���� ���� �� ����Դϴ�.
	 * @param color ���� �����Դϴ�.
	 */
	void DrawLines2D(const std::vector<Vec2f>& positions, const Vec4f& color);


	/**
	 * @brief 2D �ﰢ���� �׸��ϴ�.
	 *
	 * @param fromPosition �ﰢ�� ���� ���Դϴ�.
	 * @param byPosition �ﰢ�� �߰� ���Դϴ�.
	 * @param toPosition �ﰢ�� �� ���Դϴ�.
	 * @param color �ﰢ���� �����Դϴ�.
	 */
	void DrawTriangle2D(const Vec2f& fromPosition, const Vec2f& byPosition, const Vec2f& toPosition, const Vec4f& color);


	/**
	 * @brief 2D �ﰢ���� �׸��ϴ�.
	 *
	 * @param fromPosition �ﰢ�� ���� ���Դϴ�.
	 * @param fromColor �ﰢ�� ���� ���� �����Դϴ�.
	 * @param byPosition �ﰢ�� �߰� ���Դϴ�.
	 * @param byColor �ﰢ�� �߰� ���� �����Դϴ�.
	 * @param toPosition �ﰢ�� �� ���Դϴ�.
	 * @param toColor �ﰢ�� �� ���� �����Դϴ�.
	 */
	void DrawTriangle2D(
		const Vec2f& fromPosition, const Vec4f& fromColor,
		const Vec2f& byPosition, const Vec4f& byColor,
		const Vec2f& toPosition, const Vec4f& toColor
	);


	/**
	 * @brief 2D ���̾� ������ �ﰢ���� �׸��ϴ�.
	 *
	 * @param fromPosition �ﰢ�� ���� ���Դϴ�.
	 * @param byPosition �ﰢ�� �߰� ���Դϴ�.
	 * @param toPosition �ﰢ�� �� ���Դϴ�.
	 * @param color �ﰢ���� �����Դϴ�.
	 */
	void DrawWireframeTriangle2D(const Vec2f& fromPosition, const Vec2f& byPosition, const Vec2f& toPosition, const Vec4f& color);


	/**
	 * @brief 2D ���̾� ������ �ﰢ���� �׸��ϴ�.
	 *
	 * @param fromPosition �ﰢ�� ���� ���Դϴ�.
	 * @param fromColor �ﰢ�� ���� ���� �����Դϴ�.
	 * @param byPosition �ﰢ�� �߰� ���Դϴ�.
	 * @param byColor �ﰢ�� �߰� ���� �����Դϴ�.
	 * @param toPosition �ﰢ�� �� ���Դϴ�.
	 * @param toColor �ﰢ�� �� ���� �����Դϴ�.
	 */
	void DrawWireframeTriangle2D(
		const Vec2f& fromPosition, const Vec4f& fromColor,
		const Vec2f& byPosition, const Vec4f& byColor,
		const Vec2f& toPosition, const Vec4f& toColor
	);


	/**
	 * @brief 2D ���簢���� �׸��ϴ�.
	 *
	 * @param center ���簢���� �߽� ��ǥ�Դϴ�.
	 * @param width ���簢���� ���� ũ���Դϴ�.
	 * @param heigt ���簢���� ���� ũ���Դϴ�.
	 * @param rotate ���簢���� ���� ȸ�� �����Դϴ�.
	 * @param color ���簢���� �����Դϴ�.
	 */
	void DrawRectangle2D(const Vec2f& center, float width, float height, float rotate, const Vec4f& color);


	/**
	 * @brief 2D ���̾� ������ ���簢���� �׸��ϴ�.
	 *
	 * @param center ���簢���� �߽� ��ǥ�Դϴ�.
	 * @param width ���簢���� ���� ũ���Դϴ�.
	 * @param heigt ���簢���� ���� ũ���Դϴ�.
	 * @param rotate ���簢���� ���� ȸ�� �����Դϴ�.
	 * @param color ���簢���� �����Դϴ�.
	 */
	void DrawWireframeRectangle2D(const Vec2f& center, float width, float height, float rotate, const Vec4f& color);


	/**
	 * @brief �𼭸��� �ձ� 2D �簢���� �׸��ϴ�.
	 *
	 * @param center ���簢���� �߽� ��ǥ�Դϴ�.
	 * @param width ���簢���� ���� ũ���Դϴ�.
	 * @param heigt ���簢���� ���� ũ���Դϴ�.
	 * @param side �簢���� �ձ� �κ��� ũ���Դϴ�.
	 * @param rotate ���簢���� ���� ȸ�� �����Դϴ�.
	 * @param color ���簢���� �����Դϴ�.
	 */
	void DrawRoundRectangle2D(const Vec2f& center, float width, float height, float side, float rotate, const Vec4f& color);


	/**
	 * @brief �𼭸��� �ձ� 2D ���̾� ������ �簢���� �׸��ϴ�.
	 *
	 * @param center ���簢���� �߽� ��ǥ�Դϴ�.
	 * @param width ���簢���� ���� ũ���Դϴ�.
	 * @param heigt ���簢���� ���� ũ���Դϴ�.
	 * @param side �簢���� �ձ� �κ��� ũ���Դϴ�.
	 * @param rotate ���簢���� ���� ȸ�� �����Դϴ�.
	 * @param color ���簢���� �����Դϴ�.
	 */
	void DrawWireframeRoundRectangle2D(const Vec2f& center, float width, float height, float side, float rotate, const Vec4f& color);


	/**
	 * @brief 2D ���� �׸��ϴ�.
	 *
	 * @param center ���� �߽� ��ǥ�Դϴ�.
	 * @param radius ���� ������ �����Դϴ�.
	 * @param color ���� �����Դϴ�.
	 * @param sliceCount ���� �ѷ� ���� Ƚ���Դϴ�. �⺻ ���� 300�Դϴ�.
	 */
	void DrawCircle2D(const Vec2f& center, float radius, const Vec4f& color, int32_t sliceCount = 300);


	/**
	 * @brief 2D ���̾� ������ ���� �׸��ϴ�.
	 *
	 * @param center ���� �߽� ��ǥ�Դϴ�.
	 * @param radius ���� ������ �����Դϴ�.
	 * @param color ���� �����Դϴ�.
	 * @param sliceCount �� �ѷ��� ���� Ƚ���Դϴ�. �⺻ ���� 300�Դϴ�.
	 */
	void DrawWireframeCircle2D(const Vec2f& center, float radius, const Vec4f& color, int32_t sliceCount = 300);


	/**
	 * @brief 2D Ÿ���� �׸��ϴ�.
	 *
	 * @param center Ÿ���� �߽� ��ǥ�Դϴ�.
	 * @param xAxis Ÿ���� x�� �����Դϴ�. ����, �� ���̰� y�� ���̺��� ũ�ٸ� ������ �ǰ�, �׷��� ������ ������ �˴ϴ�.
	 * @param yAxis Ÿ���� y�� �����Դϴ�. ����, �� ���̰� x�� ���̺��� ũ�ٸ� ������ �ǰ�, �׷��� ������ ������ �˴ϴ�.
	 * @param rotate Ÿ���� ���� ȸ�� �����Դϴ�.
	 * @param color Ÿ���� �����Դϴ�.
	 * @param sliceCount Ÿ�� �ѷ��� ���� Ƚ���Դϴ�. �⺻ ���� 300�Դϴ�.
	 */
	void DrawEllipse2D(const Vec2f& center, float xAxis, float yAxis, float rotate, const Vec4f& color, int32_t sliceCount = 300);


	/**
	 * @brief 2D ���̾� ������ Ÿ���� �׸��ϴ�.
	 *
	 * @param center Ÿ���� �߽� ��ǥ�Դϴ�.
	 * @param xAxis Ÿ���� x�� �����Դϴ�. ����, �� ���̰� y�� ���̺��� ũ�ٸ� ������ �ǰ�, �׷��� ������ ������ �˴ϴ�.
	 * @param yAxis Ÿ���� y�� �����Դϴ�. ����, �� ���̰� x�� ���̺��� ũ�ٸ� ������ �ǰ�, �׷��� ������ ������ �˴ϴ�.
	 * @param rotate Ÿ���� ���� ȸ�� �����Դϴ�.
	 * @param color Ÿ���� �����Դϴ�.
	 * @param sliceCount Ÿ�� �ѷ��� ���� Ƚ���Դϴ�. �⺻ ���� 300�Դϴ�.
	 */
	void DrawWireframeEllipse2D(const Vec2f& center, float xAxis, float yAxis, float rotate, const Vec4f& color, int32_t sliceCount = 300);


	/**
	 * @brief ȭ�鿡 ���ҵ� 2D ���带 �׸��ϴ�.
	 *
	 * @param center 2D ������ �߽� ��ǥ�Դϴ�.
	 * @param view �þ� ����Դϴ�.
	 * @param projection ���� ����Դϴ�.
	 * @param width ������ ���� ũ���Դϴ�.
	 * @param height ������ ���� ũ���Դϴ�.
	 * @param rate ������ ���� �����Դϴ�. ���� ������ 0.0f ~ 1.0f�Դϴ�.
	 * @param color ������ rate ���� �κ��� �����Դϴ�.
	 * @param bgColor ������ 1.0f - rate ���� �κ��� �����Դϴ�.
	 *
	 * @note
	 * ������������������������������������������������������
	 * ��        ��                ��
	 * ��  rate  ��  1.0f - rate   ��
	 * ��        ��                ��
	 * ������������������������������������������������������
	 */
	void DrawHorizonProgressBar2D(const Vec2f& center, float width, float height, float rate, const Vec4f& color, const Vec4f& bgColor);


	/**
	 * @brief ȭ�鿡 ���ҵ� 2D ���带 �׸��ϴ�.
	 *
	 * param center 2D ������ �߽� ��ǥ�Դϴ�.
	 * @param width ������ ���� ũ���Դϴ�.
	 * @param height ������ ���� ũ���Դϴ�.
	 * @param rate ������ ���� �����Դϴ�. ���� ������ 0.0f ~ 1.0f�Դϴ�.
	 * @param color ������ rate ���� �κ��� �����Դϴ�.
	 * @param bgColor ������ 1.0f - rate ���� �κ��� �����Դϴ�.
	 *
	 * @note
	 * ��������������������������������
	 * �� 1.0f - rate  ��
	 * ��������������������������������
	 * ��     rate     ��
	 * ��������������������������������
	 */
	void DrawVerticalProgressBar2D(const Vec2f& center, float width, float height, float rate, const Vec4f& color, const Vec4f& bgColor);


private:
	/**
	 * @brief 2D ���� ���� ������ ���ο��� ����ϴ� �����Դϴ�.
	 */
	struct Vertex
	{
		/**
		 * @brief ������ �⺻ �������Դϴ�.
		 */
		Vertex() noexcept
			: position(0.0f, 0.0f)
			, color(0.0f, 0.0f, 0.0f, 0.0f) {}


		/**
		 * @brief ������ �������Դϴ�.
		 *
		 * @param p ������ ��ġ�Դϴ�.
		 * @param c ������ �����Դϴ�.
		 */
		Vertex(Vec2f&& p, Vec4f&& c) noexcept
			: position(p)
			, color(c) {}


		/**
		 * @brief ������ �������Դϴ�.
		 *
		 * @param p ������ ��ġ�Դϴ�.
		 * @param c ������ �����Դϴ�.
		 */
		Vertex(const Vec2f& p, const Vec4f& c) noexcept
			: position(p)
			, color(c) {}


		/**
		 * @brief ������ �������Դϴ�.
		 *
		 * @param x ��ġ�� X��ǥ�Դϴ�.
		 * @param y ��ġ�� Y��ǥ�Դϴ�.
		 * @param r ���� ������ R�Դϴ�.
		 * @param g ���� ������ G�Դϴ�.
		 * @param b ���� ������ B�Դϴ�.
		 * @param a ���� ������ A�Դϴ�.
		 */
		Vertex(
			float x, float y,
			float r, float g, float b, float a
		) noexcept
			: position(x, y)
			, color(r, g, b, a) {}


		/**
		 * @brief ������ �������Դϴ�.
		 *
		 * @param instance ������ ���� �ν��Ͻ��Դϴ�.
		 */
		Vertex(Vertex&& instance) noexcept
			: position(instance.position)
			, color(instance.color) {}


		/**
		 * @brief ������ �������Դϴ�.
		 *
		 * @param instance ������ ���� �ν��Ͻ��Դϴ�.
		 */
		Vertex(const Vertex& instance) noexcept
			: position(instance.position)
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
		 * @brief ������ �����Դϴ�.
		 */
		Vec4f color;
	};


private:
	/**
	 * @brief ���� ���� �׸��⸦ �����մϴ�.
	 *
	 * @param transform ��ȯ ����Դϴ�.
	 * @param drawMode �׸��� ����Դϴ�.
	 * @param vertexCount ���� ���Դϴ�.
	 */
	void DrawGeometry2D(const Mat4x4& transform, const EDrawMode& drawMode, uint32_t vertexCount);


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
	VertexBuffer* vertexBuffer_;


	/**
	 * @brief ������ �� ����� ���̴��Դϴ�.
	 */
	Shader* shader_ = nullptr;
};