#pragma once

#if defined(DEBUG_MODE) || defined(RELEASE_MODE) || defined(RELWITHDEBINFO_MODE)
#define _CRTDBG_MAP_ALLOC
#include <cstdlib>
#include <crtdbg.h>
#endif

#include <functional>
#include <string>
#include <windows.h>


namespace GameMaker
{
/**
 * @brief ���α׷��� ũ���� ���� ó���� �����մϴ�.
 */
class CrashUtils
{
public:
};

}