#pragma once

#include <vector>

#include "Quat.h"

#include "Frame.h"
#include "Interpolation.h"


/**
 * @brief Ű ������ ��ϰ� ���� ������ ������ Ʈ���Դϴ�.
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
	 * @brief Ʈ�� ���� Ű ������ ����Դϴ�.
	 */
	std::vector<Frame<N>> frames_;


	/**
	 * @brief Ű ������ ���� ����Դϴ�.
	 */
	EInterpolation interpolation_ = EInterpolation::LINEAR;
};


using ScalarTrack = Track<float, 1>;
using VectorTrack = Track<Vec3f, 3>;
using QuaternionTrack = Track<Quat, 4>;