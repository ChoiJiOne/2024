#pragma once

#include <array>
#include <vector>

#include "Shader.h"
#include "VertexBuffer.h"

class FrameBuffer;
class ColorFrameBuffer;


/**
 * @brief ����þ� ���� �����ϴ� ���̴��Դϴ�.
 *
 * @note ������ ���� ������ �� ������ �Ǵ� ��ǥ��� ������ ��ǥ���Դϴ�.
 */
class GaussianBlurEffector : public Shader
{
public:
	/**
	 * @brief ����þ� ���� �����ϴ� ���̴��� �������Դϴ�.
	 */
	explicit GaussianBlurEffector();


	/**
	 * @brief ����þ� ���� �����ϴ� ���̴��� ���� �Ҹ����Դϴ�.
	 *
	 * @note ���̴��� ���ο��� �Ҵ�� ��Ҹ� �����ϱ� ���ؼ��� �ݵ�� Release�� ȣ���ؾ� �մϴ�.
	 */
	virtual ~GaussianBlurEffector();


	/**
	 * @brief ����þ� ���� �����ϴ� ���̴��� ���� �����ڿ� ���� �����ڸ� ��������� �����մϴ�.
	 */
	DISALLOW_COPY_AND_ASSIGN(GaussianBlurEffector);


	/**
	 * @brief ���̴��� ���� ���ҽ��� �Ҵ� �����մϴ�.
	 */
	virtual void Release() override;


	/**
	 * @brief ����þ� �� ȿ�� ������ �����մϴ�.
	 *
	 * @param scene ���� ������ ���� ������ �����Դϴ�.
	 * @param pingpong ����þ� ���� ������ ���� �÷� �����Դϴ�.
	 */
	void Execute(FrameBuffer* scene, ColorFrameBuffer* pingpong[2]);


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
	 * @brief ���̴� ������ ����� ���� �����Դϴ�.
	 */
	VertexBuffer vertexBuffer_;


	/**
	 * @brief ���� ���� ���� Ƚ���Դϴ�.
	 */
	static const uint32_t COUNT_PING_PONG = 10;
};