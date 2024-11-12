#include <windows.h>
#include <dbghelp.h>
#include <pathcch.h>
#include <Shlwapi.h>

#include "Crash/CrashManager.h"
#include "Utils/Utils.h"

static LPTOP_LEVEL_EXCEPTION_FILTER gTopLevelExceptionFilter;
static std::wstring gCrashDumpPath;

CrashManager CrashManager::instance_;

LONG WINAPI DetectApplicationCrash(EXCEPTION_POINTERS* ep)
{
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