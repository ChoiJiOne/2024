#include <cstdarg>
#include <cstdint>
#include <cstdio>
#include <cstring>

#include <windows.h>

#include "Utils/Utils.h"

static const int32_t MAX_BUFFER_SIZE = 1024;

void DebugPrintF(const char* format, ...)
{
#if defined(DEBUG_MODE) || defined(RELWITHDEBINFO_MODE)
	char buffer[MAX_BUFFER_SIZE];

	va_list args;
	va_start(args, format);
	int32_t size = _vsnprintf_s(buffer, MAX_BUFFER_SIZE, MAX_BUFFER_SIZE, format, args);
	va_end(args);

	OutputDebugStringA(buffer);
#endif
}

std::string PrintF(const char* format, ...)
{
	char buffer[MAX_BUFFER_SIZE];

	va_list args;
	va_start(args, format);
	int32_t size = vsnprintf(buffer, MAX_BUFFER_SIZE, format, args);
	va_end(args);

	return std::string(buffer, size);
}

std::wstring PrintF(const wchar_t* format, ...)
{
	wchar_t buffer[MAX_BUFFER_SIZE];

	va_list args;
	va_start(args, format);
	int32_t size = _vsnwprintf_s(buffer, MAX_BUFFER_SIZE, format, args);
	va_end(args);

	return std::wstring(buffer, size);
}

#if defined(WIN32) || defined(WIN64)
const char* GetWindowsErrMessage()
{
	static const uint32_t MAX_BUFFER_SIZE = 1024;
	static char buffer[MAX_BUFFER_SIZE];

	uint32_t size = ::FormatMessageA(FORMAT_MESSAGE_FROM_SYSTEM, nullptr, GetLastError(), MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), buffer, MAX_BUFFER_SIZE, nullptr);
	return buffer;
}
#endif

bool ReadFile(const std::string& path, std::vector<uint8_t>& outBuffer, std::string& outErrMsg)
{
	HANDLE file = ::CreateFileA(path.c_str(), GENERIC_READ, FILE_SHARE_READ, nullptr, OPEN_EXISTING, 0, nullptr);
	if (file == INVALID_HANDLE_VALUE)
	{
		outErrMsg = GetWindowsErrMessage();
		return false;
	}

	DWORD fileSize = ::GetFileSize(file, nullptr);
	outBuffer.resize(fileSize);

	DWORD bytesRead;
	if (!::ReadFile(file, outBuffer.data(), fileSize, &bytesRead, nullptr))
	{
		outErrMsg = GetWindowsErrMessage();
		::CloseHandle(file);
		return false;
	}

	if (!::CloseHandle(file))
	{
		outErrMsg = GetWindowsErrMessage();
		return false;
	}
	
	return true;
}

bool ReadFile(const std::wstring& path, std::vector<uint8_t>& outBuffer, std::string& outErrMsg)
{
	HANDLE file = ::CreateFileW(path.c_str(), GENERIC_READ, FILE_SHARE_READ, nullptr, OPEN_EXISTING, 0, nullptr);
	if (file == INVALID_HANDLE_VALUE)
	{
		outErrMsg = GetWindowsErrMessage();
		return false;
	}

	DWORD fileSize = ::GetFileSize(file, nullptr);
	outBuffer.resize(fileSize);

	DWORD bytesRead;
	if (!::ReadFile(file, outBuffer.data(), fileSize, &bytesRead, nullptr))
	{
		outErrMsg = GetWindowsErrMessage();
		::CloseHandle(file);
		return false;
	}

	if (!::CloseHandle(file))
	{
		outErrMsg = GetWindowsErrMessage();
		return false;
	}

	return true;
}