#include "WindowsCrashUtils.h"

#include <dbghelp.h>
#include <pathcch.h>
#include <Shlwapi.h>

#include "Assertion.h"
#include "GameTimer.h"
#include "StringUtils.h"

std::wstring crashInfoSavePath;

LPTOP_LEVEL_EXCEPTION_FILTER topLevelExceptionFilter;

/**
 * @brief ũ���� ���� ������ �����մϴ�.
 *
 * @param path ũ���� ���� ������ ����Դϴ�.
 * @param exceptionPtr ���ܿ� ���ؽ�Ʈ ���ڵ��Դϴ�.
 *
 * @return ���� ���� ������ �����ߴٸ� true, �׷��� �ʴٸ� false�� ��ȯ�մϴ�.
 */
bool CreateMinidumpFile(const std::wstring& path, EXCEPTION_POINTERS* exceptionPtr)
{
	HANDLE fileHandle = CreateFileW(path.c_str(), GENERIC_WRITE, FILE_SHARE_WRITE, nullptr, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);
	if (fileHandle == INVALID_HANDLE_VALUE)
	{
		return false;
	}

	_MINIDUMP_EXCEPTION_INFORMATION exception;
	exception.ThreadId = GetCurrentThreadId();
	exception.ExceptionPointers = exceptionPtr;
	exception.ClientPointers = FALSE;

	bool bIsSuccessed = MiniDumpWriteDump(GetCurrentProcess(), GetCurrentProcessId(), fileHandle, MiniDumpWithFullMemory, &exception, nullptr, nullptr);

	if (!CloseHandle(fileHandle))
	{
		bIsSuccessed = false;
	}

	return bIsSuccessed;
}

/**
 * @brief ũ���ø� �����ϰ� ���� ó���� �����մϴ�.
 *
 * @param exceptionPtr ���ܿ� ���ؽ�Ʈ ���ڵ��Դϴ�.
 *
 * @return EXCEPTION_EXECUTE_HANDLER ���� ��ȯ�մϴ�.
 */
LONG WINAPI DetectApplicationCrash(EXCEPTION_POINTERS* exceptionPtr)
{
	std::wstring systemTime = GameTimer::GetCurrentSystemTime();
	std::wstring minidumpPath = StringUtils::PrintF(L"%sWindows-%s-Minidump.dmp", crashInfoSavePath.c_str(), systemTime.c_str());

	CreateMinidumpFile(minidumpPath, exceptionPtr);

	return EXCEPTION_EXECUTE_HANDLER;
}

void WindowsCrashUtils::RegisterWindowsExceptionFilter()
{
	topLevelExceptionFilter = SetUnhandledExceptionFilter(DetectApplicationCrash);

	wchar_t* bufferPtr = StringUtils::GetWideCharBufferPtr();
	WINDOWS_ASSERT(GetModuleFileNameW(nullptr, bufferPtr, StringUtils::STRING_BUFFER_SIZE), "failed to get execute file name...");
	ASSERT(SUCCEEDED(PathCchRemoveFileSpec(bufferPtr, StringUtils::STRING_BUFFER_SIZE)), "failed to remove execute file name...");

	crashInfoSavePath = StringUtils::PrintF(L"%s\\Crash\\", bufferPtr);
	if (!PathFileExistsW(crashInfoSavePath.c_str()))
	{
		WINDOWS_ASSERT(CreateDirectoryW(crashInfoSavePath.c_str(), nullptr), "failed to create %s directory...", crashInfoSavePath.c_str());
	}
}

void WindowsCrashUtils::UnregisterWindowsExceptionFilter()
{
	SetUnhandledExceptionFilter(topLevelExceptionFilter);
}