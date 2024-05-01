#pragma once

#include <array>
#include <vector>

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
	 * @brief �������� ���� ����� �����մϴ�.
	 * 
	 * @param world ������ ���� ����Դϴ�.
	 */
	void SetWorld(const Mat4x4& world) { world_ = world; }


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
	 * @brief 3D ť�긦 �׸��ϴ�.
	 * 
	 * @param projection ���� ����Դϴ�.
	 * @param extents ť���� X/Y/Z �� ���������� ũ���Դϴ�.
	 * @param color ť���� �����Դϴ�.
	 */
	void DrawCube3D(const Vec3f& extents, const Vec4f& color);


	/**
	 * @brief XZ ����� ���ڸ� �׸��ϴ�.
	 * 
	 * @param extensions ������ XYZ ���� ũ���Դϴ�.
	 * @param stride ������ �����Դϴ�.
	 */
	void DrawGrid3D(const Vec3f& extensions, float stride);


private:
	/**
	 * @brief �⺻ ������ �׸��� Ÿ���Դϴ�.
	 */
	enum class EDrawType : int32_t
	{
		Points      = 0x0000,
		Lines       = 0x0001,
		LineStrip   = 0x0003,
		Triangles   = 0x0004,
		TriangleFan = 0x0006,
		None        = 0xFFFF,
	};


	/**
	 * @brief 3D �⺻ ���� �׸��⸦ �����մϴ�.
	 * 
	 * @param drawType �׸��� Ÿ���Դϴ�.
	 * @param vertexCount ���� ���Դϴ�.
	 */
	void DrawGeometry3D(const EDrawType& drawType, uint32_t vertexCount);


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
	VertexBuffer vertexBuffer_;
};