#pragma once

#include <Windows.h>

#include "GLFWManager.h"
#include "Utils.h"

#if defined(DEBUG_MODE) || defined(RELWITHDEBINFO_MODE)
/**
 * �� ��ũ�δ� GLFW API�� ȣ�� ��� �򰡽��� �˻��մϴ�.
 * ex) 
 * GLFWwindow* window = glfwCreateWindow(...);
 * GLFW_EXP_CHECK(window != nullptr);
 */
#ifndef GLFW_EXP_CHECK
#define GLFW_EXP_CHECK(EXP)\
{\
	if (!(bool)(EXP))\
	{\
		DebugPrintF("\nAssertion check point failed!\n> File: %s\n> Line: %d\n> Function: %s\n> Expression: %s\n", __FILE__, __LINE__, __FUNCTION__, #EXP);\
		DebugPrintF("> Code: %d\n> Error: %s\n> Description: %s\n\n", GLFWManager::GetRef().GetErrorCode(),  GLFWManager::GetRef().GetErrorMessage(),  GLFWManager::GetRef().GetErrorDescription());\
		__debugbreak();\
	}\
}
#endif
/**
 * �� ��ũ�δ� GLFW API�� API ȣ�� ����� �˻��մϴ�. �ַ�, ��ȯ ���� ���� API�� ������� �մϴ�.
 * ex)
 * GLFW_API_CHECK(glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, GL_MAJOR_VERSION));
 */
#ifndef GLFW_API_CHECK
#define GLFW_API_CHECK(EXP)\
{\
	EXP;\
	if (GLFWManager::GetRef().IsDetectError())\
	{\
		DebugPrintF("\nAssertion check point failed!\n> File: %s\n> Line: %d\n> Function: %s\n> Expression: %s\n", __FILE__, __LINE__, __FUNCTION__, #EXP);\
		DebugPrintF("> Code: %d\n> Error: %s\n> Description: %s\n\n", GLFWManager::GetRef().GetErrorCode(),  GLFWManager::GetRef().GetErrorMessage(),  GLFWManager::GetRef().GetErrorDescription());\
		__debugbreak();\
	}\
}
#endif
#else // defined(RELEASE_MODE) || defined(MINSIZEREL_MODE)
/**
 * �� ��ũ�δ� GLFW API�� ȣ�� ��� �򰡽��� �˻��մϴ�.
 * ex)
 * GLFWwindow* window = glfwCreateWindow(...);
 * GLFW_EXP_CHECK(window != nullptr);
 */
#ifndef GLFW_EXP_CHECK
#define GLFW_EXP_CHECK(EXP)\
{\
	if (!(bool)(EXP))\
	{\
		std::string message = PrintF("> Code: %d\n> Error: %s\n> Description: %s", GLFWManager::GetRef().GetErrorCode(),  GLFWManager::GetRef().GetErrorMessage(),  GLFWManager::GetRef().GetErrorDescription());\
		MessageBox(NULL, message.c_str(), "Assertion check point failed!", MB_OK);\
	}\
}
#endif
/**
 * �� ��ũ�δ� GLFW API�� API ȣ�� ����� �˻��մϴ�. �ַ�, ��ȯ ���� ���� API�� ������� �մϴ�.
 * ex)
 * GLFW_API_CHECK(glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, GL_MAJOR_VERSION));
 */
#ifndef GLFW_API_CHECK
#define GLFW_API_CHECK(EXP)\
{\
	EXP;\
	if (GLFWManager::GetRef().IsDetectError())\
	{\
		std::string message = PrintF("> Code: %d\n> Error: %s\n> Description: %s", GLFWManager::GetRef().GetErrorCode(),  GLFWManager::GetRef().GetErrorMessage(),  GLFWManager::GetRef().GetErrorDescription());\
		MessageBox(NULL, message.c_str(), "Assertion check point failed!", MB_OK); \
	}\
}
#endif
#endif