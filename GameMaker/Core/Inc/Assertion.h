#pragma once

#include <cstdarg>
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <string>

#if defined(_WIN32) || defined(_WIN64)
#include <windows.h>
#endif

#if defined(DEBUG_MODE) || defined(RELEASE_MODE) || defined(RELWITHDEBINFO_MODE)
/**
 * @brief 디버그 창에 형식화된 문자열을 출력합니다.
 *
 * @param format 형식 문자열입니다.
 * @param .. 문자열 내의 형식에 대응하는 가변인자입니다.
 *
 * @note
 * - DEBUG_MODE, RELEASE_MODE, RELWITHDEBINFO_MODE 에서만 디버그 창에 문자열이 출력됩니다.
 * - MINSIZEREL_MODE 모드에서는 디버그 창에 문자열이 출력되지 않습니다.
 */
inline void DebugPrintF(const char* format, ...)
{
	static const int32_t BUFFER_SIZE = 1024;
	static char buffer[BUFFER_SIZE];

	va_list args;
	va_start(args, format);
	int32_t size = _vsnprintf_s(buffer, BUFFER_SIZE, BUFFER_SIZE, format, args);
	va_end(args);

	OutputDebugStringA(buffer);
}


/**
 * @brief 디버그 창에 형식화된 문자열을 출력합니다.
 *
 * @param format 형식 문자열입니다.
 * @param .. 문자열 내의 형식에 대응하는 가변인자입니다.
 *
 * @note
 * - DEBUG_MODE, RELEASE_MODE, RELWITHDEBINFO_MODE 에서만 디버그 창에 문자열이 출력됩니다.
 * - MINSIZEREL_MODE 모드에서는 디버그 창에 문자열이 출력되지 않습니다.
 */
inline void DebugPrintF(const wchar_t* format, ...)
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
 * @brief 평가식을 검사합니다.
 *
 * @param Expression 검사할 호출값입니다.
 * @param ... 평가식을 만족하지 못할 경우 표시할 가변 인자 메시지입니다.
 *
 * @note
 * - 디버거가 존재할 때, DEBUG_MODE에서는 브레이크 포인트가 걸린 후 프로세스가 종료됩니다.
 * - 디버거가 존재할 때, RELEASE_MODE와 RELWITHDEBINFO_MODE에서는 브레이크 포인트가 걸리지만 프로세스는 종료되지 않습니다.
 * - MINSIZEREL_MODE에서는 평가식을 검사하지 않습니다.
 */
#if defined(DEBUG_MODE)
#ifndef ASSERT
#define ASSERT(Expression, ...)\
{\
	if (!(bool)(Expression))                                                                                                                \
	{                                                                                                                                       \
		DebugPrintF("\nAssertion check point failed!\nFile : %s\nLine : %d\nExpression : %s\nMessage : ", __FILE__, __LINE__, #Expression); \
		DebugPrintF(__VA_ARGS__);                                                                                                           \
		DebugPrintF("\n\n");                                                                                                                \
		__debugbreak();                                                                                                                     \
		ExitProcess(-1);                                                                                                                    \
	}                                                                                                                                       \
}
#endif
#elif defined(RELEASE_MODE) || defined(RELWITHDEBINFO_MODE)
#ifndef ASSERT
#define ASSERT(Expression, ...)\
{\
	if (!(bool)(Expression))                                                                                                                \
	{                                                                                                                                       \
		DebugPrintF("\nAssertion check point failed!\nFile : %s\nLine : %d\nExpression : %s\nMessage : ", __FILE__, __LINE__, #Expression); \
		DebugPrintF(__VA_ARGS__);                                                                                                           \
		DebugPrintF("\n\n");                                                                                                                \
		__debugbreak();                                                                                                                     \
	}                                                                                                                                       \
}
#endif
#else // defined(MINSIZEREL_MODE)
#ifndef ASSERT
#define ASSERT(Expression, ...) ((void)(Expression))
#endif
#endif


/**
 * @brief 평가식을 검사합니다.
 *
 * @param Expression 검사할 호출값입니다.
 *
 * @note
 * - 디버거가 존재할 때, DEBUG_MODE에서는 브레이크 포인트가 걸린 후 프로세스가 종료됩니다.
 * - 디버거가 존재할 때, RELEASE_MODE와 RELWITHDEBINFO_MODE에서는 브레이크 포인트가 걸리지만 프로세스는 종료되지 않습니다.
 * - MINSIZEREL_MODE에서는 평가식을 검사하지 않습니다.
 */
#if defined(DEBUG_MODE)
#ifndef CHECK
#define CHECK(Expression)\
{\
	if (!(bool)(Expression))                                                                                              \
	{                                                                                                                     \
		DebugPrintF("\nCheck point failed!\nFile : %s\nLine : %d\nExpression : %s\n\n", __FILE__, __LINE__, #Expression); \
		__debugbreak();                                                                                                   \
		ExitProcess(-1);                                                                                                  \
	}                                                                                                                     \
}
#endif
#elif defined(RELEASE_MODE) || defined(RELWITHDEBINFO_MODE)
#ifndef CHECK
#define CHECK(Expression)\
{\
	if (!(bool)(Expression))                                                                                              \
	{                                                                                                                     \
		DebugPrintF("\nCheck point failed!\nFile : %s\nLine : %d\nExpression : %s\n\n", __FILE__, __LINE__, #Expression); \
		__debugbreak();                                                                                                   \
	}                                                                                                                     \
}
#endif
#else // defined(MINSIZEREL_MODE)
#ifndef CHECK
#define CHECK(Expression, ...) ((void)(Expression))
#endif
#endif


#if defined(SDL_h_)
/**
 * @brief 평가식을 검사합니다.
 *
 * @param Expression 검사할 호출값입니다.
 * @param ... 평가식을 만족하지 못할 경우 표시할 가변 인자 메시지입니다.
 *
 * @note
 * - 디버거가 존재할 때, DEBUG_MODE에서는 브레이크 포인트가 걸린 후 프로세스가 종료됩니다.
 * - 디버거가 존재할 때, RELEASE_MODE와 RELWITHDEBINFO_MODE에서는 브레이크 포인트가 걸리지만 프로세스는 종료되지 않습니다.
 * - MINSIZEREL_MODE에서는 평가식을 검사하지 않습니다.
 * - SDL API은 호출에 성공하면 0을 반환합니다.
 */
#if defined(DEBUG_MODE)
#ifndef SDL_ASSERT
#define SDL_ASSERT(Expression, ...)\
{\
	if ((bool)(Expression))                                                                                                                     \
	{                                                                                                                                           \
		DebugPrintF("\nSDL Assertion check point failed!\nFile : %s\nLine : %d\nExpression : %s\nMessage : ", __FILE__, __LINE__, #Expression); \
		DebugPrintF(__VA_ARGS__);                                                                                                               \
		DebugPrintF("\nSDL error message : %s\n", SDL_GetError());                                                                              \
		DebugPrintF("\n");                                                                                                                      \
		__debugbreak();                                                                                                                         \
		ExitProcess(-1);                                                                                                                        \
	}                                                                                                                                           \
}
#endif
#elif defined(RELEASE_MODE) || defined(RELWITHDEBINFO_MODE)
#ifndef SDL_ASSERT
#define SDL_ASSERT(Expression, ...)\
{\
	if ((bool)(Expression))                                                                                                                     \
	{                                                                                                                                           \
		DebugPrintF("\nSDL Assertion check point failed!\nFile : %s\nLine : %d\nExpression : %s\nMessage : ", __FILE__, __LINE__, #Expression); \
		DebugPrintF(__VA_ARGS__);                                                                                                               \
		DebugPrintF("\nSDL error message : %s\n", SDL_GetError());                                                                              \
		DebugPrintF("\n");                                                                                                                      \
		__debugbreak();                                                                                                                         \
}
#endif
#else // defined(MINSIZEREL_MODE)
#ifndef SDL_ASSERT
#define SDL_ASSERT(Expression, ...) ((void)(Expression))
#endif
#endif


/**
 * @brief SDL API가 호출에 실패했는지 확인합니다.
 *
 * @param Expression 검사할 호출값입니다.
 *
 * @note
 * - 디버거가 존재할 때, DEBUG_MODE에서는 브레이크 포인트가 걸린 후 프로세스가 종료됩니다.
 * - 디버거가 존재할 때, RELEASE_MODE와 RELWITHDEBINFO_MODE에서는 브레이크 포인트가 걸리지만 프로세스는 종료되지 않습니다.
 * - MINSIZEREL_MODE에서는 평가식을 검사하지 않습니다.
 * - SDL API은 호출에 성공하면 0을 반환합니다.
 */
#if defined(DEBUG_MODE)
#ifndef SDL_FAILED
#define SDL_FAILED(Expression)\
{\
	if ((bool)(Expression))                                                                                                   \
	{                                                                                                                         \
		DebugPrintF("\nSDL API call has failed!\nFile : %s\nLine : %d\nExpression : %s\n", __FILE__, __LINE__, #Expression);  \
		DebugPrintF("SDL error message : %s\n", SDL_GetError());                                                              \
		DebugPrintF("\n");                                                                                                    \
		__debugbreak();                                                                                                       \
		ExitProcess(-1);                                                                                                      \
	}                                                                                                                         \
}
#endif
#elif defined(RELEASE_MODE) || defined(RELWITHDEBINFO_MODE)
#ifndef SDL_FAILED
#define SDL_FAILED(Expression)\
{\
	if ((bool)(Expression))                                                                                                   \
	{                                                                                                                         \
		DebugPrintF("\nSDL API call has failed!\nFile : %s\nLine : %d\nExpression : %s\n", __FILE__, __LINE__, #Expression);  \
		DebugPrintF("SDL error message : %s\n", SDL_GetError());                                                              \
		DebugPrintF("\n");                                                                                                    \
		__debugbreak();                                                                                                       \
	}                                                                                                                         \
}
#endif
#else // defined(MINSIZEREL_MODE)
#ifndef SDL_FAILED
#define SDL_FAILED(Expression, ...) ((void)(Expression))
#endif
#endif
#endif


#if defined(_WIN32) || defined(_WIN64)
/**
 * @brief Windows 에러 코드에 대응하는 메시지를 얻습니다.
 * 
 * @param errorCode 에러 메시지를 얻을 에러 코드입니다.
 * 
 * @return 에러 코드에 대응하는 메시지를 반환합니다.
 * 
 * @see https://learn.microsoft.com/ko-kr/windows/win32/api/winbase/nf-winbase-formatmessagea
 */
inline std::string GetWinErrorCodeMessageA(uint32_t errorCode)
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
 * @brief Windows 에러 코드에 대응하는 메시지를 얻습니다.
 *
 * @param errorCode 에러 메시지를 얻을 에러 코드입니다.
 *
 * @return 에러 코드에 대응하는 메시지를 반환합니다.
 */
inline std::wstring GetWinErrorCodeMessageW(uint32_t errorCode)
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


/**
 * @brief 평가식을 검사합니다.
 *
 * @param Expression 검사할 호출값입니다.
 * @param ... 평가식을 만족하지 못할 경우 표시할 가변 인자 메시지입니다.
 *
 * @note
 * - 디버거가 존재할 때, DEBUG_MODE에서는 브레이크 포인트가 걸린 후 프로세스가 종료됩니다.
 * - 디버거가 존재할 때, RELEASE_MODE와 RELWITHDEBINFO_MODE에서는 브레이크 포인트가 걸리지만 프로세스는 종료되지 않습니다.
 * - MINSIZEREL_MODE에서는 평가식을 검사하지 않습니다.
 */
#if defined(DEBUG_MODE)
#ifndef WINDOWS_ASSERT
#define WINDOWS_ASSERT(Expression, ...)\
{\
	if (!(bool)(Expression))                                                                                                                        \
	{                                                                                                                                               \
		DebugPrintF("\nWindows assertion check point failed!\nFile : %s\nLine : %d\nExpression : %s\nMessage : ", __FILE__, __LINE__, #Expression); \
		DebugPrintF(__VA_ARGS__);                                                                                                                   \
		DebugPrintF(L"Windows error message : %s\n", GetWinErrorCodeMessageW(GetLastError()).c_str());                                              \
		DebugPrintF("\n\n");                                                                                                                        \
		__debugbreak();                                                                                                                             \
		ExitProcess(-1);                                                                                                                            \
	}                                                                                                                                               \
}
#endif
#elif defined(RELEASE_MODE) || defined(RELWITHDEBINFO_MODE)
#ifndef WINDOWS_ASSERT
#define WINDOWS_ASSERT(Expression, ...)\
{\
	if (!(bool)(Expression))                                                                                                                        \
	{                                                                                                                                               \
		DebugPrintF("\nWindows assertion check point failed!\nFile : %s\nLine : %d\nExpression : %s\nMessage : ", __FILE__, __LINE__, #Expression); \
		DebugPrintF(__VA_ARGS__);                                                                                                                   \
		DebugPrintF(L"Windows error message : %s\n", GetWinErrorCodeMessageW(GetLastError()).c_str());                                              \
		DebugPrintF("\n\n");                                                                                                                        \
		__debugbreak();                                                                                                                             \
	}                                                                                                                                               \
}
#endif
#else // defined(MINSIZEREL_MODE)
#ifndef WINDOWS_ASSERT
#define WINDOWS_ASSERT(Expression, ...) ((void)(Expression))
#endif
#endif


/**
 * @brief 평가식을 검사합니다.
 *
 * @param Expression 검사할 호출값입니다.
 *
 * @note
 * - 디버거가 존재할 때, DEBUG_MODE에서는 브레이크 포인트가 걸린 후 프로세스가 종료됩니다.
 * - 디버거가 존재할 때, RELEASE_MODE와 RELWITHDEBINFO_MODE에서는 브레이크 포인트가 걸리지만 프로세스는 종료되지 않습니다.
 * - MINSIZEREL_MODE에서는 평가식을 검사하지 않습니다.
 */
#if defined(DEBUG_MODE)
#ifndef WINDOWS_CHECK
#define WINDOWS_CHECK(Expression)\
{\
	if (!(bool)(Expression))                                                                                              \
	{                                                                                                                     \
		DebugPrintF("\nCheck point failed!\nFile : %s\nLine : %d\nExpression : %s\n\n", __FILE__, __LINE__, #Expression); \
		DebugPrintF(L"Windows error message : %s\n", GetWinErrorCodeMessageW(GetLastError()).c_str());                    \
		__debugbreak();                                                                                                   \
		ExitProcess(-1);                                                                                                  \
	}                                                                                                                     \
}
#endif
#elif defined(RELEASE_MODE) || defined(RELWITHDEBINFO_MODE)
#ifndef WINDOWS_CHECK
#define WINDOWS_CHECK(Expression)\
{\
	if (!(bool)(Expression))                                                                                              \
	{                                                                                                                     \
		DebugPrintF("\nCheck point failed!\nFile : %s\nLine : %d\nExpression : %s\n\n", __FILE__, __LINE__, #Expression); \
		DebugPrintF(L"Windows error message : %s\n", GetWinErrorCodeMessageW(GetLastError()).c_str());                    \
		__debugbreak();                                                                                                   \
	}                                                                                                                     \
}
#endif
#else // defined(MINSIZEREL_MODE)
#ifndef WINDOWS_CHECK
#define WINDOWS_CHECK(Expression, ...) ((void)(Expression))
#endif
#endif
#endif


#if defined(__glad_h_)
/**
 * @brief 에러 코드에 대응하는 메시지를 얻습니다.
 *
 * @param errorCode 확인할 에러 코드입니다.
 *
 * @return 에러 코드에 대응하는 메시지를 반환합니다.
 *
 * @note
 * - https://registry.khronos.org/OpenGL-Refpages/gl4/html/glGetError.xhtml
 * - https://www.khronos.org/opengl/wiki/OpenGL_Error
 */
inline std::string GetGLErrorCodeMessageA(const GLenum& errorCode)
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
 * @brief 에러 코드에 대응하는 메시지를 얻습니다.
 *
 * @param errorCode 확인할 에러 코드입니다.
 *
 * @return 에러 코드에 대응하는 메시지를 반환합니다.
 *
 * @note
 * - https://registry.khronos.org/OpenGL-Refpages/gl4/html/glGetError.xhtml
 * - https://www.khronos.org/opengl/wiki/OpenGL_Error
 */
inline std::wstring GetGLErrorCodeMessageW(const GLenum& errorCode)
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
 * @brief OpenGL API 호출값을 검사합니다.
 *
 * @param Expression 검사할 호출값입니다.
 * @param ... 평가식을 만족하지 못할 경우 표시할 가변 인자 메시지입니다.
 *
 * @note
 * - Debug 모드와 Release 모드에서는 평가식을 검사하지만 Shipping 모드에서는 평가식을 검사하지 않습니다.
 * - 디버거가 존재하면 브레이크 포인트가 걸립니다.
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
		DebugPrintF("\nOpenGL error message : %s\n\n", GetGLErrorCodeMessageA(_errorCode).c_str());                                                  \
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
		DebugPrintF("\nOpenGL error message : %s\n\n", GetGLErrorCodeMessageA(_errorCode).c_str());                                                  \
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
  * @brief OpenGL API 호출에 실패했는지 확인합니다.
  *
  * @param Expression 검사할 호출값입니다.
  *
  * @note
  * - Debug 모드와 Release 모드에서는 평가식을 검사하지만 Shipping 모드에서는 평가식을 검사하지 않습니다.
  * - 디버거가 존재하면 브레이크 포인트가 걸립니다.
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
		DebugPrintF("OpenGL error message : %s\n\n", GetGLErrorCodeMessageA(_errorCode).c_str());                                 \
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
		DebugPrintF("OpenGL error message : %s\n\n", GetGLErrorCodeMessageA(_errorCode).c_str());                                 \
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