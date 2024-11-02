#pragma once

#include "GL/GLManager.h"
#include "Utils.h"

#if defined(DEBUG_MODE) || defined(RELWITHDEBINFO_MODE)
/**
 * �� ��ũ�δ� OpenGL API�� ȣ�� ��� �򰡽��� �˻��ϰ�, �򰡽��� �������� ������ break�� �̴ϴ�.
 * ex)
 * uint32_t shaderID = glCreateShader(...);
 * GL_EXP_CHECK(shaderID != 0);
 */
#ifndef GL_EXP_CHECK 
#define GL_EXP_CHECK(EXP)\
{\
	if (!(bool)(EXP))\
	{\
		GLenum _errorCode = glGetError();\
		DebugPrintF("\nAssertion check point failed!\n> File: %s\n> Line: %d\n> Function: %s\n> Expression: %s\n", __FILE__, __LINE__, __FUNCTION__, #EXP);\
		DebugPrintF("> Code: %d\n> Error: %s\n\n", static_cast<int32_t>(_errorCode), GLManager::GetRef().GetErrorMessage(_errorCode));\
		__debugbreak();\
	}\
}
#endif
/**
 * �� ��ũ�δ� OpenGL API�� API ȣ�� ����� �˻��ϰ�, �򰡽��� �������� ������ break�� �̴ϴ�.
 * �ַ�, ��ȯ ���� ���� API�� ������� �մϴ�.
 * ex)
 * GL_API_CHECK(glBindBuffer(...));
 */
#ifndef GL_API_CHECK
#define GL_API_CHECK(EXP)\
{\
	EXP;\
	GLenum _errorCode = glGetError();\
	if (_errorCode != GL_NO_ERROR)\
	{\
		DebugPrintF("\nAssertion check point failed!\n> File: %s\n> Line: %d\n> Function: %s\n> Expression: %s\n", __FILE__, __LINE__, __FUNCTION__, #EXP);\
		DebugPrintF("> Code: %d\n> Error: %s\n\n", static_cast<int32_t>(_errorCode), GLManager::GetRef().GetErrorMessage(_errorCode));\
		__debugbreak();\
	}\
}
#endif
/**
 * �� ��ũ�δ� OpenGL API ȣ�� ��� �򰡽��� �˻��ϰ�, �򰡽��� �������� ������ break�� �̴ϴ�.
 * ex)
 * uint32_t shaderID = glCreateShader(...);
 * GL_EXP_ASSERT(shaderID != 0, "Failed to create shader");
 */
#ifndef GL_EXP_ASSERT
#define GL_EXP_ASSERT(EXP, ...)\
{\
	if (!(bool)(EXP))\
	{\
		GLenum _errorCode = glGetError(); \
		DebugPrintF("\nAssertion check point failed!\n> File: %s\n> Line: %d\n> Function: %s\n> Expression: %s\n", __FILE__, __LINE__, __FUNCTION__, #EXP); \
		DebugPrintF("> Code: %d\n> Error: %s\n> Description:", static_cast<int32_t>(_errorCode), GLManager::GetRef().GetErrorMessage(_errorCode)); \
		DebugPrintF(__VA_ARGS__);\
		DebugPrintF("\n\n");\
		__debugbreak(); \
	}\
}
#endif
/**
 * �� ��ũ�δ� OpenGL API�� API ȣ�� ����� �˻��ϰ�, �򰡽��� �������� ������ break�� �̴ϴ�.
 * �ַ�, ��ȯ ���� ���� API�� ������� �մϴ�.
 * ex)
 * GL_API_ASSERT(glBindBuffer(...), "Failed to bind buffer");
 */
#ifndef GL_API_ASSERT
#define GL_API_ASSERT(EXP, ...)\
{\
	EXP;\
	GLenum _errorCode = glGetError();\
	if (_errorCode != GL_NO_ERROR)\
	{\
		DebugPrintF("\nAssertion check point failed!\n> File: %s\n> Line: %d\n> Function: %s\n> Expression: %s\n", __FILE__, __LINE__, __FUNCTION__, #EXP); \
		DebugPrintF("> Code: %d\n> Error: %s\n> Description:", static_cast<int32_t>(_errorCode), GLManager::GetRef().GetErrorMessage(_errorCode)); \
		DebugPrintF(__VA_ARGS__);\
		DebugPrintF("\n\n");\
		__debugbreak();\
	}\
}
#endif
#else // defined(RELEASE_MODE) || defined(MINSIZEREL_MODE)
/**
 * �� ��ũ�δ� OpenGL API�� ȣ�� ��� �򰡽��� �˻��ϰ�, �򰡽��� �������� ������ break�� �̴ϴ�.
 * ex)
 * uint32_t shaderID = glCreateShader(...);
 * GL_EXP_CHECK(shaderID != 0);
 */
#ifndef GL_EXP_CHECK 
#define GL_EXP_CHECK(EXP)\
{\
	if (!(bool)(EXP))\
	{\
		GLenum _errorCode = glGetError();\
		std::string text = PrintF("> Code: %d\n> Error: %s", static_cast<int32_t>(_errorCode), GLManager::GetRef().GetErrorMessage(_errorCode));\
		MessageBox(NULL, text.c_str(), "Assertion check point failed!", MB_OK);\
	}\
}
#endif
/**
 * �� ��ũ�δ� OpenGL API�� API ȣ�� ����� �˻��ϰ�, �򰡽��� �������� ������ break�� �̴ϴ�.
 * �ַ�, ��ȯ ���� ���� API�� ������� �մϴ�.
 * ex)
 * GL_API_CHECK(glBindBuffer(...));
 */
#ifndef GL_API_CHECK
#define GL_API_CHECK(EXP)\
{\
	EXP;\
	GLenum _errorCode = glGetError();\
	if (_errorCode != GL_NO_ERROR)\
	{\
		std::string text = PrintF("> Code: %d\n> Error: %s", static_cast<int32_t>(_errorCode), GLManager::GetRef().GetErrorMessage(_errorCode));\
		MessageBox(NULL, text.c_str(), "Assertion check point failed!", MB_OK);\
	}\
}
#endif
/**
 * �� ��ũ�δ� OpenGL API ȣ�� ��� �򰡽��� �˻��ϰ�, �򰡽��� �������� ������ break�� �̴ϴ�.
 * ex)
 * uint32_t shaderID = glCreateShader(...);
 * GL_EXP_ASSERT(shaderID != 0, "Failed to create shader");
 */
#ifndef GL_EXP_ASSERT
#define GL_EXP_ASSERT(EXP, ...)\
{\
	if (!(bool)(EXP))\
	{\
		GLenum _errorCode = glGetError(); \
		std::string description = PrintF(__VA_ARGS__);\
		std::string text = PrintF("> Code: %d\n> Error: %s\n> Description: %s", static_cast<int32_t>(_errorCode), GLManager::GetRef().GetErrorMessage(_errorCode), description.c_str());\
		MessageBox(NULL, text.c_str(), "Assertion check point failed!", MB_OK);\
	}\
}
#endif
/**
 * �� ��ũ�δ� OpenGL API�� API ȣ�� ����� �˻��ϰ�, �򰡽��� �������� ������ break�� �̴ϴ�.
 * �ַ�, ��ȯ ���� ���� API�� ������� �մϴ�.
 * ex)
 * GL_API_ASSERT(glBindBuffer(...), "Failed to bind buffer");
 */
#ifndef GL_API_ASSERT
#define GL_API_ASSERT(EXP, ...)\
{\
	EXP;\
	GLenum _errorCode = glGetError();\
	if (_errorCode != GL_NO_ERROR)\
	{\
		std::string description = PrintF(__VA_ARGS__);\
		std::string text = PrintF("> Code: %d\n> Error: %s\n> Description: %s", static_cast<int32_t>(_errorCode), GLManager::GetRef().GetErrorMessage(_errorCode), description.c_str());\
		MessageBox(NULL, text.c_str(), "Assertion check point failed!", MB_OK);\
	}\
}
#endif
#endif