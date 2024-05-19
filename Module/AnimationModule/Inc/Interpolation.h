#pragma once

/**
 * @brief 애니메이션 곡선 보간 유형입니다.
 */
enum class EInterpolation
{
	CONSTANT = 0x00, // 상수 곡선입니다.
	LINEAR   = 0x01, // 선형 곡선입니다.
	CUBIC    = 0x02, // 큐빅 곡선입니다.
};