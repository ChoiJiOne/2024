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
	 * @note �� �޼���� ���α׷� ���� �� �� �� ���� ȣ���� �� �ֽ��ϴ�.
	 * 
	 * @param commandLine ��ü ����� ���ڿ��� �������Դϴ�.
	 */
	static void Parse(const wchar_t* commandLine);


	/**
	 * @brief ���� ���� ��θ� ����ϴ�.
	 * 
	 * @return ���� ���� ��θ� ��ȯ�մϴ�.
	 */
	static std::wstring GetExecutePath() { return executePath_; }


private:
	/**
	 * @brief �ʱ�ȭ�� ���� �ִ��� Ȯ���մϴ�.
	 */
	static bool bIsInitialized_;


	/**
	 * @brief ���� ���� ����Դϴ�.
	 */
	static std::wstring executePath_;


	/**
	 * @brief ����� ������ Ű-�� ���Դϴ�.
	 */
	static std::unordered_map<std::wstring, std::wstring> argumentMaps_;
};