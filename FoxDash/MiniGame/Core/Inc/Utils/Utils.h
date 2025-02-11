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

/** 표준 문자열을 변환합니다. */
std::wstring ConvertString(const std::string& text);
std::string ConvertString(const std::wstring& text);

/** 파일을 읽어 벡터에 저장합니다. */
bool ReadFile(const std::string& path, std::vector<uint8_t>& outBuffer, std::string& outErrMsg);

/** 파일을 읽어 벡터에 저장합니다. */
bool ReadFile(const std::wstring& path, std::vector<uint8_t>& outBuffer, std::string& outErrMsg);

/** 벡터에 저장된 버퍼를 파일에 씁니다. */
bool WriteFile(const std::string& path, const std::vector<uint8_t>& buffer, std::string& outErrMsg);

/** 벡터에 저장된 버퍼를 파일에 씁니다. */
bool WriteFile(const std::wstring& path, const std::vector<uint8_t>& buffer, std::string& outErrMsg);

/** 현재 시스템 시간 값을 얻습니다. */
void GetCurrentSystemTime(int32_t& outYear, int32_t& outMonth, int32_t& outDay, int32_t& outHour, int32_t& outMinute, int32_t& outSecond);

/** 현재 시스템 시간을 문자열로 얻습니다. */
std::string GetCurrentSystemTimeAsString();

/** 현재 시스템 시간을 문자열로 얻습니다. */
std::wstring GetCurrentSystemTimeAsWString();

/** 디렉토리를 생성합니다. */
bool MakeDirectory(const std::string& path, std::string& outErrMsg);

/** 디렉토리를 생성합니다. */
bool MakeDirectory(const std::wstring& path, std::string& outErrMsg);

/** 파일이나 폴더 경로가 유효한지 확인합니다.  */
bool IsValidPath(const std::string& path);

/** 파일이나 폴더 경로가 유효한지 확인합니다.  */
bool IsValidPath(const std::wstring& path);

/**
 * 전체 경로에서 베이스 경로를 얻습니다.
 * ex)
 * AA\\BB\\CC\\D.txt => AA\\BB\\CC\\
 */
std::string GetBasePath(const std::string& path);

/**
 * 전체 경로에서 베이스 경로를 얻습니다.
 * ex)
 * AA\\BB\\CC\\D.txt => AA\\BB\\CC\\
 */
std::wstring GetBasePath(const std::wstring& path);

/**
 * 전체 경로에서 베이스 경로를 삭제합니다.
 * ex)
 * AA\\BB\\CC\\D.txt => D.txt
 */
std::string RemoveBasePath(const std::string& path);

/**
 * 전체 경로에서 베이스 경로를 삭제합니다.
 * ex)
 * AA\\BB\\CC\\D.txt => D.txt
 */
std::wstring RemoveBasePath(const std::wstring& path);

/**
 * 전체 경로에서 파일 확장자를 얻습니다.
 * ex)
 * AA\\BB\\CC\\D.txt => txt
 */
std::string GetFileExtension(const std::string& path);

/**
 * 전체 경로에서 파일 확장자를 얻습니다.
 * ex)
 * AA\\BB\\CC\\D.txt => txt
 */
std::wstring GetFileExtension(const std::wstring& path);