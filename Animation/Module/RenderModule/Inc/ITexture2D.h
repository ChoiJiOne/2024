#pragma once

#include <cstdint>

#include "IResource.h"


/**
 * @brief 2D �ؽ�ó ���ҽ� �������̽��Դϴ�.
 */
class ITexture2D : public IResource
{
public:
	/**
	 * @brief 2D �ؽ�ó ���ҽ� �������̽��� ����Ʈ �������Դϴ�.
	 */
	ITexture2D() = default;


	/**
	 * @brief 2D �ؽ�ó ���ҽ� �������̽��� ���� �Ҹ����Դϴ�.
	 */
	virtual ~ITexture2D() {}


	/**
	 * @brief 2D �ؽ�ó ���ҽ� �������̽� ���� ���ҽ��� �Ҵ� �����մϴ�.
	 *
	 * @note 2D �ؽ�ó ���ҽ� �������̽��� ��ӹ޴� ���� Ŭ�������� �ݵ�� �����ؾ� �մϴ�.
	 */
	virtual void Release() = 0;


	/**
	 * @brief �ؽ�ó�� Ȱ��ȭ�մϴ�.
	 *
	 * @param unit Ȱ��ȭ �� �ؽ�ó �����Դϴ�.
	 */
	virtual void Active(uint32_t unit) const = 0;
};