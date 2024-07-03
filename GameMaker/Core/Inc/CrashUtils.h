#pragma once

#if defined(DEBUG_MODE) || defined(RELEASE_MODE) || defined(RELWITHDEBINFO_MODE)
#define _CRTDBG_MAP_ALLOC
#include <cstdlib>
#include <crtdbg.h>
#endif

#include <functional>
#include <string>
#include <windows.h>


namespace GameMaker
{
/**
 * @brief ���α׷��� ũ���� ���� ó���� �����մϴ�.
 */
class CrashUtils
{
public:
	/**
	 * @brief ���ø����̼��� ũ���ø� �����ϰ� ���� ������ �����մϴ�.
	 * 
	 * @param ep ���ܿ� ���� ���ؽ�Ʈ �������Դϴ�.
	 * 
	 * @return ��������� EXCEPTION_EXECUTE_HANDLER ���� ��ȯ�մϴ�.
	 */
	static LONG WINAPI DetectApplicationCrash(EXCEPTION_POINTERS* ep);


public:
	/**
	 * @brief ���� �ý��� �ð��� ���ڿ��� ����ϴ�.
	 *
	 * @return ���ڿ��� ������ ���� �ý��� �ð��� ��ȯ�մϴ�.
	 */
	static std::wstring GetCurrentSystemTimeAsString();


	/**
	 * @brief �̴� ���� ������ ��θ� ����ϴ�.
	 *
	 * @return �̴� ���� ������ ��θ� ��ȯ�մϴ�.
	 */
	static std::wstring GetMinidumpPath();


	/**
	 * @brief ���� ������ �����մϴ�.
	 *
	 * @param path ���� ���� ����Դϴ�.
	 * @param ep ���ܿ� ���� ���ؽ�Ʈ �������Դϴ�.
	 *
	 * @return ���� ���� ������ �����ϸ� true, �׷��� ������ false ���� ��ȯ�մϴ�.
	 *
	 * @see
	 * - https://learn.microsoft.com/ko-kr/windows/win32/api/winnt/ns-winnt-exception_pointers
	 * - https://learn.microsoft.com/ko-kr/windows/win32/api/minidumpapiset/nf-minidumpapiset-minidumpwritedump
	 */
	static bool CreateMinidumpFile(const std::wstring& path, EXCEPTION_POINTERS* ep);
};

}