#include <windows.h>
#include <dbghelp.h>
#include <pathcch.h>
#include <Shlwapi.h>

#include "Crash/CrashManager.h"
#include "Utils/Utils.h"

CrashManager CrashManager::instance_;

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
}

void CrashManager::Shutdown()
{
}
