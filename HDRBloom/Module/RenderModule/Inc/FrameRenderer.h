#pragma once

#include <array>
#include <vector>

#include "Shader.h"
#include "Vertex2D.h"
#include "VertexBuffer.h"

class ColorFrameBuffer;
class FrameBuffer;


/**
 * @brief 프레임 버퍼를 그리는 렌더러입니다.
 */
class FrameRenderer : public Shader
{
public:
	/**
	 * @brief 프레임 버퍼를 그리는 렌더러의 생성자입니다.
	 */
	explicit FrameRenderer();


	/**
	 * @brief 프레임 버퍼를 그리는 렌더러의 가상 소멸자입니다.
	 *
	 * @note 프레임 버퍼를 그리는 렌더러의 내부에서 할당된 요소를 해제하기 위해서는 반드시 Release를 호출해야 합니다.
	 */
	virtual ~FrameRenderer();


	/**
	 * @brief 프레임 버퍼를 그리는 렌더러의 복사 생성자와 대입 연산자를 명시적으로 삭제합니다.
	 */
	DISALLOW_COPY_AND_ASSIGN(FrameRenderer);


	/**
	 * @brief 프레임 버퍼를 그리는 렌더러의 내부 리소스를 할당 해제합니다.
	 */
	virtual void Release() override;


	/**
	 * @brief 색상 프레임 버퍼를 그립니다.
	 *
	 * @param framebuffer 그릴 프레임 버퍼입니다.
	 */
	void DrawColorFrameBuffer(const ColorFrameBuffer* framebuffer);


	/**
	 * @brief 프레임 버퍼를 그립니다.
	 *
	 * @param framebuffer 전송할 프레임 버퍼입니다.
	 * @param index 프레임 버퍼의 컬러 버퍼 인덱스입니다.
	 */
	void DrawFrameBuffer(const FrameBuffer* framebuffer, uint32_t index);


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
	 * @brief 렌더러 내에서 사용할 정점 버퍼입니다.
	 */
	VertexBuffer vertexBuffer_;
};