#pragma once

#include <string>
#include <vector>

/**
 * DEBUG â�� �����õ� ���ڿ��� ����մϴ�.
 * �̶�, �� ����� DEBUG_MODE�� RELWITHDEBINFO_MODE ���� �����մϴ�.
 */
void DebugPrintF(const char* format, ...);

/** ǥ�� ���ڿ� ����� ���ڿ� �������� �����մϴ�. */
std::string PrintF(const char* format, ...);

/** ǥ�� ���ڿ� ����� ���ڿ� �������� �����մϴ�. */
std::wstring PrintF(const wchar_t* format, ...);

/** ������ �о� ���Ϳ� �����մϴ�. */
bool ReadFile(const std::string& path, std::vector<uint8_t>& outBuffer, std::string& outErrMsg);

/** ������ �о� ���Ϳ� �����մϴ�. */
bool ReadFile(const std::wstring& path, std::vector<uint8_t>& outBuffer, std::string& outErrMsg);

/** ���Ϳ� ����� ���۸� ���Ͽ� ���ϴ�. */
bool WriteFile(const std::string& path, const std::vector<uint8_t>& buffer, std::string& outErrMsg);

/** ���Ϳ� ����� ���۸� ���Ͽ� ���ϴ�. */
bool WriteFile(const std::wstring& path, const std::vector<uint8_t>& buffer, std::string& outErrMsg);

/** ���� �ý��� �ð� ���� ����ϴ�. */
void GetCurrentSystemTime(int32_t& outYear, int32_t& outMonth, int32_t& outDay, int32_t& outHour, int32_t& outMinute, int32_t& outSecond);

/** ���� �ý��� �ð��� ���ڿ��� ����ϴ�. */
std::string GetCurrentSystemTimeAsString();

/** ���� �ý��� �ð��� ���ڿ��� ����ϴ�. */
static std::wstring GetCurrentSystemTimeAsWString();

/** ���丮�� �����մϴ�. */
bool MakeDirectory(const std::string& path, std::string& outErrMsg);

/** ���丮�� �����մϴ�. */
bool MakeDirectory(const std::wstring& path, std::string& outErrMsg);

/** �����̳� ���� ��ΰ� ��ȿ���� Ȯ���մϴ�.  */
bool IsValidPath(const std::string& path);

/** �����̳� ���� ��ΰ� ��ȿ���� Ȯ���մϴ�.  */
bool IsValidPath(const std::wstring& path);