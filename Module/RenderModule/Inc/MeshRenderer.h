#pragma once

#include <array>
#include <vector>

#include "ITexture2D.h"
#include "Shader.h"
#include "Vertex3D.h"
#include "StaticMesh.h"


/**
 * @brief 메시를 렌더링하는 렌더러입니다.
 */
class MeshRenderer : public Shader
{
public:
	/**
	 * @brief 메시를 렌더링하는 렌더러의 디폴트 생성자입니다.
	 */
	explicit MeshRenderer();


	/**
	 * @brief 메시를 렌더링하는 렌더러의 가상 소멸자입니다.
	 *
	 * @note 렌더러 내부에서 할당된 요소를 해제하기 위해서는 반드시 Release를 호출해야 합니다.
	 */
	virtual ~MeshRenderer();


	/**
	 * @brief 메시를 렌더링하는 렌더러의 복사 생성자와 대입 연산자를 명시적으로 삭제합니다.
	 */
	DISALLOW_COPY_AND_ASSIGN(MeshRenderer);


	/**
	 * @brief 렌더러 내부 리소스를 할당 해제합니다.
	 */
	virtual void Release() override;


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
	 * @brief 3D 메시를 그립니다.
	 *
	 * @param mesh 그리기를 수행할 3D 메시입니다.
	 * @param world 월드 행렬입니다.
	 * @param material 메시에 매핑될 재질 텍스처입니다.
	 */
	void DrawMesh(StaticMesh<VertexPositionNormalUv3D>* mesh, const Mat4x4& world, ITexture2D* material);


private:
	/**
	 * @brief 렌더러의 뷰 행렬입니다.
	 */
	Mat4x4 view_;


	/**
	 * @brief 렌더러의 투영 행렬입니다.
	 */
	Mat4x4 projection_;
};