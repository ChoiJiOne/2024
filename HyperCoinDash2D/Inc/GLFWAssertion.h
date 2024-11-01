#pragma once

#include "GLFWManager.h"
#include "Utils.h"


#if defined(DEBUG_MODE) || defined(RELWITHDEBINFO_MODE)
#ifndef GLFW_CHECK
#define GLFW_CHECK(EXP)\
{\
	if (!(bool)(EXP))\
	{\
		DebugPrintF("\nAssertion check point failed!\n>File : %s\n>Line : %d\n>Function: %s\n>Expression : %s\n", __FILE__, __LINE__, __FUNCTION__, #EXP);\
		__debugbreak();\
	}\
}
#endif

//#ifndef GLFW_API_CHECK
//#define GLFW_API_CHECK(EXP)
//{
//
//}
//#endif






#else // defined(RELEASE_MODE) || defined(MINSIZEREL_MODE)







#endif