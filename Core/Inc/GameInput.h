#pragma once

#include <cstdint>

namespace GameInput
{
/**
 * --------------------------------------
 * | ���� ������ | ���� ������ | �Է� ���� |
 * --------------------------------------
 * |     0      |     0      | NONE     |
 * |     0      |     1      | PRESSED  |
 * |     1      |     0      | RELEASED |
 * |     1      |     1      | HELD     |
 * --------------------------------------
 */
enum class PressState : int32_t
{
	NONE     = 0x00,
	PRESSED  = 0x01,
	RELEASED = 0x02,
	HELD     = 0x03
};





}