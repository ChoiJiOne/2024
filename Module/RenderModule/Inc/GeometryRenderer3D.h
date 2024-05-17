#pragma once

#include <array>
#include <vector>

#include "RenderModule.h"
#include "Shader.h"
#include "Vertex3D.h"
#include "VertexBuffer.h"


/**
 * @brief 3D �⺻ ������ �׸��� �������Դϴ�.
 */
class GeometryRenderer3D : public Shader
{
public:
	/**
	 * @brief 3D �⺻ ������ �׸��� �������� ����Ʈ �������Դϴ�.
	 */
	explicit GeometryRenderer3D();


	/**
	 * @brief 3D �⺻ ������ �׸��� �������� ���� �Ҹ����Դϴ�.
	 *
	 * @note ������ ���ο��� �Ҵ�� ��Ҹ� �����ϱ� ���ؼ��� �ݵ�� Release�� ȣ���ؾ� �մϴ�.
	 */
	virtual ~GeometryRenderer3D();


	/**
	 * @brief 3D �⺻ ������ �׸��� �������� ���� �����ڿ� ���� �����ڸ� ��������� �����մϴ�.
	 */
	DISALLOW_COPY_AND_ASSIGN(GeometryRenderer3D);


	/**
	 * @brief ������ ���� ���ҽ��� �Ҵ� �����մϴ�.
	 */
	virtual void Release() override;


	/**
	 * @brief �������� �� ����� �����մϴ�.
	 *
	 * @param view ������ �� ����Դϴ�.
	 */
	void SetView(const Mat4x4& view) { view_ = view; }


	/**
	 * @brief �������� ���� ����� �����մϴ�.
	 *
	 * @param projection ������ ���� ����Դϴ�.
	 */
	void SetProjection(const Mat4x4& projection) { projection_ = projection; }


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
	 * @brief 3D �⺻ ���� �׸��⸦ �����մϴ�.
	 *
	 * @param drawMode �׸��� Ÿ���Դϴ�.
	 * @param vertexCount ���� ���Դϴ�.
	 */
	void DrawGeometry3D(const EDrawMode& drawMode, uint32_t vertexCount);


private:
	/**
	 * @brief ���� ���� ����� �ִ� ũ���Դϴ�.
	 */
	static const int32_t MAX_VERTEX_SIZE = 10000;


	/**
	 * @brief ������ ���� ����Դϴ�.
	 */
	std::array<VertexPositionColor3D, MAX_VERTEX_SIZE> vertices_;


	/**
	 * @brief �������� ���� ����Դϴ�.
	 */
	Mat4x4 world_;


	/**
	 * @brief �������� �� ����Դϴ�.
	 */
	Mat4x4 view_;


	/**
	 * @brief �������� ���� ����Դϴ�.
	 */
	Mat4x4 projection_;


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
};