#pragma once

#include <array>
#include <vector>

#include "Shader.h"
#include "Vertex3D.h"
#include "VertexBuffer.h"


/**
 * @brief 3D 기본 도형을 그리는 렌더러입니다.
 */
class GeometryRenderer3D : public Shader
{
public:
	/**
	 * @brief 3D 기본 도형을 그리는 렌더러의 디폴트 생성자입니다.
	 */
	explicit GeometryRenderer3D();


	/**
	 * @brief 3D 기본 도형을 그리는 렌더러의 가상 소멸자입니다.
	 *
	 * @note 렌더러 내부에서 할당된 요소를 해제하기 위해서는 반드시 Release를 호출해야 합니다.
	 */
	virtual ~GeometryRenderer3D();


	/**
	 * @brief 3D 기본 도형을 그리는 렌더러의 복사 생성자와 대입 연산자를 명시적으로 삭제합니다.
	 */
	DISALLOW_COPY_AND_ASSIGN(GeometryRenderer3D);


	/**
	 * @brief 렌더러 내부 리소스를 할당 해제합니다.
	 */
	virtual void Release() override;


	/**
	 * @brief 렌더러의 월드 행렬을 설정합니다.
	 * 
	 * @param world 설정할 월드 행렬입니다.
	 */
	void SetWorld(const Mat4x4& world) { world_ = world; }


	/**
	 * @brief 렌더러의 뷰 행렬을 설정합니다.
	 * 
	 * @param view 설정할 뷰 행렬입니다.
	 */
	void SetView(const Mat4x4& view) { view_ = view; }


	/**
	 * @brief 렌더러의 투영 행렬을 설정합니다.
	 * 
	 * @param projection 설정할 투영 행렬입니다.
	 */
	void SetProjection(const Mat4x4& projection) { projection_ = projection; }


	/**
	 * @brief 3D 점들을 그립니다.
	 * 
	 * @param positions 화면 상의 3D 점들입니다.
	 * @param color 점들의 색상입니다.
	 * @param pointSize 점의 크기입니다. 기본 값은 1.0f입니다.
	 *
	 * @note 3D 점들의 개수는 MAX_VERTEX_SIZE(10000)의 크기를 넘을 수 없습니다.
	 */
	void DrawPoints3D(const std::vector<Vec3f>& positions, const Vec4f& color, float pointSize = 1.0f);


	/**
	 * @brief 점들을 연결한 3D 선을 그립니다.
	 * 
	 * @param positions 화면 상의 3D 점들입니다.
	 * @param color 점들의 색상입니다.
	 *
	 * @note 2D 점들의 개수는 MAX_VERTEX_SIZE(10000)의 크기를 넘을 수 없습니다.
	 */
	void DrawConnectPoints3D(const std::vector<Vec3f>& positions, const Vec4f& color);


	/**
	 * @brief 3D 선을 그립니다.
	 * 
	 * @param fromPosition 선의 시작점입니다.
	 * @param toPosition 선의 끝점입니다.
	 * @param color 선의 색상입니다.
	 */
	void DrawLine3D(const Vec3f& fromPosition, const Vec3f& toPosition, const Vec4f& color);


	/**
	 * @brief 3D 선을 그립니다.
	 * 
	 * @param fromPosition 선의 시작점입니다.
	 * @param fromColor 선의 시작점 색상입니다.
	 * @param toPosition 선의 끝점입니다.
	 * @param toColor 선의 끝점 색상입니다.
	 */
	void DrawLine3D(const Vec3f& fromPosition, const Vec4f& fromColor, const Vec3f& toPosition, const Vec4f& toColor);


	/**
	 * @brief 3D 선들을 그립니다.
	 * 
	 * @param positions 연결되지 않은 선의 점 목록입니다.
	 * @param color 선의 색상입니다.
	 */
	void DrawLines3D(const std::vector<Vec3f>& positions, const Vec4f& color);


	/**
	 * @brief 3D 큐브를 그립니다.
	 * 
	 * @param world 월드 행렬입니다.
	 * @param extents 큐브의 X/Y/Z 축 방향으로의 크기입니다.
	 * @param color 큐브의 색상입니다.
	 */
	void DrawCube3D(const Mat4x4& world, const Vec3f& extents, const Vec4f& color);


	/**
	 * @brief XZ 평면의 격자를 그립니다.
	 * 
	 * @param extensions 격자의 XYZ 순의 크기입니다.
	 * @param stride 격자의 간격입니다.
	 */
	void DrawGrid3D(const Vec3f& extensions, float stride);


private:
	/**
	 * @brief 기본 도형의 그리기 타입입니다.
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
	 * @brief 3D 기본 도형 그리기를 수행합니다.
	 * 
	 * @param drawType 그리기 타입입니다.
	 * @param vertexCount 정점 수입니다.
	 */
	void DrawGeometry3D(const EDrawType& drawType, uint32_t vertexCount);


private:
	/**
	 * @brief 도형 정점 목록의 최대 크기입니다.
	 */
	static const int32_t MAX_VERTEX_SIZE = 10000;


	/**
	 * @brief 도형의 정점 목록입니다.
	 */
	std::array<VertexPositionColor3D, MAX_VERTEX_SIZE> vertices_;


	/**
	 * @brief 렌더러의 월드 행렬입니다.
	 */
	Mat4x4 world_;


	/**
	 * @brief 렌더러의 뷰 행렬입니다.
	 */
	Mat4x4 view_;


	/**
	 * @brief 렌더러의 투영 행렬입니다.
	 */
	Mat4x4 projection_;


	/**
	 * @brief 점의 크기입니다.
	 */
	float pointSize_ = 1.0f;


	/**
	 * @brief 정점 버퍼 목록의 오브젝트입니다.
	 */
	uint32_t vertexArrayObject_ = 0;


	/**
	 * @brief 정점 버퍼입니다.
	 */
	VertexBuffer vertexBuffer_;
};