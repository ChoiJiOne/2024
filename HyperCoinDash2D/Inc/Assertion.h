#pragma once

#include <Windows.h>

#include "Utils.h"

#if defined(DEBUG_MODE) || defined(RELWITHDEBINFO_MODE)
/**
 * 이 매크로는 평가식을 검사하고, 평가식을 만족하지 않으면 break를 겁니다.
 * ex)
 * A* a = new A();
 * CHECK(a != nullptr);
 */
#ifndef CHECK
#define CHECK(EXP)\
{\
	if (!(bool)(EXP))\
	{\
		DebugPrintF("\nAssertion check point failed!\n> File: %s\n> Line: %d\n> Function: %s\n> Expression: %s\n\n", __FILE__, __LINE__, __FUNCTION__, #EXP);\
		__debugbreak();\
	}\
}
#endif
/**
 * 이 매크로는 평가식을 검사하고, 평가식을 만족하지 않으면 break를 겁니다.
 * ex)
 * A* a = new A();
 * ASSERTION(a != nullptr, "Failed to create A object in %s", "example");
 */
#ifndef ASSERTION
#define ASSERTION(EXP, ...)\
{\
	if (!(bool)(EXP))\
	{\
		DebugPrintF("\nAssertion check point failed!\n> File: %s\n> Line: %d\n> Function: %s\n> Expression: %s\n> Description: ", __FILE__, __LINE__, __FUNCTION__, #EXP);\
		DebugPrintF(__VA_ARGS__);\
		DebugPrintF("\n\n");\
		__debugbreak();\
	}\
}
#endif
#else // defined(RELEASE_MODE) || defined(MINSIZEREL_MODE)
/**
 * 이 매크로는 평가식을 검사하고, 평가식을 만족하지 않으면 메시지 박스를 띄웁니다.
 * ex)
 * A* a = new A();
 * CHECK(a != nullptr);
 */
#ifndef CHECK
#define CHECK(EXP)\
{\
	if (!(bool)(EXP))\
	{\
		MessageBox(NULL, "Assertion check point failed!", "Assertion check point failed!", MB_OK);\
	}\
}
#endif
 /**
  * 이 매크로는 평가식을 검사하고, 평가식을 만족하지 않으면 메시지 박스를 띄웁니다.
  * ex)
  * A* a = new A();
  * ASSERTION(a != nullptr, "Failed to create A object in %s", "example");
  */
#ifndef ASSERTION
#define ASSERTION(EXP, ...)\
{\
	if (!(bool)(EXP))\
	{\
		std::string description = PrintF(__VA_ARGS__);\
		std::string text = PrintF("> Description: %s", description.c_str());\
		MessageBox(NULL, text.c_str(), "Assertion check point failed!", MB_OK);\
	}\
}
#endif
#endif