#pragma once

#include <cstdarg>
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <string>
#include <windows.h>


#if defined(DEBUG) || defined(RELEASE)
/**
 * @brief ���� �ڵ忡 �����ϴ� �޽����� ����ϴ�.
 * 
 * @param errorCode Ȯ���� ���� �ڵ��Դϴ�.
 * 
 * @return ���� �ڵ忡 �����ϴ� �޽����� ��ȯ�մϴ�.
 */
std::string GetErrorCodeMessageA(const uint32_t& errorCode)
{
	static const uint32_t MAX_BUFFER_SIZE = 1024;
	static char buffer[MAX_BUFFER_SIZE];

	uint32_t size = FormatMessageA(
		FORMAT_MESSAGE_FROM_SYSTEM,
		nullptr,
		static_cast<DWORD>(errorCode),
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		buffer,
		MAX_BUFFER_SIZE,
		nullptr
	);

	return std::string(buffer, size);
}


/**
 * @brief ���� �ڵ忡 �����ϴ� �޽����� ����ϴ�.
 * 
 * @param errorCode Ȯ���� ���� �ڵ��Դϴ�.
 *
 * @return ���� �ڵ忡 �����ϴ� �޽����� ��ȯ�մϴ�.
 */
std::wstring GetErrorCodeMessageW(const uint32_t& errorCode)
{
	static const uint32_t MAX_BUFFER_SIZE = 1024;
	static wchar_t buffer[MAX_BUFFER_SIZE];

	uint32_t size = FormatMessageW(
		FORMAT_MESSAGE_FROM_SYSTEM,
		nullptr,
		static_cast<DWORD>(errorCode),
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		buffer,
		MAX_BUFFER_SIZE,
		nullptr
	);

	return std::wstring(buffer, size);
}
#endif


/**
 * @brief Windows API ȣ�Ⱚ�� �˻��մϴ�.
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

#elif defined(RELEASE)

#else // defined(SHIPPING)

#endif