#pragma once

#include "Clip.h"
#include "Pose.h"


/**
 * @brief 애니메이션 패이딩 시 샘플링된 포즈의 상태 값입니다.
 */
class CrossFadeTarget
{
public:
	/**
	 * @brief 크로스 페이드 타겟의 기본 생성자입니다.
	 */
	CrossFadeTarget() = default;


	/**
	 * @brief 크로스 페이드 타겟의 생성자입니다.
	 * 
	 * @param 크로스 페이드 타겟의 클립입니다.
	 * @param 크로스 페이드 타겟의 포즈입니다.
	 * @param 크로스 페이드 타겟의 애니메이션 지속 시간입니다.
	 */
	CrossFadeTarget(Clip* target, const Pose& pose, float duration)
		: clip_(target)
		, pose_(pose)
		, time_(target->GetStartTime())
		, duration_(duration)
		, elapsed_(0.0f) {}


	/**
	 * @brief 크로스 페이드 타겟의 복사 생성자입니다.
	 * 
	 * @param instance 복사할 인스턴스입니다.
	 */
	CrossFadeTarget(CrossFadeTarget&& instance) noexcept
		: pose_(instance.pose_)
		, clip_(instance.clip_)
		, time_(instance.time_)
		, duration_(instance.duration_)
		, elapsed_(instance.elapsed_) {}


	/**
	 * @brief 크로스 페이드 타겟의 복사 생성자입니다.
	 *
	 * @param instance 복사할 인스턴스입니다.
	 */
	CrossFadeTarget(const CrossFadeTarget& instance) noexcept
		: pose_(instance.pose_)
		, clip_(instance.clip_)
		, time_(instance.time_)
		, duration_(instance.duration_)
		, elapsed_(instance.elapsed_) {}


private:
	/**
	 * @brief 애니메이션 패이딩 시 샘플링할 포즈입니다.
	 */
	Pose pose_;


	/**
	 * @brief 현재의 애니메이션 클립입니다.
	 */
	Clip* clip_ = nullptr;


	/**
	 * @brief 누적 시간값입니다.
	 */
	float time_ = 0.0f;


	/**
	 * @brief 애니메이션 지속 시간입니다.
	 */
	float duration_ = 0.0f;


	/**
	 * @brief 애니메이션 플레이 경과 시간입니다.
	 */
	float elapsed_ = 0.0f;
};