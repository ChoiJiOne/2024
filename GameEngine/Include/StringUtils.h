#pragma once

#include <vector>
#include <string>
#include <cstdarg>


/**
 * @brief ǥ�� ���ڿ�(std::string, std::wstring)�� Ȯ�� ����� �����մϴ�.
 */
class StringUtils
{
public:


private:
	/**
	 * @brief ���ڿ� ������ ũ���Դϴ�.
	 */
	static const int32_t STRING_BUFFER_SIZE = 1024;


	/**
	 * @brief char ���ڿ� �����Դϴ�.
	 */
	static char charBuffer_[STRING_BUFFER_SIZE];


	/**
	 * @brief wchar_t ���ڿ� �����Դϴ�.
	 */
	static wchar_t wcharBuffer_[STRING_BUFFER_SIZE];
};