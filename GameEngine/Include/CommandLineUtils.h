#pragma once

#include <string>
#include <unordered_map>


/**
 * @brief Ŀ�ǵ� ����(�����)�� ���� Ȯ�� ����� �����մϴ�.
 *
 * @note
 * - �� Ȯ�� ����� "<key>=<value>" ������� �����մϴ�.
 * - �� Ȯ�� ����� std::wstring ǥ�� ���ڿ��� ������� �����մϴ�.
 */
namespace CommandLineUtils
{
	/**
	 * @brief Ŀ�ǵ� ����(�����)�� �Ľ��մϴ�.
	 *
	 * @note
	 * - �� �޼���� ���α׷� ���� �� �� �� ���� ȣ���� �� �ֽ��ϴ�.
	 * - ���ο��� ��ü ������� ã�� �Ľ��� �����մϴ�.
	 */
	void Parse();


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
	bool GetBoolValue(const std::string& key, bool& value);


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
	bool GetBoolValue(const std::wstring& key, bool& value);


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
	bool GetIntValue(const std::string& key, int32_t& value);


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
	bool GetIntValue(const std::wstring& key, int32_t& value);


	/**
	 * @brief Ű ���� �����ϴ� �ε� �Ҽ��� Ÿ�� ���� ����ϴ�.
	 *
	 * @param key ���� �����ϴ� Ű ���Դϴ�.
	 * @param value Ű ���� �����ϴ� �ε� �Ҽ��� ���Դϴ�.
	 *
	 * @return Ű ���� �����ϴ� �ε� �Ҽ��� Ÿ�� ���� ��� �� �����ߴٸ� true, �׷��� �ʴٸ� false�� ��ȯ�մϴ�.
	 */
	bool GetFloatValue(const std::string& key, float& value);


	/**
	 * @brief Ű ���� �����ϴ� �ε� �Ҽ��� Ÿ�� ���� ����ϴ�.
	 *
	 * @param key ���� �����ϴ� Ű ���Դϴ�.
	 * @param value Ű ���� �����ϴ� �ε� �Ҽ��� ���Դϴ�.
	 *
	 * @return Ű ���� �����ϴ� �ε� �Ҽ��� Ÿ�� ���� ��� �� �����ߴٸ� true, �׷��� �ʴٸ� false�� ��ȯ�մϴ�.
	 */
	bool GetFloatValue(const std::wstring& key, float& value);


	/**
	 * @brief Ű ���� �����ϴ� ���ڿ� Ÿ�� ���� ����ϴ�.
	 *
	 * @param key ���� �����ϴ� Ű ���Դϴ�.
	 * @param value Ű ���� �����ϴ� ���ڿ� ���Դϴ�.
	 *
	 * @return Ű ���� �����ϴ� ���ڿ� Ÿ�� ���� ��� �� �����ߴٸ� true, �׷��� �ʴٸ� false�� ��ȯ�մϴ�.
	 */
	bool GetStringValue(const std::string& key, std::string& value);


	/**
	 * @brief Ű ���� �����ϴ� ���ڿ� Ÿ�� ���� ����ϴ�.
	 *
	 * @param key ���� �����ϴ� Ű ���Դϴ�.
	 * @param value Ű ���� �����ϴ� ���ڿ� ���Դϴ�.
	 *
	 * @return Ű ���� �����ϴ� ���ڿ� Ÿ�� ���� ��� �� �����ߴٸ� true, �׷��� �ʴٸ� false�� ��ȯ�մϴ�.
	 */
	bool GetStringValue(const std::string& key, std::wstring& value);


	/**
	 * @brief Ű ���� �����ϴ� ���ڿ� Ÿ�� ���� ����ϴ�.
	 *
	 * @param key ���� �����ϴ� Ű ���Դϴ�.
	 * @param value Ű ���� �����ϴ� ���ڿ� ���Դϴ�.
	 *
	 * @return Ű ���� �����ϴ� ���ڿ� Ÿ�� ���� ��� �� �����ߴٸ� true, �׷��� �ʴٸ� false�� ��ȯ�մϴ�.
	 */
	bool GetStringValue(const std::wstring& key, std::string& value);


	/**
	 * @brief Ű ���� �����ϴ� ���ڿ� Ÿ�� ���� ����ϴ�.
	 *
	 * @param key ���� �����ϴ� Ű ���Դϴ�.
	 * @param value Ű ���� �����ϴ� ���ڿ� ���Դϴ�.
	 *
	 * @return Ű ���� �����ϴ� ���ڿ� Ÿ�� ���� ��� �� �����ߴٸ� true, �׷��� �ʴٸ� false�� ��ȯ�մϴ�.
	 */
	bool GetStringValue(const std::wstring& key, std::wstring& value);


	/**
	 * @brief Ű ���� ��ȿ���� Ȯ���մϴ�.
	 *
	 * @param key ��ȿ���� Ȯ���� Ű ���Դϴ�.
	 *
	 * @return Ű ���� ��ȿ�ϴٸ� true, �׷��� �ʴٸ� false�� ��ȯ�մϴ�.
	 */
	bool IsValid(const std::wstring& key);
};