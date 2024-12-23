#include <cstdarg>
#include <cstdint>
#include <cstdio>
#include <cstring>

#include <windows.h>
#include <Shlwapi.h>

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

std::wstring ConvertString(const std::string& text)
{
	static wchar_t buffer[MAX_BUFFER_SIZE];
	std::size_t size = std::mbstowcs(buffer, text.c_str(), MAX_BUFFER_SIZE);
	return std::wstring(buffer, size);
}

std::string ConvertString(const std::wstring& text)
{
	static char buffer[MAX_BUFFER_SIZE];
	std::size_t size = std::wcstombs(buffer, text.c_str(), MAX_BUFFER_SIZE);
	return std::string(buffer, size);
}

#if defined(WIN32) || defined(WIN64)
const char* GetWindowsErrMessage()
{
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

bool WriteFile(const std::string& path, const std::vector<uint8_t>& buffer, std::string& outErrMsg)
{
	HANDLE file = ::CreateFileA(path.c_str(), GENERIC_WRITE, 0, nullptr, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);
	if (file == INVALID_HANDLE_VALUE)
	{
		outErrMsg = GetWindowsErrMessage();
		return false;
	}
	
	DWORD writeByteSize = 0;
	if (!::WriteFile(file, buffer.data(), static_cast<DWORD>(buffer.size()), &writeByteSize, nullptr))
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

bool WriteFile(const std::wstring& path, const std::vector<uint8_t>& buffer, std::string& outErrMsg)
{
	HANDLE file = ::CreateFileW(path.c_str(), GENERIC_WRITE, 0, nullptr, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);
	if (file == INVALID_HANDLE_VALUE)
	{
		outErrMsg = GetWindowsErrMessage();
		return false;
	}

	DWORD writeByteSize = 0;
	if (!::WriteFile(file, buffer.data(), static_cast<DWORD>(buffer.size()), &writeByteSize, nullptr))
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

void GetCurrentSystemTime(int32_t& outYear, int32_t& outMonth, int32_t& outDay, int32_t& outHour, int32_t& outMinute, int32_t& outSecond)
{
	SYSTEMTIME systemTime;
	GetLocalTime(&systemTime);

	outYear = static_cast<int32_t>(systemTime.wYear);
	outMonth = static_cast<int32_t>(systemTime.wMonth);
	outDay = static_cast<int32_t>(systemTime.wDay);
	outHour = static_cast<int32_t>(systemTime.wHour);
	outMinute = static_cast<int32_t>(systemTime.wMinute);
	outSecond = static_cast<int32_t>(systemTime.wSecond);
}

std::string GetCurrentSystemTimeAsString()
{
	int32_t year = 0;
	int32_t month = 0;
	int32_t day = 0;
	int32_t hour = 0;
	int32_t minute = 0;
	int32_t second = 0;
	GetCurrentSystemTime(year, month, day, hour, minute, second);

	return PrintF("%4d-%02d-%02d-%02d-%02d-%02d", year, month, day, hour, minute, second);
}

std::wstring GetCurrentSystemTimeAsWString()
{
	int32_t year = 0;
	int32_t month = 0;
	int32_t day = 0;
	int32_t hour = 0;
	int32_t minute = 0;
	int32_t second = 0;
	GetCurrentSystemTime(year, month, day, hour, minute, second);

	return PrintF(L"%4d-%02d-%02d-%02d-%02d-%02d", year, month, day, hour, minute, second);
}

bool MakeDirectory(const std::string& path, std::string& outErrMsg)
{
	bool bSucceed = CreateDirectoryA(path.c_str(), nullptr);
	if (!bSucceed)
	{
		outErrMsg = GetWindowsErrMessage();
	}

	return bSucceed;
}

bool MakeDirectory(const std::wstring& path, std::string& outErrMsg)
{
	bool bSucceed = CreateDirectoryW(path.c_str(), nullptr);
	if (!bSucceed)
	{
		outErrMsg = GetWindowsErrMessage();
	}

	return bSucceed;
}

bool IsValidPath(const std::string& path)
{
	return PathFileExistsA(path.c_str());
}

bool IsValidPath(const std::wstring& path)
{
	return PathFileExistsW(path.c_str());
}

std::string GetBasePath(const std::string& path)
{
	std::size_t lastSlash;

	if ((lastSlash = path.rfind('/')) != std::string::npos)
	{
		return path.substr(0, lastSlash + 1);
	}
	else if ((lastSlash = path.rfind('\\')) != std::string::npos)
	{
		return path.substr(0, lastSlash + 1);
	}
	else
	{
		return "";
	}
}

std::wstring GetBasePath(const std::wstring& path)
{
	std::size_t lastSlash;

	if ((lastSlash = path.rfind(L'/')) != std::wstring::npos)
	{
		return path.substr(0, lastSlash + 1);
	}
	else if ((lastSlash = path.rfind(L'\\')) != std::wstring::npos)
	{
		return path.substr(0, lastSlash + 1);
	}
	else
	{
		return L"";
	}
}

std::string RemoveBasePath(const std::string& path)
{
	std::size_t lastSlash;

	if ((lastSlash = path.rfind('/')) != std::string::npos)
	{
		return path.substr(lastSlash + 1, std::string::npos);
	}
	else if ((lastSlash = path.rfind('\\')) != std::string::npos)
	{
		return path.substr(lastSlash + 1, std::string::npos);
	}
	else
	{
		return path;
	}
}

std::wstring RemoveBasePath(const std::wstring& path)
{
	std::size_t lastSlash;

	if ((lastSlash = path.rfind(L'/')) != std::wstring::npos)
	{
		return path.substr(lastSlash + 1, std::wstring::npos);
	}
	else if ((lastSlash = path.rfind(L'\\')) != std::wstring::npos)
	{
		return path.substr(lastSlash + 1, std::wstring::npos);
	}
	else
	{
		return path;
	}
}

std::string GetFileExtension(const std::string& path)
{
	std::string filename = RemoveBasePath(path);
	std::size_t offset = filename.rfind('.');

	return (offset == std::string::npos) ? "" : filename.substr(offset + 1);
}

std::wstring GetFileExtension(const std::wstring& path)
{
	std::wstring filename = RemoveBasePath(path);
	std::size_t offset = filename.rfind('.');

	return (offset == std::wstring::npos) ? L"" : filename.substr(offset + 1);
}