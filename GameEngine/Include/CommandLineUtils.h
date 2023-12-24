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