#pragma once

#include <array>
#include <vector>

#include "Shader.h"
#include "VertexBuffer.h"

class FrameBuffer;
class ColorFrameBuffer;


/**
 * @brief 가우시안 블러를 수행하는 셰이더입니다.
 *
 * @note 프레임 버퍼 렌더링 시 기준이 되는 좌표계는 윈도우 좌표계입니다.
 */
class GaussianBlurEffector : public Shader
{
public:
	/**
	 * @brief 가우시안 블러를 수행하는 셰이더의 생성자입니다.
	 */
	explicit GaussianBlurEffector();


	/**
	 * @brief 가우시안 블러를 수행하는 셰이더의 가상 소멸자입니다.
	 *
	 * @note 셰이더의 내부에서 할당된 요소를 해제하기 위해서는 반드시 Release를 호출해야 합니다.
	 */
	virtual ~GaussianBlurEffector();


	/**
	 * @brief 가우시안 블러를 수행하는 셰이더의 복사 생성자와 대입 연산자를 명시적으로 삭제합니다.
	 */
	DISALLOW_COPY_AND_ASSIGN(GaussianBlurEffector);


	/**
	 * @brief 셰이더의 내부 리소스를 할당 해제합니다.
	 */
	virtual void Release() override;


	/**
	 * @brief 가우시안 블러 효과 적용을 수행합니다.
	 *
	 * @param scene 블러를 수행할 씬의 프레임 버퍼입니다.
	 * @param pingpong 가우시언 블러를 수행할 핑퐁 컬러 버퍼입니다.
	 */
	void Execute(FrameBuffer* scene, ColorFrameBuffer* pingpong[2]);


private:
	/**
	 * @brief 정점 목록의 최대 크기입니다.
	 */
	static const int32_t MAX_VERTEX_SIZE = 6;


	/**
	 * @brief 정점 버퍼 목록의 오브젝트입니다.
	 */
	uint32_t vertexArrayObject_ = 0;


	/**
	 * @brief 셰이더 내에서 사용할 정점 버퍼입니다.
	 */
	VertexBuffer vertexBuffer_;


	/**
	 * @brief 블러를 위한 핑퐁 횟수입니다.
	 */
	static const uint32_t COUNT_PING_PONG = 10;
};