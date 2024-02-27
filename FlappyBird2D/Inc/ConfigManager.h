#pragma once

#include "IManager.h"
#include "IResource.h"


/**
 * @brief ��ü ������ �����ϴ� �Ŵ����Դϴ�.
 * 
 * @note �� Ŭ������ �̱����Դϴ�.
 */
class ConfigManager : public IManager
{
public:
	/**
	 * @brief ������ ��׶��� �����Դϴ�.
	 */
	enum class EBackground : int32_t
	{
		Day   = 0x00,
		Night = 0x01,
	};


public:
	/**
	 * @brief ��ü ������ �����ϴ� �Ŵ����� ���� �����ڿ� ���� �����ڸ� ��������� �����մϴ�.
	 */
	DISALLOW_COPY_AND_ASSIGN(ConfigManager);


	/**
	 * @brief ��ü ������ �����ϴ� �Ŵ����� ���� �ν��Ͻ��� ����ϴ�.
	 *
	 * @return ��ü ������ �����ϴ� �Ŵ����� ���� �ν��Ͻ��� ��ȯ�մϴ�.
	 */
	static ConfigManager& Get();


	/**
	 * @brief ��ü ������ �����ϴ� �Ŵ����� ����� �����մϴ�.
	 *
	 * @note �� �޼���� �� ���� ȣ��Ǿ�� �մϴ�.
	 */
	virtual void Startup() override;


	/**
	 * @brief ��ü ������ �����ϴ� �Ŵ����� ����� �����մϴ�.
	 *
	 * @note
	 * - ���ø����̼� ���� ���� �� �޼��带 �ݵ�� ȣ���Ͽ� ���θ� �����ؾ� �մϴ�.
	 * - �� �޼���� �ݵ�� �� ���� ȣ��Ǿ�� �մϴ�.
	 */
	virtual void Shutdown() override;


	/**
	 * @brief ���� ��� ���ҽ��� ID ���� ����ϴ�.
	 * 
	 * @return ���� ��� ���ҽ��� ID ���� ��ȯ�մϴ�.
	 */
	RUID GetCurrentBackgroundID() { return currentBackgroundID_; }


	/**
	 * @brief ���� ����� �����մϴ�.
	 * 
	 * @param background ������ ��׶����Դϴ�.
	 */
	void SetCurrentBackgroundID(const EBackground& background);


private:
	/**
	 * @brief ��ü ������ �����ϴ� �Ŵ����� ����Ʈ �����ڿ� �� ���� �Ҹ��ڸ� �����մϴ�.
	 */
	DEFAULT_CONSTRUCTOR_AND_VIRTUAL_DESTRUCTOR(ConfigManager);


private:
	/**
	 * @brief ���� ��� ���ҽ��� ID ���Դϴ�.
	 */
	RUID currentBackgroundID_ = -1;

	
	/**
	 * @brief �� ��� ���ҽ��� ID ���Դϴ�.
	 */
	RUID dayBackgroundID_ = -1;


	/**
	 * @brief �� ��� ���ҽ��� ID ���Դϴ�.
	 */
	RUID nightBackgroundID_ = -1;
};