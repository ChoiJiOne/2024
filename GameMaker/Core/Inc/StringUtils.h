#pragma once

#include <vector>
#include <string>
#include <cstdarg>


namespace GameMaker
{
/**
 * @brief ���ڿ��� Ȯ�� ����� �����մϴ�.
 *
 * @note 
 * - ���ڿ��� std::string, std::wstring ǥ�� ���ڿ� �����Դϴ�.
 * - �� Ŭ������ ��� ��� ������ �޼���� ����(static) Ÿ���Դϴ�.
 */
class StringUtils
{
public:
	/**
	 * @brief ����ȭ�� ���ڿ��� ��ȯ�մϴ�.
	 *
	 * @note
	 * - �� �޼���� snprintf�� ���� �Լ��� ��ü�ϱ� ���� ���Դϴ�.
	 * - ���ڿ��� ���̴� �ִ� 1024 �Դϴ�.
	 *
	 * @param format ���� ���ڿ��Դϴ�.
	 * @param ... ���ڿ��� ���Ŀ� �����ϴ� ���������Դϴ�.
	 *
	 * @return ����ȭ�� ǥ�� ���ڿ��� ��ȯ�մϴ�.
	 *
	 * @see https://learn.microsoft.com/ko-kr/cpp/c-runtime-library/reference/vsnprintf-vsnprintf-vsnprintf-l-vsnwprintf-vsnwprintf-l?view=msvc-170
	 */
	static std::string PrintF(const char* format, ...);


	/**
	 * @brief ����ȭ�� ���ڿ��� ��ȯ�մϴ�.
	 *
	 * @note
	 * - �� �޼���� snprintf�� ���� �Լ��� ��ü�ϱ� ���� ���Դϴ�.
	 * - ���ڿ��� ���̴� �ִ� 1024 �Դϴ�.
	 *
	 * @param format ���� ���ڿ��Դϴ�.
	 * @param ... ���ڿ��� ���Ŀ� �����ϴ� ���������Դϴ�.
	 *
	 * @return ����ȭ�� ǥ�� ���ڿ��� ��ȯ�մϴ�.
	 *
	 * @see https://learn.microsoft.com/ko-kr/cpp/c-runtime-library/reference/vsnprintf-vsnprintf-vsnprintf-l-vsnwprintf-vsnwprintf-l?view=msvc-170
	 */
	static std::wstring PrintF(const wchar_t* format, ...);


	/**
	 * @brief Ư�� ���ڿ��� �������� �ؽ�Ʈ�� �и��մϴ�.
	 *
	 * @param text �и��� ��� ���ڿ��Դϴ�.
	 * @param delimiter �и��� ���� ���� ���ڿ��Դϴ�.
	 *
	 * @return �и��� ���ڿ��� ��� �ִ� ����(std::vector)�� ��ȯ�մϴ�.
	 */
	static std::vector<std::string> Split(const std::string& text, const std::string& delimiter);


	/**
	 * @brief Ư�� ���ڿ��� �������� �ؽ�Ʈ�� �и��մϴ�.
	 *
	 * @param text �и��� ��� ���ڿ��Դϴ�.
	 * @param delimiter �и��� ���� ���� ���ڿ��Դϴ�.
	 *
	 * @return �и��� ���ڿ��� ��� �ִ� ����(std::vector)�Դϴ�.
	 */
	static std::vector<std::wstring> Split(const std::wstring& text, const std::wstring& delimiter);


	/**
	 * @brief char ���ڿ��� wchar_t ���ڿ��� ��ȯ�մϴ�.
	 *
	 * @see https://en.cppreference.com/w/cpp/string/multibyte/mbstowcs
	 *
	 * @param text ��ȯ�� ǥ�� �ؽ�Ʈ�Դϴ�.
	 *
	 * @return ��ȯ�� ���ڿ��� ��ȯ�մϴ�.
	 */
	static std::wstring Convert(const std::string& text);


	/**
	 * @brief wchar_t ���ڿ��� char ���ڿ��� ��ȯ�մϴ�.
	 *
	 * @see https://en.cppreference.com/w/cpp/string/multibyte/wcstombs
	 *
	 * @param text ��ȯ�� ǥ�� �ؽ�Ʈ�Դϴ�.
	 *
	 * @return ��ȯ�� ���ڿ��� ��ȯ�մϴ�.
	 */
	static std::string Convert(const std::wstring& text);


	/**
	 * @brief ���ڿ��� ���ĺ��� ��� �ҹ��ڷ� ��ȯ�մϴ�.
	 *
	 * @param text ��ȯ�� ���ڿ��Դϴ�.
	 *
	 * @return ���ڿ� ���� ���ĺ��� ��� �ҹ��ڷ� ��ȯ�� ��ü ���ڿ��� ��ȯ�մϴ�.
	 */
	static std::string ToLower(const std::string& text);


	/**
	 * @brief ���ڿ��� ���ĺ��� ��� �ҹ��ڷ� ��ȯ�մϴ�.
	 *
	 * @param text ��ȯ�� ���ڿ��Դϴ�.
	 *
	 * @return ���ڿ� ���� ���ĺ��� ��� �ҹ��ڷ� ��ȯ�� ��ü ���ڿ��� ��ȯ�մϴ�.
	 */
	static std::wstring ToLower(const std::wstring& text);


	/**
	 * @brief ���ڿ��� ���ĺ��� ��� �빮�ڷ� ��ȯ�մϴ�.
	 *
	 * @param text ��ȯ�� ���ڿ��Դϴ�.
	 *
	 * @return ���ڿ� ���� ���ĺ��� ��� �빮�ڷ� ��ȯ�� ��ü ���ڿ��� ��ȯ�մϴ�.
	 */
	static std::string ToUpper(const std::string& text);


	/**
	 * @brief ���ڿ��� ���ĺ��� ��� �빮�ڷ� ��ȯ�մϴ�.
	 *
	 * @param text ��ȯ�� ���ڿ��Դϴ�.
	 *
	 * @return ���ڿ� ���� ���ĺ��� ��� �빮�ڷ� ��ȯ�� ��ü ���ڿ��� ��ȯ�մϴ�.
	 */
	static std::wstring ToUpper(const std::wstring& text);


	/**
	 * @brief ������ ������ ���ڿ��� 10���� ���� ������ ��ȯ�մϴ�.
	 *
	 * @param integer ������ ������ ���ڿ��Դϴ�.
	 * @param outInteger ��ȯ�� ���� ���� ������ ���� �����Դϴ�.
	 *
	 * @return ��ȯ�� �����ϸ� true, �׷��� ������ false�� ��ȯ�մϴ�.
	 *
	 * @see https://learn.microsoft.com/ko-kr/cpp/c-runtime-library/reference/strtol-wcstol-strtol-l-wcstol-l?view=msvc-170
	 */
	static bool ToInt(const std::string& integer, int32_t& outInteger);


	/**
	 * @brief ������ ������ ���ڿ��� 10���� ���� ������ ��ȯ�մϴ�.
	 *
	 * @param integer ������ ������ ���ڿ��Դϴ�.
	 * @param outInteger ��ȯ�� ���� ���� ������ ���� �����Դϴ�.
	 *
	 * @return ��ȯ�� �����ϸ� true, �׷��� ������ false�� ��ȯ�մϴ�.
	 *
	 * @see https://learn.microsoft.com/ko-kr/cpp/c-runtime-library/reference/strtol-wcstol-strtol-l-wcstol-l?view=msvc-170
	 */
	static bool ToInt(const std::wstring& integer, int32_t& outInteger);


	/**
	 * @brief �ε� �Ҽ������� ������ ���ڿ��� �ε� �Ҽ��� �� ������ ��ȯ�մϴ�.
	 *
	 * @param floating �ε� �Ҽ������� ������ ���ڿ��Դϴ�.
	 * @param outFloating ��ȯ�� �ε� �Ҽ��� �� ���� ������ ���� �����Դϴ�.
	 *
	 * @return ��ȯ�� �����ϸ� true, �׷��� ������ false�� ��ȯ�մϴ�.
	 *
	 * @see https://learn.microsoft.com/ko-kr/cpp/c-runtime-library/reference/strtof-strtof-l-wcstof-wcstof-l?view=msvc-170
	 */
	static bool ToFloat(const std::string& floating, float& outFloating);


	/**
	 * @brief �ε� �Ҽ������� ������ ���ڿ��� �ε� �Ҽ��� �� ������ ��ȯ�մϴ�.
	 *
	 * @param floating �ε� �Ҽ������� ������ ���ڿ��Դϴ�.
	 * @param outFloating ��ȯ�� �ε� �Ҽ��� �� ���� ������ ���� �����Դϴ�.
	 *
	 * @return ��ȯ�� �����ϸ� true, �׷��� ������ false�� ��ȯ�մϴ�.
	 *
	 * @see https://learn.microsoft.com/ko-kr/cpp/c-runtime-library/reference/strtof-strtof-l-wcstof-wcstof-l?view=msvc-170
	 */
	static bool ToFloat(const std::wstring& floating, float& outFloating);


private:
	/**
	 * @brief ���ο����� ����ϴ� ���ڿ� ������ �ִ� ũ���Դϴ�.
	 */
	static const uint32_t MAX_STRING_BUFFER_SIZE = 1024;


	/**
	 * @brief char Ÿ���� ���ڿ� �����Դϴ�.
	 */
	static char charBuffer_[MAX_STRING_BUFFER_SIZE];


	/**
	 * @brief wchar_t Ÿ���� ���ڿ� �����Դϴ�.
	 */
	static wchar_t wcharBuffer_[MAX_STRING_BUFFER_SIZE];
};

}