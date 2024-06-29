#pragma once

#include <array>
#include <functional>

#include "GameMath.h"


namespace GameMaker
{
/**
 * @brief �Է� ���¸� ��Ÿ���ϴ�.
 *
 * @note �����ӿ� ���� �Է� �����Դϴ�.
 * --------------------------------------
 * | ���� ������ | ���� ������ | �Է� ���� |
 * --------------------------------------
 * |     0      |     0      | NONE     |
 * |     0      |     1      | PRESSED  |
 * |     1      |     0      | RELEASED |
 * |     1      |     1      | HELD     |
 * --------------------------------------
 */
enum class EPressState : int32_t
{
	NONE     = 0x00,
	PRESSED  = 0x01,
	RELEASED = 0x02,
	HELD     = 0x03
};


/**
 * @brief ���콺�� ��ư�� �����Դϴ�.
 */
enum class EMouse : int32_t
{
	LEFT   = (1 << ((1) - 1)),
	MIDDLE = (1 << ((2) - 1)),
	RIGHT  = (1 << ((3) - 1)),
};



};