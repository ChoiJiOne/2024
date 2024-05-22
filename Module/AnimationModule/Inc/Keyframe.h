#pragma once

#include <cstdint>


/**
 * @brief �ִϸ��̼� Ʈ���� �� ����� Ű �������Դϴ�.
 */
template <uint32_t N>
struct Keyframe
{
	float value[N];
	float in[N];
	float out[N];
	float time;
};

using ScalarFrame = Keyframe<1>;
using VectorFrame = Keyframe<3>;
using QuaternionFrame = Keyframe<4>;