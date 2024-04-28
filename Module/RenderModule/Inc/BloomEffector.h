#pragma once

#include <array>
#include <vector>

#include "Shader.h"
#include "VertexBuffer.h"

class FrameBuffer;
class ColorFrameBuffer;


/**
 * @brief ��� ȿ���� �������ϴ� ���̴��Դϴ�.
 *
 * @note ������ ���� ������ �� ������ �Ǵ� ��ǥ��� ������ ��ǥ���Դϴ�.
 */
class BloomEffector : public Shader
{
public:
	/**
	 * @brief ��� ȿ���� �������ϴ� ���̴��� �������Դϴ�.
	 */
	explicit BloomEffector();


	/**
	 * @brief ��� ȿ���� �������ϴ� ���̴��� ���� �Ҹ����Դϴ�.
	 *
	 * @note ���̴��� ���ο��� �Ҵ�� ��Ҹ� �����ϱ� ���ؼ��� �ݵ�� Release�� ȣ���ؾ� �մϴ�.
	 */
	virtual ~BloomEffector();


	/**
	 * @brief ��� ȿ���� �������ϴ� ���̴��� ���� �����ڿ� ���� �����ڸ� ��������� �����մϴ�.
	 */
	DISALLOW_COPY_AND_ASSIGN(BloomEffector);


	/**
	 * @brief ���̴��� ���� ���ҽ��� �Ҵ� �����մϴ�.
	 */
	virtual void Release() override;


	/**
	 * @brief ���� ��� ȿ���� �����մϴ�.
	 *
	 * @param scene ���� ������ ���� ������ �����Դϴ�.
	 * @param blur ����þ� ���� ������ ���� �÷� �����Դϴ�.
	 */
	void Execute(FrameBuffer* scene, ColorFrameBuffer* blur);


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
};