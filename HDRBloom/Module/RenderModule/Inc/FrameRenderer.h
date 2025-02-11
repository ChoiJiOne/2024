#pragma once

#include <array>
#include <vector>

#include "Shader.h"
#include "Vertex2D.h"
#include "VertexBuffer.h"

class ColorFrameBuffer;
class FrameBuffer;


/**
 * @brief ������ ���۸� �׸��� �������Դϴ�.
 */
class FrameRenderer : public Shader
{
public:
	/**
	 * @brief ������ ���۸� �׸��� �������� �������Դϴ�.
	 */
	explicit FrameRenderer();


	/**
	 * @brief ������ ���۸� �׸��� �������� ���� �Ҹ����Դϴ�.
	 *
	 * @note ������ ���۸� �׸��� �������� ���ο��� �Ҵ�� ��Ҹ� �����ϱ� ���ؼ��� �ݵ�� Release�� ȣ���ؾ� �մϴ�.
	 */
	virtual ~FrameRenderer();


	/**
	 * @brief ������ ���۸� �׸��� �������� ���� �����ڿ� ���� �����ڸ� ��������� �����մϴ�.
	 */
	DISALLOW_COPY_AND_ASSIGN(FrameRenderer);


	/**
	 * @brief ������ ���۸� �׸��� �������� ���� ���ҽ��� �Ҵ� �����մϴ�.
	 */
	virtual void Release() override;


	/**
	 * @brief ���� ������ ���۸� �׸��ϴ�.
	 *
	 * @param framebuffer �׸� ������ �����Դϴ�.
	 */
	void DrawColorFrameBuffer(const ColorFrameBuffer* framebuffer);


	/**
	 * @brief ������ ���۸� �׸��ϴ�.
	 *
	 * @param framebuffer ������ ������ �����Դϴ�.
	 * @param index ������ ������ �÷� ���� �ε����Դϴ�.
	 */
	void DrawFrameBuffer(const FrameBuffer* framebuffer, uint32_t index);


private:
	/**
	 * @brief ���� ����� �ִ� ũ���Դϴ�.
	 */
	static const int32_t MAX_VERTEX_SIZE = 6;


	/**
	 * @brief ���� ���� ����� ������Ʈ�Դϴ�.
	 */
	uint32_t vertexArrayObject_ = 0;


	/**
	 * @brief ������ ������ ����� ���� �����Դϴ�.
	 */
	VertexBuffer vertexBuffer_;
};