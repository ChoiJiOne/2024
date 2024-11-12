#include <windows.h>
#include <dbghelp.h>
#include <pathcch.h>
#include <Shlwapi.h>

#include "Crash/CrashManager.h"
#include "Utils/Utils.h"

static LPTOP_LEVEL_EXCEPTION_FILTER gTopLevelExceptionFilter;
static std::function<void()> gCrashCallbackEvent = nullptr;
static std::wstring gCrashDumpPath;

CrashManager CrashManager::instance_;

LONG WINAPI DetectApplicationCrash(EXCEPTION_POINTERS* ep)
{
	std::wstring currSystemTime = GetCurrentSystemTimeAsWString();
	std::string errMsg;
	if (!IsValidPath(gCrashDumpPath))
	{
		if (!MakeDirectory(gCrashDumpPath, errMsg))
		{
			return EXCEPTION_EXECUTE_HANDLER;
		}
	}

	std::wstring path = PrintF(L"%sWindows-%s-Minidump.dmp", gCrashDumpPath.c_str(), currSystemTime.c_str());
	HANDLE file = ::CreateFileW(path.c_str(), GENERIC_WRITE, FILE_SHARE_WRITE, nullptr, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);

	_MINIDUMP_EXCEPTION_INFORMATION exception;
	exception.ThreadId = ::GetCurrentThreadId();
	exception.ExceptionPointers = ep;
	exception.ClientPointers = FALSE;

	HANDLE process = ::GetCurrentProcess();
	DWORD processID = ::GetCurrentProcessId();
	::MiniDumpWriteDump(process, processID, file, MiniDumpWithFullMemory, &exception, nullptr, nullptr);
	::CloseHandle(file);

	if (gCrashCallbackEvent)
	{
		gCrashCallbackEvent();
	}

	return EXCEPTION_EXECUTE_HANDLER;
}

CrashManager& CrashManager::GetRef()
{
	return instance_;
}

CrashManager* CrashManager::GetPtr()
{
	return &instance_;
}

void CrashManager::SetCrashCallbackEvent(const std::function<void()>& callback)
{
	gCrashCallbackEvent = callback;
}

void CrashManager::ShowMessageBox(const std::string& message)
{
	::MessageBox(NULL, message.c_str(), "DETECT APPLICATION CRASH", MB_OK);
}

void CrashManager::Startup()
{
	static wchar_t exePath[MAX_PATH];
	GetModuleFileNameW(nullptr, exePath, MAX_PATH);

	std::wstring minidumpPath(exePath);
	std::wstring basePath = GetBasePath(minidumpPath);

	gCrashDumpPath = PrintF(L"%s\\Crash\\", basePath.c_str());
	gTopLevelExceptionFilter = ::SetUnhandledExceptionFilter(DetectApplicationCrash);
}

void CrashManager::Shutdown()
{
	::SetUnhandledExceptionFilter(gTopLevelExceptionFilter);
}