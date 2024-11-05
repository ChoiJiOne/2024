#pragma once

#include <string>
#include <vector>

/**
 * DEBUG 창에 포멧팅된 문자열을 출력합니다.
 * 이때, 이 기능은 DEBUG_MODE와 RELWITHDEBINFO_MODE 때만 동작합니다.
 */
void DebugPrintF(const char* format, ...);

/** 표준 문자열 기반의 문자열 포멧팅을 수행합니다. */
std::string PrintF(const char* format, ...);

/** 표준 문자열 기반의 문자열 포멧팅을 수행합니다. */
std::wstring PrintF(const wchar_t* format, ...);

/** 파일을 읽어 벡터에 저장합니다. */
bool ReadFile(const std::string& path, std::vector<uint8_t>& outBuffer, std::string& outErrMsg);

/** 파일을 읽어 벡터에 저장합니다. */
bool ReadFile(const std::wstring& path, std::vector<uint8_t>& outBuffer, std::string& outErrMsg);