#pragma once

#include <functional>
#include <string>

#include "Macro.h"

/** ũ���� �Ŵ����� �̱��� Ŭ�����Դϴ�. */
class CrashManager
{
public:
	DISALLOW_COPY_AND_ASSIGN(CrashManager);

	static CrashManager& Get();

	void SetCrashCallbackEvent(const std::function<void()>& callback);
	const wchar_t* GetCrashDumpFileNamePtr();
	const std::wstring& GetCrashDumpFileName();

private:
	CrashManager() = default;
	virtual ~CrashManager() {}
};