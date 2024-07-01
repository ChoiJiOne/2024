#pragma once

#include <cstdint>

#include "IResource.h"


namespace GameMaker
{
/**
 * @brief �޽� ���ҽ� �������̽��Դϴ�.
 */
class IMesh : public IResource
{
public:
	/**
	 * @brief �޽� ���ҽ� �������̽��� ����Ʈ �������Դϴ�.
	 */
	IMesh() = default;


	/**
	 * @brief �޽� ���ҽ� �������̽��� ���� �Ҹ����Դϴ�.
	 */
	virtual ~IMesh() {}


	/**
	 * @brief �޽� ���ҽ� �������̽� ���� ���ҽ��� �Ҵ� �����մϴ�.
	 * 
	 * @note �޽� ���ҽ� �������̽��� ��ӹ޴� ���� Ŭ�������� �ݵ�� �����ؾ� �մϴ�.
	 */
	virtual void Release() = 0;


	/**
	 * @brief �޽� ���ҽ� �������̽��� ���������ο� ���ε��մϴ�.
	 */
	virtual void Bind() const = 0;


	/**
	 * @brief ���ε��� �޽� ���ҽ� �������̽��� ���ε� �����մϴ�.
	 */
	virtual void Unbind() const = 0;


	/**
	 * @brief �޽��� �ε��� ���� ����ϴ�.
	 *
	 * @return �޽��� �ε��� ���� ��ȯ�մϴ�.
	 */
	virtual uint32_t GetIndexCount() const = 0;


	/**
	 * @brief �޽��� ���� ���� ����ϴ�.
	 * 
	 * @return �޽��� ���� ���� ��ȯ�մϴ�.
	 */
	virtual uint32_t GetVertexCount() const = 0;
};

}