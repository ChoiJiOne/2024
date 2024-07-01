#pragma once

#include <cstdint>

#include "IResource.h"


namespace GameMaker
{
/**
 * @brief �ε��� �����Դϴ�.
 */
class IndexBuffer : public IResource
{
public:
	/**
	 * @brief ������ ���۸� �����մϴ�.
	 *
	 * @param bufferPtr �ʱ�ȭ�� ������ �������Դϴ�.
	 * @param byteSize ���� ������ ����Ʈ ũ���Դϴ�.
	 */
	explicit IndexBuffer(const void* bufferPtr, uint32_t indexCount);


	/**
	 * @brief �ε��� ���۸� �Ҵ� �����մϴ�.
	 */
	virtual ~IndexBuffer();


	/**
	 * @brief �ε��� ������ ���� �����ڿ� ���� �����ڸ� ��������� �����մϴ�.
	 */
	DISALLOW_COPY_AND_ASSIGN(IndexBuffer);


	/**
	 * @brief �ε��� ������ ���ο��� �Ҵ�� ���ҽ��� �Ҵ��� �����մϴ�.
	 */
	virtual void Release() override;


	/**
	 * @brief �ε��� ���۸� ���ε��մϴ�.
	 */
	void Bind();


	/**
	 * @brief �ε��� ������ ���ε��� �����մϴ�.
	 */
	void Unbind();


	/**
	 * @brief �ε��� ������ ũ�⸦ ����ϴ�.
	 * 
	 * @return �ε��� ������ ũ�⸦ ��ȯ�մϴ�.
	 */
	uint32_t GetIndexCount() const { return indexCount_; }


private:
	/**
	 * @brief �ε��� ���� ������Ʈ ID�Դϴ�.
	 */
	uint32_t indexBufferID_ = 0;


	/**
	 * @brief �ε��� ������ ũ���Դϴ�.
	 */
	uint32_t indexCount_ = 0;
};

}