#pragma once

#include <cstdarg>
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <windows.h>


#if defined(DEBUG) || defined(RELEASE)


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