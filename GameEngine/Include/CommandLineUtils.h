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
	 * - ��ü Ŀ�ǵ� ������ ���� ���� ��ΰ� ���ܵ� ���ڿ��� �����ؾ� �մϴ�.
	 * 
	 * @param commandLine ��ü ����� ���ڿ��� �������Դϴ�.
	 */
	static void Parse(const wchar_t* commandLine);


	/**
	 * @brief Ŀ�ǵ� ����(����� ����)�� �Ľ��մϴ�.
	 * 
	 * @note
	 * - �� �޼���� ���α׷� ���� �� �� �� ���� ȣ���� �� �ֽ��ϴ�.
	 * - ��ü ������� ���ڸ� ���ͷ� �����ؾ� �մϴ�.
	 * - ���� ������ "<key>=<value>" ���ĸ� �����մϴ�.
	 * 
	 * @param arguments ���� ���� ��θ� ������ ����� �����Դϴ�.
	 */
	static void ParseArguments(const std::vector<std::wstring>& arguments);


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