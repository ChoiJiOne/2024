#pragma once

#include <cstdint>

#include "IResource.h"


namespace GameMaker
{
/**
 * @brief �ؽ�ó ���ҽ� �������̽��Դϴ�.
 */
class ITexture : public IResource
{
public:
	/**
	 * @brief �ؽ�ó ���ҽ� �������̽��� ����Ʈ �������Դϴ�.
	 */
	ITexture() = default;


	/**
	 * @brief �ؽ�ó ���ҽ� �������̽��� ���� �Ҹ����Դϴ�.
	 */
	virtual ~ITexture() {}


	/**
	 * @brief �ؽ�ó ���ҽ� �������̽� ���� ���ҽ��� �Ҵ� �����մϴ�.
	 *
	 * @note �ؽ�ó ���ҽ� �������̽��� ��ӹ޴� ���� Ŭ�������� �ݵ�� �����ؾ� �մϴ�.
	 */
	virtual void Release() = 0;


	/**
	 * @brief �ؽ�ó�� Ȱ��ȭ�մϴ�.
	 *
	 * @param unit Ȱ��ȭ �� �ؽ�ó �����Դϴ�.
	 */
	virtual void Active(uint32_t unit) const = 0;
};

}