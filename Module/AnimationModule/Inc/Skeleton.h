#pragma once

#include <string>
#include <vector>

#include "Mat.h"

#include "Pose.h"


/**
 * @brief 스켈레톤(뼈대)입니다.
 */
class Skeleton
{
public:


private:
	/**
	 * @brief 뼈대의 Rest 포즈입니다.
	 */
	Pose restPose_;


	/**
	 * @brief 뼈대의 Bind 포즈입니다.
	 */
	Pose bindPose_;


	/**
	 * @brief 역 바인드 포즈 행렬 목록입니다.
	 */
	std::vector<Mat4x4> invBindPose_;


	/**
	 * @brief 관절(Bone) 이름 목록입니다.
	 */
	std::vector<std::string> jointNames_;
};