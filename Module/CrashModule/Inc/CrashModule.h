#pragma once

#include <functional>
#include <windows.h>


/**
 * @brief ���ø����̼� ũ���ø� ó���ϴ� ����� �����մϴ�.
 */
class CrashModule
{
public:
	/**
	 * @brief ũ���� ����� ���� ����Դϴ�.
	 */
	enum class Errors
	{
		OK            = 0x00, // ���� ����
		FAILED        = 0x01, // �Ϲ����� ����
		ERR_CREATE    = 0x02, // ���� ���� ����
		ERR_WRITE     = 0x03, // ���� ���� ����
		ERR_CLOSE     = 0x04, // ���� �ݱ� ����
		ERR_API       = 0x05, // API ȣ�� ����
		ERR_PREV_INIT = 0x06, // ������ �ʱ�ȭ�� �����߽��ϴ�.
		ERR_NOT_INIT  = 0x07, // �ʱ�ȭ�� ������� �ʾҽ��ϴ�.
	};


	/**
	 * @brief ũ���� ����� �ʱ�ȭ�մϴ�.
	 *
	 * @param callback ũ���� �߻� �� ������ �ݹ� �Լ��Դϴ�.
	 *
	 * @return ũ���� ��� �ʱ�ȭ�� �����ϸ� Errors �������� OK, �׷��� ������ �� ���� ���� ��ȯ�մϴ�.
	 */
	static Errors Init(const std::function<void()>& callback = nullptr);


	/**
	 * @brief ũ���� ����� �ʱ�ȭ�� �����մϴ�.
	 * 
	 * @return ũ���� ��� �ʱ�ȭ ������ �����ϸ� Errors �������� OK, �׷��� ������ �� ���� ���� ��ȯ�մϴ�.
	 */
	static Errors Uninit();


	/**
	 * @brief ũ���� ����� ���� �ֱ� ���� �޽����� ����ϴ�.
	 *
	 * @return ũ���� ����� ���� �������� �߻��� ���� �޽����� ��ȯ�մϴ�.
	 */
	static const char* GetLastErrorMessage();


private:
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
	 * @brief ���� �޽����� �����մϴ�.
	 * 
	 * @note ������ �������� ������ �ƹ� ���۵� �������� �ʽ��ϴ�.
	 */
	static void SetLastErrorMessage();


	/**
	 * @brief ���� �޽����� �����մϴ�.
	 *
	 * @param message ������ �޽����Դϴ�.
	 */
	static void SetLastErrorMessage(const std::string& message);


	/**
	 * @brief ���� �ý��� �ð��� ���ڿ��� ����ϴ�.
	 *
	 * @return ���ڿ��� ������ ���� �ý��� �ð��� ��ȯ�մϴ�.
	 */
	static std::wstring GetCurrentSystemTimeAsString();


	/**
	 * @brief ���ڿ� �ؽ�Ʈ�� ���Ͽ� ���ϴ�.
	 * 
	 * @param path ������ ����Դϴ�.
	 * @param text ���Ͽ� �� �ؽ�Ʈ�Դϴ�.
	 * 
	 * @return ���ڿ� �ؽ�Ʈ�� ���Ͽ� ���� �� �����ߴٸ� Errors �������� OK, �׷��� ������ �� ���� ���� ��ȯ�մϴ�.
	 */
	static Errors WriteTextFile(const std::wstring& path, const std::string& text);


	/**
	 * @brief ���� ������ �����մϴ�.
	 * 
	 * @param path ���� ���� ����Դϴ�.
	 * @param exceptionPtr ���ܿ� ���� ���ؽ�Ʈ �������Դϴ�.
	 * 
	 * @return ���� ���� ������ �����ϸ� Errors �������� OK, �׷��� ������ �� ���� ���� ��ȯ�մϴ�.
	 * 
	 * @see 
	 * - https://learn.microsoft.com/ko-kr/windows/win32/api/winnt/ns-winnt-exception_pointers
	 * - https://learn.microsoft.com/ko-kr/windows/win32/api/minidumpapiset/nf-minidumpapiset-minidumpwritedump
	 */
	static Errors CreateMinidumpFile(const std::wstring& path, EXCEPTION_POINTERS* exceptionPtr);


	/**
	 * @brief ���� ������ ��θ� ����ϴ�.
	 * 
	 * @param outDumpFilePath ���� ������ ����Դϴ�.
	 * 
	 * @return ���� ������ ��θ� ��� �� �����ϸ� Errors �������� OK, �׷��� ������ �� ���� ���� ��ȯ�մϴ�.
	 */
	static Errors GetDumpFilePath(std::wstring& outDumpFilePath);


	/**
	 * @brief ���ø����̼��� ũ���ø� �����մϴ�.
	 * 
	 * @param exceptionPtr ���ܿ� ���� ���ؽ�Ʈ �������Դϴ�.
	 * 
	 * @return ��������� EXCEPTION_EXECUTE_HANDLER ���� ��ȯ�մϴ�.
	 */
	static LONG WINAPI DetectApplicationCrash(EXCEPTION_POINTERS* exceptionPtr);


private:
	/**
	 * @brief ���ڿ� ������ �ִ� ũ���Դϴ�.
	 */
	static const uint32_t MAX_BUFFER_SIZE = 1024;


	/**
	 * @brief ũ���� ����� �ʱ�ȭ�Ǿ����� Ȯ���մϴ�.
	 */
	static bool bIsInitialize;


	/**
	 * @brief ���� ������ ���� �޽����� �����ϴ� �����Դϴ�.
	 */
	static char lastErrorMessage[MAX_BUFFER_SIZE];


	/**
	 * @brief ���� ���� ���� ����Դϴ�.
	 */
	static wchar_t dumpPath[MAX_BUFFER_SIZE];


	/**
	 * @brief �ʱ�ȭ ������ �ֻ��� ���� ó�� �����Դϴ�.
	 */
	static LPTOP_LEVEL_EXCEPTION_FILTER topLevelExceptionFilter;


	/**
	 * @brief ũ���� �߻� �� ������ �ݹ� �Լ��Դϴ�.
	 * 
	 * @note �ʱ�ȭ �� ����ؾ� ����� �� �ֽ��ϴ�.
	 */
	static std::function<void()> crashCallback;
};