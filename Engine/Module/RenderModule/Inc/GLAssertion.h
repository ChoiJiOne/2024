#pragma once

#include "Assertion.h"


#if defined(__glad_h_)
  /**
   * @brief ���� �ڵ忡 �����ϴ� �޽����� ����ϴ�.
   *
   * @param errorCode Ȯ���� ���� �ڵ��Դϴ�.
   *
   * @return ���� �ڵ忡 �����ϴ� �޽����� ��ȯ�մϴ�.
   *
   * @note
   * - https://registry.khronos.org/OpenGL-Refpages/gl4/html/glGetError.xhtml
   * - https://www.khronos.org/opengl/wiki/OpenGL_Error
   */
inline std::string GetErrorCodeMessageA(const GLenum& errorCode)
{
	std::string errorMessage;

	switch (errorCode)
	{
	case GL_NO_ERROR:
		errorMessage = "No error has been recorded. (GL_NO_ERROR)";
		break;

	case GL_INVALID_ENUM:
		errorMessage = "An unacceptable value is specified for an enumerated argument. (GL_INVALID_ENUM)";
		break;

	case GL_INVALID_VALUE:
		errorMessage = "A numeric argument is out of range. (GL_INVALID_VALUE)";
		break;

	case GL_INVALID_OPERATION:
		errorMessage = "The specified operation is not allowed in the current state. (GL_INVALID_OPERATION)";
		break;

	case GL_INVALID_FRAMEBUFFER_OPERATION:
		errorMessage = "The framebuffer object is not complete. (GL_INVALID_FRAMEBUFFER_OPERATION)";
		break;

	case GL_OUT_OF_MEMORY:
		errorMessage = "There is not enough memory left to execute the command. (GL_OUT_OF_MEMORY)";
		break;

	case GL_STACK_UNDERFLOW:
		errorMessage = "An attempt has been made to perform an operation that would cause an internal stack to underflow. (GL_STACK_UNDERFLOW)";
		break;

	case GL_STACK_OVERFLOW:
		errorMessage = "An attempt has been made to perform an operation that would cause an internal stack to overflow. (GL_STACK_OVERFLOW)";
		break;

	case GL_CONTEXT_LOST:
		errorMessage = "This occurs when the OpenGL context becomes lost due to a graphics card reset. (GL_CONTEXT_LOST)";
		break;

	default:
		errorMessage = "Undefined error message.";
	}

	return errorMessage;
}


/**
 * @brief ���� �ڵ忡 �����ϴ� �޽����� ����ϴ�.
 *
 * @param errorCode Ȯ���� ���� �ڵ��Դϴ�.
 *
 * @return ���� �ڵ忡 �����ϴ� �޽����� ��ȯ�մϴ�.
 *
 * @note
 * - https://registry.khronos.org/OpenGL-Refpages/gl4/html/glGetError.xhtml
 * - https://www.khronos.org/opengl/wiki/OpenGL_Error
 */
inline std::wstring GetErrorCodeMessageW(const GLenum& errorCode)
{
	std::wstring errorMessage;

	switch (errorCode)
	{
	case GL_NO_ERROR:
		errorMessage = L"No error has been recorded. (GL_NO_ERROR)";
		break;

	case GL_INVALID_ENUM:
		errorMessage = L"An unacceptable value is specified for an enumerated argument. (GL_INVALID_ENUM)";
		break;

	case GL_INVALID_VALUE:
		errorMessage = L"A numeric argument is out of range. (GL_INVALID_VALUE)";
		break;

	case GL_INVALID_OPERATION:
		errorMessage = L"The specified operation is not allowed in the current state. (GL_INVALID_OPERATION)";
		break;

	case GL_INVALID_FRAMEBUFFER_OPERATION:
		errorMessage = L"The framebuffer object is not complete. (GL_INVALID_FRAMEBUFFER_OPERATION)";
		break;

	case GL_OUT_OF_MEMORY:
		errorMessage = L"There is not enough memory left to execute the command. (GL_OUT_OF_MEMORY)";
		break;

	case GL_STACK_UNDERFLOW:
		errorMessage = L"An attempt has been made to perform an operation that would cause an internal stack to underflow. (GL_STACK_UNDERFLOW)";
		break;

	case GL_STACK_OVERFLOW:
		errorMessage = L"An attempt has been made to perform an operation that would cause an internal stack to overflow. (GL_STACK_OVERFLOW)";
		break;

	case GL_CONTEXT_LOST:
		errorMessage = L"This occurs when the OpenGL context becomes lost due to a graphics card reset. (GL_CONTEXT_LOST)";
		break;

	default:
		errorMessage = L"Undefined error message.";
	}

	return errorMessage;
}


/**
 * @brief OpenGL API ȣ�Ⱚ�� �˻��մϴ�.
 *
 * @param Expression �˻��� ȣ�Ⱚ�Դϴ�.
 * @param ... �򰡽��� �������� ���� ��� ǥ���� ���� ���� �޽����Դϴ�.
 *
 * @note
 * - Debug ���� Release ��忡���� �򰡽��� �˻������� Shipping ��忡���� �򰡽��� �˻����� �ʽ��ϴ�.
 * - ����Ű� �����ϸ� �극��ũ ����Ʈ�� �ɸ��ϴ�.
 */
#if defined(DEBUG_MODE)
#ifndef GL_ASSERT
#define GL_ASSERT(Expression, ...)\
Expression;\
{\
	GLenum _errorCode = glGetError();                                                                                                              \
	if (_errorCode != GL_NO_ERROR)                                                                                                                 \
	{                                                                                                                                              \
		DebugPrintF("\nOpenGL assertion check point failed!\nFile : %s\nLine : %d\nExpression : %s\nMessage : ", __FILE__, __LINE__, #Expression); \
		DebugPrintF(__VA_ARGS__);                                                                                                                  \
		DebugPrintF("\nOpenGL error message : %s\n\n", GetErrorCodeMessageA(_errorCode).c_str());                                                  \
		__debugbreak();                                                                                                                            \
		ExitProcess(-1);                                                                                                                           \
	}\
}
#endif
#elif defined(RELEASE_MODE) || defined(DEVELOPMENT_MODE)
#ifndef GL_ASSERT
#define GL_ASSERT(Expression, ...)\
Expression;\
{\
	GLenum _errorCode = glGetError();                                                                                                              \
	if (_errorCode != GL_NO_ERROR)                                                                                                                 \
	{                                                                                                                                              \
		DebugPrintF("\nOpenGL assertion check point failed!\nFile : %s\nLine : %d\nExpression : %s\nMessage : ", __FILE__, __LINE__, #Expression); \
		DebugPrintF(__VA_ARGS__);                                                                                                                  \
		DebugPrintF("\nOpenGL error message : %s\n\n", GetErrorCodeMessageA(_errorCode).c_str());                                                  \
		__debugbreak();                                                                                                                            \
	}\
}
#endif
#else // defined(SHIPPING_MODE)
#ifndef GL_ASSERT
#define GL_ASSERT(Expression, ...)\
Expression;
#endif
#endif


 /**
  * @brief OpenGL API ȣ�⿡ �����ߴ��� Ȯ���մϴ�.
  *
  * @param Expression �˻��� ȣ�Ⱚ�Դϴ�.
  *
  * @note
  * - Debug ���� Release ��忡���� �򰡽��� �˻������� Shipping ��忡���� �򰡽��� �˻����� �ʽ��ϴ�.
  * - ����Ű� �����ϸ� �극��ũ ����Ʈ�� �ɸ��ϴ�.
  */
#if defined(DEBUG_MODE)
#ifndef GL_FAILED
#define GL_FAILED(Expression)\
Expression;\
{\
	GLenum _errorCode = glGetError();                                                                                           \
	if (_errorCode != GL_NO_ERROR)                                                                                              \
	{                                                                                                                           \
		DebugPrintF("\nOpenGL API call has failed!\nFile : %s\nLine : %d\nExpression : %s\n", __FILE__, __LINE__, #Expression); \
		DebugPrintF("OpenGL error message : %s\n\n", GetErrorCodeMessageA(_errorCode).c_str());                                 \
		__debugbreak();                                                                                                         \
		ExitProcess(-1);                                                                                                        \
	}\
}
#endif
#elif defined(RELEASE_MODE) || defined(DEVELOPMENT_MODE)
#ifndef GL_FAILED
#define GL_FAILED(Expression)\
Expression;\
{\
	GLenum _errorCode = glGetError();                                                                                           \
	if (_errorCode != GL_NO_ERROR)                                                                                              \
	{                                                                                                                           \
		DebugPrintF("\nOpenGL API call has failed!\nFile : %s\nLine : %d\nExpression : %s\n", __FILE__, __LINE__, #Expression); \
		DebugPrintF("OpenGL error message : %s\n\n", GetErrorCodeMessageA(_errorCode).c_str());                                 \
		__debugbreak();                                                                                                         \
	}\
}
#endif
#else // defined(SHIPPING_MODE)
#ifndef GL_FAILED
#define GL_FAILED(Expression)\
Expression;
#endif
#endif
#endif