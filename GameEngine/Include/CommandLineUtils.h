#pragma once

#include <string>
#include <unordered_map>


/**
 * @brief Ŀ�ǵ� ����(�����)�� ���� Ȯ�� ����� �����մϴ�.
 * 
 * @note
 * - �� Ŭ������ ����� "<key>=<value>" ������� �����մϴ�.
 * - �� Ȯ�� ����� std::wstring ǥ�� ���ڿ��� ������� �����մϴ�.
 * - �� Ŭ������ ��� ��� ������ �޼���� ��� static�Դϴ�.
 */
class CommandLineUtils
{
public:
	/**
	 * @brief Ŀ�ǵ� ����(�����)�� �Ľ��մϴ�.
	 * 
	 * @note
	 * - �� �޼���� ���α׷� ���� �� �� �� ���� ȣ���� �� �ֽ��ϴ�.
	 * - ���ο��� ��ü ������� ã�� �Ľ��� �����մϴ�.
	 */
	static void Parse();


	/**
	 * @brief Ű ���� �����ϴ� �Ҹ��� Ÿ�� ���� ����ϴ�.
	 * 
	 * @param key ���� �����ϴ� Ű ���Դϴ�.
	 * @param value Ű ���� �����ϴ� �Ҹ��� ���Դϴ�.
	 * 
	 * @return Ű ���� �����ϴ� �Ҹ��� Ÿ�� ���� ��� �� �����ߴٸ� true, �׷��� ������ false�� ��ȯ�մϴ�.
	 * 
	 * @note boolean ������ true, True, TRUE, false, False, FALSE ��� �����մϴ�.
	 */
	static bool GetBoolValue(const std::string& key, bool& value);


	/**
	 * @brief Ű ���� �����ϴ� �Ҹ��� Ÿ�� ���� ����ϴ�.
	 *
	 * @param key ���� �����ϴ� Ű ���Դϴ�.
	 * @param value Ű ���� �����ϴ� �Ҹ��� ���Դϴ�.
	 *
	 * @return Ű ���� �����ϴ� �Ҹ��� Ÿ�� ���� ��� �� �����ߴٸ� true, �׷��� ������ false�� ��ȯ�մϴ�.
	 * 
	 * @note boolean ������ true, True, TRUE, false, False, FALSE ��� �����մϴ�.
	 */
	static bool GetBoolValue(const std::wstring& key, bool& value);


	/**
	 * @brief Ű ���� �����ϴ� ���� Ÿ�� ���� ����ϴ�.
	 * 
	 * @param key ���� �����ϴ� Ű ���Դϴ�.
	 * @param value Ű ���� �����ϴ� ���� ���Դϴ�.
	 * 
	 * @return Ű ���� �����ϴ� ���� Ÿ�� ���� ��� �� �����ߴٸ� true, �׷��� �ʴٸ� false�� ��ȯ�մϴ�.
	 * 
	 * @note ���� ������ �����մϴ�.
	 */
	static bool GetIntValue(const std::string& key, int32_t& value);


	/**
	 * @brief Ű ���� �����ϴ� ���� Ÿ�� ���� ����ϴ�.
	 *
	 * @param key ���� �����ϴ� Ű ���Դϴ�.
	 * @param value Ű ���� �����ϴ� ���� ���Դϴ�.
	 *
	 * @return Ű ���� �����ϴ� ���� Ÿ�� ���� ��� �� �����ߴٸ� true, �׷��� �ʴٸ� false�� ��ȯ�մϴ�.
	 *
	 * @note ���� ������ �����մϴ�.
	 */
	static bool GetIntValue(const std::wstring& key, int32_t& value);


	/**
	 * @brief Ű ���� �����ϴ� �ε� �Ҽ��� Ÿ�� ���� ����ϴ�.
	 *
	 * @param key ���� �����ϴ� Ű ���Դϴ�.
	 * @param value Ű ���� �����ϴ� �ε� �Ҽ��� ���Դϴ�.
	 *
	 * @return Ű ���� �����ϴ� �ε� �Ҽ��� Ÿ�� ���� ��� �� �����ߴٸ� true, �׷��� �ʴٸ� false�� ��ȯ�մϴ�.
	 */
	static bool GetFloatValue(const std::string& key, float& value);


	/**
	 * @brief Ű ���� �����ϴ� �ε� �Ҽ��� Ÿ�� ���� ����ϴ�.
	 *
	 * @param key ���� �����ϴ� Ű ���Դϴ�.
	 * @param value Ű ���� �����ϴ� �ε� �Ҽ��� ���Դϴ�.
	 *
	 * @return Ű ���� �����ϴ� �ε� �Ҽ��� Ÿ�� ���� ��� �� �����ߴٸ� true, �׷��� �ʴٸ� false�� ��ȯ�մϴ�.
	 */
	static bool GetFloatValue(const std::wstring& key, float& value);


	/**
	 * @brief Ű ���� �����ϴ� ���ڿ� Ÿ�� ���� ����ϴ�.
	 *
	 * @param key ���� �����ϴ� Ű ���Դϴ�.
	 * @param value Ű ���� �����ϴ� ���ڿ� ���Դϴ�.
	 *
	 * @return Ű ���� �����ϴ� ���ڿ� Ÿ�� ���� ��� �� �����ߴٸ� true, �׷��� �ʴٸ� false�� ��ȯ�մϴ�.
	 */
	static bool GetStringValue(const std::string& key, std::string& value);


	/**
	 * @brief Ű ���� �����ϴ� ���ڿ� Ÿ�� ���� ����ϴ�.
	 *
	 * @param key ���� �����ϴ� Ű ���Դϴ�.
	 * @param value Ű ���� �����ϴ� ���ڿ� ���Դϴ�.
	 *
	 * @return Ű ���� �����ϴ� ���ڿ� Ÿ�� ���� ��� �� �����ߴٸ� true, �׷��� �ʴٸ� false�� ��ȯ�մϴ�.
	 */
	static bool GetStringValue(const std::string& key, std::wstring& value);


	/**
	 * @brief Ű ���� �����ϴ� ���ڿ� Ÿ�� ���� ����ϴ�.
	 *
	 * @param key ���� �����ϴ� Ű ���Դϴ�.
	 * @param value Ű ���� �����ϴ� ���ڿ� ���Դϴ�.
	 *
	 * @return Ű ���� �����ϴ� ���ڿ� Ÿ�� ���� ��� �� �����ߴٸ� true, �׷��� �ʴٸ� false�� ��ȯ�մϴ�.
	 */
	static bool GetStringValue(const std::wstring& key, std::string& value);


	/**
	 * @brief Ű ���� �����ϴ� ���ڿ� Ÿ�� ���� ����ϴ�.
	 *
	 * @param key ���� �����ϴ� Ű ���Դϴ�.
	 * @param value Ű ���� �����ϴ� ���ڿ� ���Դϴ�.
	 *
	 * @return Ű ���� �����ϴ� ���ڿ� Ÿ�� ���� ��� �� �����ߴٸ� true, �׷��� �ʴٸ� false�� ��ȯ�մϴ�.
	 */
	static bool GetStringValue(const std::wstring& key, std::wstring& value);


private:
	/**
	 * @brief Ű ���� ��ȿ���� Ȯ���մϴ�.
	 * 
	 * @param key ��ȿ���� Ȯ���� Ű ���Դϴ�.
	 * 
	 * @return Ű ���� ��ȿ�ϴٸ� true, �׷��� �ʴٸ� false�� ��ȯ�մϴ�.
	 */
	static bool IsValid(const std::wstring& key);

	
private:
	/**
	 * @brief �ʱ�ȭ�� ���� �ִ��� Ȯ���մϴ�.
	 */
	static bool bIsInitialized_;


	/**
	 * @brief ����� ������ Ű-�� ���Դϴ�.
	 */
	static std::unordered_map<std::wstring, std::wstring> argumentMaps_;
};