#pragma once

#include "IResource.h"


/**
 * @brief ���� �����Դϴ�.
 */
class VertexBuffer : public IResource
{
public:
	/**
	 * @brief ���� ������ ��� �����Դϴ�.
	 *
	 * @see https://registry.khronos.org/OpenGL-Refpages/gl2.1/xhtml/glBufferData.xml
	 */
	enum class EUsage
	{
		Stream = 0x88E0,
		Static = 0x88E4,
		Dynamic = 0x88E8,
	};


public:
	/**
	 * @brief ���̴����� ��� ������ ���� ���۸� �����մϴ�.
	 *
	 * @param byteSize ���� ������ ����Ʈ ũ���Դϴ�.
	 * @param usage ���� ������ ��� �����Դϴ�.
	 */
	explicit VertexBuffer(uint32_t byteSize, const EUsage& usage);


	/**
	 * @brief ���̴����� ��� ������ ���� ���۸� �����մϴ�.
	 *
	 * @param bufferPtr �ʱ�ȭ�� ������ �������Դϴ�.
	 * @param byteSize ���� ������ ����Ʈ ũ���Դϴ�.
	 * @param usage ���� ������ ��� �����Դϴ�.
	 */
	explicit VertexBuffer(const void* bufferPtr, uint32_t byteSize, const EUsage& usage);


	/**
	 * @brief ���̴����� ��� ������ ���� ���۸� �Ҵ� �����մϴ�.
	 */
	virtual ~VertexBuffer();


	/**
	 * @brief ���� ������ ���� �����ڿ� ���� �����ڸ� ��������� �����մϴ�.
	 */
	DISALLOW_COPY_AND_ASSIGN(VertexBuffer);


	/**
	 * @brief ���� ������ ���ο��� �Ҵ�� ���ҽ��� �Ҵ��� �����մϴ�.
	 */
	virtual void Release() override;


	/**
	 * @brief ���� ���۸� ���ε��մϴ�.
	 */
	void Bind();


	/**
	 * @brief ���� ������ ���ε��� �����մϴ�.
	 */
	void Unbind();


	/**
	 * @brief ���� ���ۿ� �����͸� ���ϴ�.
	 *
	 * @param bufferPtr ���ۿ� �� �������� �������Դϴ�.
	 * @param bufferSize ���ۿ� �� �������� ũ���Դϴ�.
	 */
	void SetBufferData(const void* bufferPtr, uint32_t bufferSize);


private:
	/**
	 * @brief ���� ���� ������Ʈ ID�Դϴ�.
	 */
	uint32_t vertexBufferID_ = 0;


	/**
	 * @brief ���� ������ ����Ʈ ũ���Դϴ�.
	 */
	uint32_t byteSize_ = 0;


	/**
	 * @brief ���� ������ ��� �����Դϴ�.
	 */
	EUsage usage_ = EUsage::Static;
};