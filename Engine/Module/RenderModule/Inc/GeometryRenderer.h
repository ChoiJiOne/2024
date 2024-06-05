#pragma once

#include <array>

#include "RenderModule.h"
#include "VertexBuffer.h"

class Shader;


/**
 * @brief ���� ������ �������ϴ� �������Դϴ�.
 */
class GeometryRenderer : public IResource
{
public:
	/**
	 * @brief ���� ������ �׸��� �������� ����Ʈ �������Դϴ�.
	 */
	explicit GeometryRenderer();


	/**
	 * @brief ���� ������ �׸��� �������� ���� �Ҹ����Դϴ�.
	 *
	 * @note ������ ���ο��� �Ҵ�� ��Ҹ� �����ϱ� ���ؼ��� �ݵ�� Release�� ȣ���ؾ� �մϴ�.
	 */
	virtual ~GeometryRenderer();


	/**
	 * @brief 3D ���� ������ �׸��� �������� ���� �����ڿ� ���� �����ڸ� ��������� �����մϴ�.
	 */
	DISALLOW_COPY_AND_ASSIGN(GeometryRenderer);


	/**
	 * @brief ������ ���� ���ҽ��� �Ҵ� �����մϴ�.
	 */
	virtual void Release() override;


	/**
	 * @brief �������� �Ķ���͸� �����մϴ�.
	 *
	 * @param view ������ �� ����Դϴ�.
	 */
	void SetView(const Mat4x4& view) { view_ = view; }


	/**
	 * @brief �������� ���� ���� ����� �����մϴ�.
	 *
	 * @param projection ������ ���� ����Դϴ�.
	 */
	void SetProjection(const Mat4x4& projection) { projection_ = projection; }


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


	/**
	 * @brief 3D ������ �׸��ϴ�.
	 *
	 * @param positions ȭ�� ���� 3D �����Դϴ�.
	 * @param color ������ �����Դϴ�.
	 * @param pointSize ���� ũ���Դϴ�. �⺻ ���� 1.0f�Դϴ�.
	 *
	 * @note 3D ������ ������ MAX_VERTEX_SIZE(10000)�� ũ�⸦ ���� �� �����ϴ�.
	 */
	void DrawPoints3D(const std::vector<Vec3f>& positions, const Vec4f& color, float pointSize = 1.0f);


	/**
	 * @brief ������ ������ 3D ���� �׸��ϴ�.
	 *
	 * @param positions ȭ�� ���� 3D �����Դϴ�.
	 * @param color ������ �����Դϴ�.
	 *
	 * @note 2D ������ ������ MAX_VERTEX_SIZE(10000)�� ũ�⸦ ���� �� �����ϴ�.
	 */
	void DrawConnectPoints3D(const std::vector<Vec3f>& positions, const Vec4f& color);


	/**
	 * @brief 3D ���� �׸��ϴ�.
	 *
	 * @param fromPosition ���� �������Դϴ�.
	 * @param toPosition ���� �����Դϴ�.
	 * @param color ���� �����Դϴ�.
	 */
	void DrawLine3D(const Vec3f& fromPosition, const Vec3f& toPosition, const Vec4f& color);


	/**
	 * @brief 3D ���� �׸��ϴ�.
	 *
	 * @param fromPosition ���� �������Դϴ�.
	 * @param fromColor ���� ������ �����Դϴ�.
	 * @param toPosition ���� �����Դϴ�.
	 * @param toColor ���� ���� �����Դϴ�.
	 */
	void DrawLine3D(const Vec3f& fromPosition, const Vec4f& fromColor, const Vec3f& toPosition, const Vec4f& toColor);


	/**
	 * @brief 3D ������ �׸��ϴ�.
	 *
	 * @param positions ������� ���� ���� �� ����Դϴ�.
	 * @param color ���� �����Դϴ�.
	 */
	void DrawLines3D(const std::vector<Vec3f>& positions, const Vec4f& color);


	/**
	 * @brief 3D ���带 �׸��ϴ�.
	 *
	 * @param world ���� ����Դϴ�.
	 * @param width ������ ���� ũ���Դϴ�.
	 * @param height ������ ���� ũ���Դϴ�.
	 * @param color ������ �����Դϴ�.
	 *
	 * @note 3D ����� XY��� �����Դϴ�.
	 */
	void DrawQuad3D(const Mat4x4& world, float width, float height, const Vec4f& color);


	/**
	 * @brief ȭ�鿡 ���ҵ� 3D ���带 �׸��ϴ�.
	 *
	 * @param world ���� ����Դϴ�.
	 * @param view �þ� ����Դϴ�.
	 * @param projection ���� ����Դϴ�.
	 * @param width ������ ���� ũ���Դϴ�.
	 * @param height ������ ���� ũ���Դϴ�.
	 * @param rate ������ ���� �����Դϴ�. ���� ������ 0.0f ~ 1.0f�Դϴ�.
	 * @param color ������ rate ���� �κ��� �����Դϴ�.
	 * @param bgColor ������ 1.0f - rate ���� �κ��� �����Դϴ�.
	 *
	 * @note
	 * - 3D ����� XY ��� �����Դϴ�.
	 * - ���� �����Դϴ�.
	 * ������������������������������������������������������
	 * ��        ��                ��
	 * ��  rate  ��  1.0f - rate   ��
	 * ��        ��                ��
	 * ������������������������������������������������������
	 */
	void DrawHorizonProgressBar3D(const Mat4x4& world, float width, float height, float rate, const Vec4f& color, const Vec4f& bgColor);


	/**
	 * @brief ȭ�鿡 ���ҵ� 3D ���带 �׸��ϴ�.
	 *
	 * @param world ���� ����Դϴ�.
	 * @param width ������ ���� ũ���Դϴ�.
	 * @param height ������ ���� ũ���Դϴ�.
	 * @param rate ������ ���� �����Դϴ�. ���� ������ 0.0f ~ 1.0f�Դϴ�.
	 * @param color ������ rate ���� �κ��� �����Դϴ�.
	 * @param bgColor ������ 1.0f - rate ���� �κ��� �����Դϴ�.
	 *
	 * @note
	 * - 3D ����� XY ��� �����Դϴ�.
	 * - ���� �����Դϴ�.
	 * ��������������������������������
	 * �� 1.0f - rate  ��
	 * ��������������������������������
	 * ��     rate     ��
	 * ��������������������������������
	 */
	void DrawVerticalProgressBar3D(const Mat4x4& world, float width, float height, float rate, const Vec4f& color, const Vec4f& bgColor);


	/**
	 * @brief 3D ť�긦 �׸��ϴ�.
	 *
	 * @param world ���� ����Դϴ�.
	 * @param extents ť���� X/Y/Z �� ���������� ũ���Դϴ�.
	 * @param color ť���� �����Դϴ�.
	 */
	void DrawCube3D(const Mat4x4& world, const Vec3f& extents, const Vec4f& color);


	/**
	 * @brief 3D ���� �׸��ϴ�.
	 *
	 * @param world ���� ����Դϴ�.
	 * @param radius ���� ������ �����Դϴ�.
	 * @param color ���� �����Դϴ�.
	 */
	void DrawSphere3D(const Mat4x4& world, float radius, const Vec4f& color);


	/**
	 * @brief ���ڸ� �׸��ϴ�.
	 *
	 * @param extensions ������ XYZ ���� ũ���Դϴ�.
	 * @param stride ������ �����Դϴ�.
	 */
	void DrawGrid3D(const Vec3f& extensions, float stride);


private:
	/**
	 * @brief 3D ��ġ�� ���� ������ ���� �����Դϴ�.
	 */
	struct VertexPositionColor3D
	{
		/**
		 * @brief 3D ��ġ�� ���� ������ ���� ������ �⺻ �������Դϴ�.
		 */
		VertexPositionColor3D() noexcept
			: position(0.0f, 0.0f, 0.0f)
			, color(0.0f, 0.0f, 0.0f, 0.0f) {}


		/**
		 * @brief 3D ��ġ�� ���� ������ ���� ������ �������Դϴ�.
		 *
		 * @param p ������ ��ġ�Դϴ�.
		 * @param c ������ �����Դϴ�.
		 */
		VertexPositionColor3D(Vec3f&& p, Vec4f&& c) noexcept
			: position(p)
			, color(c) {}


		/**
		 * @brief 3D ��ġ�� ���� ������ ���� ������ �������Դϴ�.
		 *
		 * @param p ������ ��ġ�Դϴ�.
		 * @param c ������ �����Դϴ�.
		 */
		VertexPositionColor3D(const Vec3f& p, const Vec4f& c) noexcept
			: position(p)
			, color(c) {}


		/**
		 * @brief 3D ��ġ�� ���� ������ ���� ������ �������Դϴ�.
		 *
		 * @param x ��ġ�� X��ǥ�Դϴ�.
		 * @param y ��ġ�� Y��ǥ�Դϴ�.
		 * @param z ��ġ�� Z��ǥ�Դϴ�.
		 * @param r ���� ������ R�Դϴ�.
		 * @param g ���� ������ G�Դϴ�.
		 * @param b ���� ������ B�Դϴ�.
		 * @param a ���� ������ A�Դϴ�.
		 */
		VertexPositionColor3D(
			float x, float y, float z,
			float r, float g, float b, float a
		) noexcept
			: position(x, y, z)
			, color(r, g, b, a) {}


		/**
		 * @brief 3D ��ġ�� ���� ������ ���� ������ �������Դϴ�.
		 *
		 * @param instance ������ ���� �ν��Ͻ��Դϴ�.
		 */
		VertexPositionColor3D(VertexPositionColor3D&& instance) noexcept
			: position(instance.position)
			, color(instance.color) {}


		/**
		 * @brief 3D ��ġ�� ���� ������ ���� ������ �������Դϴ�.
		 *
		 * @param instance ������ ���� �ν��Ͻ��Դϴ�.
		 */
		VertexPositionColor3D(const VertexPositionColor3D& instance) noexcept
			: position(instance.position)
			, color(instance.color) {}


		/**
		 * @brief 3D ��ġ�� ���� ������ ���� ������ ���� �������Դϴ�.
		 *
		 * @param instance ������ ���� �ν��Ͻ��Դϴ�.
		 *
		 * @return ������ ��ü�� �����ڸ� ��ȯ�մϴ�.
		 */
		VertexPositionColor3D& operator=(VertexPositionColor3D&& instance) noexcept
		{
			if (this == &instance) return *this;

			position = instance.position;
			color = instance.color;

			return *this;
		}


		/**
		 * @brief 3D ��ġ�� ���� ������ ���� ������ ���� �������Դϴ�.
		 *
		 * @param instance ������ ���� �ν��Ͻ��Դϴ�.
		 *
		 * @return ������ ��ü�� �����ڸ� ��ȯ�մϴ�.
		 */
		VertexPositionColor3D& operator=(const VertexPositionColor3D& instance) noexcept
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
			return sizeof(VertexPositionColor3D);
		}


		/**
		 * @brief ������ ��ġ�Դϴ�.
		 */
		Vec3f position;


		/**
		 * @brief ������ �����Դϴ�.
		 */
		Vec4f color;
	};


private:
	/**
	 * @brief ���� ���� �׸��⸦ �����մϴ�.
	 *
	 * @parma world ���� ����Դϴ�.
	 * @param view �þ� ����Դϴ�.
	 * @param projection ���� ����Դϴ�.
	 * @param drawMode �׸��� Ÿ���Դϴ�.
	 * @param vertexCount ���� ���Դϴ�.
	 * @param bEnableDepth ���� �׽�Ʈ Ȱ��ȭ �����Դϴ�.
	 */
	void DrawGeometry(const Mat4x4& world, const Mat4x4& view, const Mat4x4& projection, const EDrawMode& drawMode, uint32_t vertexCount, bool bEnableDepth);


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
	std::array<VertexPositionColor3D, MAX_VERTEX_SIZE> vertices_;


	/**
	 * @brief �������� �� ����Դϴ�.
	 */
	Mat4x4 view_;


	/**
	 * @brief �������� ���� ���� ����Դϴ�.
	 */
	Mat4x4 projection_;


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