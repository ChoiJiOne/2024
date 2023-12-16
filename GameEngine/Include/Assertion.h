#pragma once

#include <cstdarg>
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <string>
#include <windows.h>


#if defined(DEBUG) || defined(RELEASE)
/**
 * @brief ����� â�� ����ȭ�� ���ڿ��� ����մϴ�.
 *
 * @param format ���� ���ڿ��Դϴ�.
 * @param .. ���ڿ� ���� ���Ŀ� �����ϴ� ���������Դϴ�.
 *
 * @note
 * - Debug�� Release��忡���� ����� â�� ���ڿ��� ��µ˴ϴ�.
 * - Shipping ��忡���� ����� â�� ���ڿ��� ��µ��� �ʽ��ϴ�.
 */
inline void AssertPrintF(const char* format, ...)
{
	static const int32_t BUFFER_SIZE = 1024;
	static char buffer[BUFFER_SIZE];

	va_list args;
	va_start(args, format);
	int32_t size = vsnprintf(buffer, BUFFER_SIZE, format, args);
	va_end(args);

	OutputDebugStringA(buffer);
}


/**
 * @brief ����� â�� ����ȭ�� ���ڿ��� ����մϴ�.
 *
 * @param format ���� ���ڿ��Դϴ�.
 * @param .. ���ڿ� ���� ���Ŀ� �����ϴ� ���������Դϴ�.
 *
 * @note
 * - Debug�� Release��忡���� ����� â�� ���ڿ��� ��µ˴ϴ�.
 * - Shipping ��忡���� ����� â�� ���ڿ��� ��µ��� �ʽ��ϴ�.
 */
inline void AssertPrintF(const wchar_t* format, ...)
{
	static const int32_t BUFFER_SIZE = 1024;
	static wchar_t buffer[BUFFER_SIZE];

	va_list args;
	va_start(args, format);
	int32_t size = _vsnwprintf_s(buffer, BUFFER_SIZE, format, args);
	va_end(args);

	OutputDebugStringW(buffer);
}
#endif


/**
 * @brief �򰡽��� �˻��մϴ�.
 * 
 * @param Expression �˻��� ȣ�Ⱚ�Դϴ�.
 * @param ... �򰡽��� �������� ���� ��� ǥ���� ���� ���� �޽����Դϴ�.
 *
 * @note
 * - Debug ���� Release ��忡���� �򰡽��� �˻������� Shipping ��忡���� �򰡽��� �˻����� �ʽ��ϴ�.
 * - ����Ű� �����ϸ� �극��ũ ����Ʈ�� �ɸ��ϴ�.
 * - ����Ű� �������� ������ ũ���� ���� ������ �����մϴ�.
 */
#if defined(DEBUG)
#ifndef ASSERT
#define ASSERT(Expression, ...)\
{\
	if(!(bool)(Expression))\
	{\
		AssertPrintF("\nAssertion check point failed!\nFile : %s\nLine : %d\nExpression : %s\nMessage : ", __FILE__, __LINE__, #Expression);\
		AssertPrintF(__VA_ARGS__);\
		AssertPrintF("\n");\
		__debugbreak();\
		ExitProcess(-1);\
	}\
}
#endif
#elif defined(RELEASE)
#ifndef ASSERT
#define ASSERT(Expression, ...)\
{\
	if(!(bool)(Expression))\
	{\
		AssertPrintF("\nAssertion check point failed!\nFile : %s\nLine : %d\nExpression : %s\nMessage : ", __FILE__, __LINE__, #Expression);\
		AssertPrintF(__VA_ARGS__);\
		AssertPrintF("\n");\
		__debugbreak();\
	}\
}
#endif
#else // defined(SHIPPING)
#ifndef ASSERT
#define ASSERT(Expression, ...) ((void)(Expression))
#endif
#endif