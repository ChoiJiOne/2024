#pragma once

#include <string>
#include <windows.h>


/**
 * @brief Windows ũ���ÿ� ���� Ȯ�� ����� �����մϴ�.
 */
namespace WindowsCrashUtils
{
	/**
	 * @brief �ֻ��� ���� ó���⸦ ����մϴ�.
	 *
	 * @see https://learn.microsoft.com/ko-kr/windows/win32/api/errhandlingapi/nf-errhandlingapi-setunhandledexceptionfilter
	 */
	void RegisterWindowsExceptionFilter();


	/**
	 * @brief �ֻ��� ���� ó���� ����� �����մϴ�.
	 */
	void UnregisterWindowsExceptionFilter();
};