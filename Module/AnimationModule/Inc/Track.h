#pragma once

#include <vector>

#include "Quat.h"

#include "Frame.h"
#include "Interpolation.h"


/**
 * @brief 키 프레임 목록과 보간 정보를 포함한 트랙입니다.
 * 
 * @see https://gabormakesgames.com/blog_animation_tracks.html
 */
template <typename T, uint32_t N>
class Track
{
public:


private:



private:
	/**
	 * @brief 트랙 내의 키 프레임 목록입니다.
	 */
	std::vector<Frame<N>> frames_;


	/**
	 * @brief 키 프레임 보간 방법입니다.
	 */
	EInterpolation interpolation_ = EInterpolation::LINEAR;
};


using ScalarTrack = Track<float, 1>;
using VectorTrack = Track<Vec3f, 3>;
using QuaternionTrack = Track<Quat, 4>;