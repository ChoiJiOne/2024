#pragma once

#include <cstdint>


/**
 * @brief 키프레임 데이터입니다.
 * 
 * @see https://gabormakesgames.com/blog_animation_frames.html
 */
template <uint32_t N>
struct Frame
{
	float value[N];
	float in[N];
	float out[N];
	float time;
};


using ScalarFrame = Frame<1>;
using VectorFrame = Frame<3>;
using QuaternionFrame = Frame<4>;