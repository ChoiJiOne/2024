#pragma once

#include "Macro.h"


/**
 * @brief �� �������̽��Դϴ�.
 * 
 * @note ���� ���� ���� ��� �� �������̽��� ��ӹ޾ƾ� �մϴ�.
 */
class IScene
{
public:
	/**
	 * @brief ���� ����Ʈ �������Դϴ�.
	 */
	IScene() = default;


	/**
	 * @brief ���� ���� �Ҹ����Դϴ�.
	 */
	virtual ~IScene() {}


	/**
	 * @brief ���� ���� �����ڿ� ���� �����ڸ� ��������� �����մϴ�.
	 */
	DISALLOW_COPY_AND_ASSIGN(IScene);


	/**
	 * @brief ���� �� �������� �����մϴ�.
	 *
	 * @param deltaSeconds ��Ÿ �ð����Դϴ�.
	 */
	virtual void Tick(float deltaSeconds) = 0;
};