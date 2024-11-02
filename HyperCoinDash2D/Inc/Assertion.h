#pragma once

#include "Utils.h"

#if defined(DEBUG_MODE) || defined(RELWITHDEBINFO_MODE)
/**
 * �� ��ũ�δ� �򰡽��� �˻��ϰ�, �򰡽��� �������� ������ break�� �̴ϴ�.
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
 * �� ��ũ�δ� �򰡽��� �˻��ϰ�, �򰡽��� �������� ������ break�� �̴ϴ�.
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
 * �� ��ũ�δ� �򰡽��� �˻��ϰ�, �򰡽��� �������� ������ �޽��� �ڽ��� ���ϴ�.
 * ex)
 * A* a = new A();
 * CHECK(a != nullptr);
 */
#ifndef CHECK
#define CHECK(EXP)\
{\
	if (!(bool)(EXP))\
	{\
		MessageBox(NULL, "Common assertion check point failed!", "Assertion check point failed!", MB_OK);\
	}\
}
#endif
 /**
  * �� ��ũ�δ� �򰡽��� �˻��ϰ�, �򰡽��� �������� ������ �޽��� �ڽ��� ���ϴ�.
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