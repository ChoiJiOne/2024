#pragma once

#include <memory>
#include <string>

#include "IResource.h"

#include <miniaudio.h>


/**
 * @brief �÷��� ������ ���� ���ҽ��Դϴ�.
 */
class Sound : public IResource
{
public:
	/**
	 * @brief ������ ����Ʈ �������Դϴ�.
	 * 
	 * @note ������ �̿��� �޼��忡�� ������ �ʱ�ȭ�� �����ؾ� �մϴ�.
	 */
	Sound() = default;


	/**
	 * @brief ������ ���� �Ҹ����Դϴ�.
	 * 
	 * @note ���� ���ο��� �Ҵ�� ��Ҹ� �����ϱ� ���ؼ��� �ݵ�� Release�� ȣ���ؾ� �մϴ�.
	 */
	virtual ~Sound();


	/**
	 * @brief ������ ���� �����ڿ� ���� �����ڸ� ��������� �����մϴ�.
	 */
	DISALLOW_COPY_AND_ASSIGN(Sound);


	/**
	 * @brief ���� ������ �ε��ϰ� �ʱ�ȭ�մϴ�.
	 * 
	 * @param path ���� ������ ����Դϴ�.
	 */
	void Initialize(const std::wstring& path);


	/**
	 * @brief ������ ���� ���ҽ��� �Ҵ� �����մϴ�.
	 */
	virtual void Release() override;


private:
	/**
	 * @brief miniaudio ���� ���ҽ��Դϴ�.
	 */
	std::unique_ptr<ma_sound> sound_ = nullptr;
};