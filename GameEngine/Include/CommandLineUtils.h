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
	void Parse(const wchar_t* commandLine);


private:
	/**
	 * @brief �ʱ�ȭ�� ���� �ִ��� Ȯ���մϴ�.
	 */
	static bool bIsInitialized_;
};