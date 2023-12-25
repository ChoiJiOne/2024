#pragma once

#include <string>
#include <windows.h>


/**
 * @brief Windows ũ���ÿ� ���� Ȯ�� ����� �����մϴ�.
 * 
 * @note �� Ŭ������ ��� ��� ������ �޼���� ��� static�Դϴ�.
 */
class WindowsCrashUtils
{
public:
	/**
	 * @brief �ֻ��� ���� ó���⸦ ����մϴ�.
	 *
	 * @see https://learn.microsoft.com/ko-kr/windows/win32/api/errhandlingapi/nf-errhandlingapi-setunhandledexceptionfilter
	 */
	static void RegisterExceptionFilter();


	/**
	 * @brief �ֻ��� ���� ó���� ����� �����մϴ�.
	 */
	static void UnregisterExceptionFilter();


	/**
	 * @brief ũ���ø� �����ϰ� ���� ó���� �����մϴ�.
	 * 
	 * @param exceptionPtr ���ܿ� ���ؽ�Ʈ ���ڵ��Դϴ�.
	 * 
	 * @return EXCEPTION_EXECUTE_HANDLER ���� ��ȯ�մϴ�.
	 */
	static LONG WINAPI DetectApplicationCrash(EXCEPTION_POINTERS* exceptionPtr);


private:
	/**
	 * @brief ũ���ð� ������ �ý��� �ð����� ����ϴ�.
	 * 
	 * @return �ý��� �ð����� ��ȯ�մϴ�.
	 */
	static std::wstring GetCrashSystemTime();

	
private:
	/**
	 * @brief ũ���ÿ� ���õ� ���ϵ��� ������ ����Դϴ�.
	 * 
	 * @note ũ���ÿ� ���õ� ������ �̴� ���� ���ϰ� �ݽ��� ��� �����Դϴ�.
	 */
	static std::wstring crashInfoSavePath_;
};