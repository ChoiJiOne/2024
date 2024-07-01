#pragma once

#include <cstdint>

#include "IResource.h"


namespace GameMaker
{
/**
 * @brief ������ �����Դϴ�.
 */
class UniformBuffer : public IResource
{
public:
	/**
	 * @brief ������ ������ ��� �����Դϴ�.
	 *
	 * @see https://registry.khronos.org/OpenGL-Refpages/gl2.1/xhtml/glBufferData.xml
	 */
	enum class EUsage
	{
		STREAM  = 0x88E0,
		STATIC  = 0x88E4,
		DYNAMIC = 0x88E8,
	};


public:
	/**
	 * @brief ������ ���۸� �����մϴ�.
	 *
	 * @param byteSize ������ ������ ����Ʈ ũ���Դϴ�.
	 * @param usage ������ ������ ��� �����Դϴ�.
	 */
	UniformBuffer(uint32_t byteSize, const EUsage& usage);


	/**
	 * @brief ������ ���۸� �����մϴ�.
	 *
	 * @param bufferPtr �ʱ�ȭ�� ������ �������Դϴ�.
	 * @param byteSize ������ ������ ����Ʈ ũ���Դϴ�.
	 * @param usage ������ ������ ��� �����Դϴ�.
	 */
	UniformBuffer(const void* bufferPtr, uint32_t byteSize, const EUsage& usage);


	/**
	 * @brief ������ ���۸� �Ҵ� �����մϴ�.
	 */
	virtual ~UniformBuffer();


	/**
	 * @brief ������ ������ ���� �����ڿ� ���� �����ڸ� ��������� �����մϴ�.
	 */
	DISALLOW_COPY_AND_ASSIGN(UniformBuffer);


	/**
	 * @brief ������ ������ ���ο��� �Ҵ�� ���ҽ��� �Ҵ��� �����մϴ�.
	 */
	virtual void Release() override;


	/**
	 * @brief ������ ���۸� ���ε��մϴ�.
	 */
	void Bind();


	/**
	 * @brief ������ ���۸� ������ ���ε� ����Ʈ�� ���ε��մϴ�.
	 *
	 * @param slot ������ ���۸� ���ε��� �����Դϴ�.
	 *
	 * @see https://registry.khronos.org/OpenGL-Refpages/gl4/html/glBindBufferBase.xhtml
	 */
	void Bind(const uint32_t slot);


	/**
	 * @brief ������ ������ ���ε��� �����մϴ�.
	 */
	void Unbind();


	/**
	 * @brief ������ ���ۿ� �����͸� ���ϴ�.
	 *
	 * @param bufferPtr ���ۿ� �� �������� �������Դϴ�.
	 * @param bufferSize ���ۿ� �� �������� ũ���Դϴ�.
	 */
	void SetBufferData(const void* bufferPtr, uint32_t bufferSize);


private:
	/**
	 * @brief ������ ���� ������Ʈ ID�Դϴ�.
	 */
	uint32_t uniformBufferID_ = 0;


	/**
	 * @brief ������ ������ ����Ʈ ũ���Դϴ�.
	 */
	uint32_t byteSize_ = 0;


	/**
	 * @brief ������ ������ ��� �����Դϴ�.
	 */
	EUsage usage_ = EUsage::STATIC;
};

}