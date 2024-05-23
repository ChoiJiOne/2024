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
	/**
	 * @brief 스켈레톤(뼈대)의 디폴트 생성자입니다.
	 */
	Skeleton() = default;


	/**
	 * @brief 스켈레톤(뼈대)의 복사 생성자입니다.
	 * 
	 * @param instance 복사할 인스턴스입니다.
	 */
	Skeleton(Skeleton&& instance) noexcept
		: restPose_(instance.restPose_)
		, bindPose_(instance.bindPose_)
		, invBindPose_(instance.invBindPose_)
		, jointNames_(instance.jointNames_) {}


	/**
	 * @brief 스켈레톤(뼈대)의 복사 생성자입니다.
	 * 
	 * @param instance 복사할 인스턴스입니다.
	 */
	Skeleton(const Skeleton& instance) noexcept
		: restPose_(instance.restPose_)
		, bindPose_(instance.bindPose_)
		, invBindPose_(instance.invBindPose_)
		, jointNames_(instance.jointNames_) {}


	/**
	 * @brief 스켈레톤(뼈대)의 가상 소멸자입니다.
	 */
	virtual ~Skeleton() {}


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