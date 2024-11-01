#include <cstdarg>
#include <cstdint>
#include <cstdio>
#include <cstring>

#include <windows.h>

#include "Utils.h"

void DebugPrintF(const char* format, ...)
{
#if defined(DEBUG_MODE) || defined(RELWITHDEBINFO_MODE)
	static const int32_t BUFFER_SIZE = 1024;
	char buffer[BUFFER_SIZE];

	va_list args;
	va_start(args, format);
	int32_t size = _vsnprintf_s(buffer, BUFFER_SIZE, BUFFER_SIZE, format, args);
	va_end(args);

	OutputDebugStringA(buffer);
#endif
}