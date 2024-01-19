#pragma once

#include "IObject.h"


/**
 * @brief UI ������Ʈ�Դϴ�.
 */
class UIObject : public IObject
{
public:
	/**
	 * @brief UI ������Ʈ�� ����Ʈ �������Դϴ�.
	 */
	UIObject() = default;


	/**
	 * @brief UI ������Ʈ�� ���� �Ҹ����Դϴ�.
	 */
	virtual ~UIObject() {}


	/**
	 * @brief UI ������Ʈ�� ���� �����ڿ� ���� �����ڸ� ��������� �����մϴ�.
	 */
	DISALLOW_COPY_AND_ASSIGN(UIObject);


	/**
	 * @brief UI�� ȭ�鿡 �׸��ϴ�.
	 */
	virtual void Render() = 0;
};