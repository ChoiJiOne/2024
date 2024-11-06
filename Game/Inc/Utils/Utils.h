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