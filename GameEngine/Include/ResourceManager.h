#pragma once

#include <cstdint>
#include <string>
#include <memory>
#include <unordered_map>

#include "IManager.h"
#include "IResource.h"


/**
 * @brief ���ҽ� ������ �����ϴ� �Ŵ����Դϴ�.
 * 
 * @note �� Ŭ������ �̱����Դϴ�.
 */
class ResourceManager : public IManager
{
public:
	/**
	 * @brief ���ҽ� ������ �����ϴ� �Ŵ����� ���� �����ڿ� ���� �����ڸ� ��������� �����մϴ�.
	 */
	DISALLOW_COPY_AND_ASSIGN(ResourceManager);


	/**
	 * @brief ���ҽ� ������ �����ϴ� �Ŵ����� ���� �ν��Ͻ��� ����ϴ�.
	 *
	 * @return ���ҽ� ������ �����ϴ� �Ŵ����� �����ڸ� ��ȯ�մϴ�.
	 */
	static ResourceManager& Get()
	{
		static ResourceManager instance;
		return instance;
	}


	/**
	 * @brief ���ҽ� ������ �����ϴ� �Ŵ����� ����� �����մϴ�.
	 *
	 * @note �� �޼���� �� ���� ȣ��Ǿ�� �մϴ�.
	 */
	virtual void Startup() override;


	/**
	 * @brief ���ҽ� ������ �����ϴ� �Ŵ����� ����� �����մϴ�.
	 *
	 * @note
	 * - ���ø����̼� ���� ���� �� �޼��带 �ݵ�� ȣ���Ͽ� ���� ���ҽ��� �����ؾ� �մϴ�.
	 * - �� �޼���� �ݵ�� �� ���� ȣ��Ǿ�� �մϴ�.
	 */
	virtual void Shutdown() override;


private:
	/**
	 * @brief ���ҽ� ������ �����ϴ� �Ŵ����� ����Ʈ �����ڿ� �� ���� �Ҹ��ڸ� �����մϴ�.
	 */
	DEFAULT_CONSTRUCTOR_AND_VIRTUAL_DESTRUCTOR(ResourceManager);


	/**
	 * @brief Ű ���� ��ȿ���� Ȯ���մϴ�.
	 * 
	 * @param key ��ȿ���� Ȯ���� Ű ���Դϴ�.
	 * 
	 * @return Ű ���� �����ϴ� ���ҽ��� �����ϸ� true, �׷��� ������ false�� ��ȯ�մϴ�.
	 */
	bool IsValidResourceKey(const std::string& key);


private:
	/**
	 * @brief ���ҽ� �Ŵ��� ���� ���ҽ� ĳ���Դϴ�.
	 */
	std::unordered_map<std::string, std::unique_ptr<IResource>> resourceCache_;
};