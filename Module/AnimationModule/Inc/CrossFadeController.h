#pragma once

#include <vector>

#include "CrossFadeTarget.h"
#include "Skeleton.h"


/**
 * @brief 포즈를 블랜딩하는 크로스 페이드 컨트롤러입니다.
 */
class CrossFadeController
{
public:
	/**
	 * @brief 크로스 페이드 컨트롤러의 디폴트 생성자입니다
	 */
	CrossFadeController() = default;


	/**
	 * @brief 크로스 페이드 컨트롤러의 뼈대입니다.
	 * 
	 * @param skeleton 스켈레톤(뼈대)입니다.
	 */
	CrossFadeController(const Skeleton& skeleton);


	/**
	 * @brief 크로스 페이드 컨트롤러의 복사 생성자입니다.
	 * 
	 * @param instance 복사할 인스턴스입니다.
	 */
	CrossFadeController(CrossFadeController&& instance) noexcept
		: targets_(instance.targets_)
		, clip_(instance.clip_)
		, time_(instance.time_)
		, pose_(instance.pose_)
		, skeleton_(instance.skeleton_)
		, bWasSetSkeleton_(instance.bWasSetSkeleton_) {}


	/**
	 * @brief 크로스 페이드 컨트롤러의 복사 생성자입니다.
	 *
	 * @param instance 복사할 인스턴스입니다.
	 */
	CrossFadeController(const CrossFadeController& instance) noexcept
		: targets_(instance.targets_)
		, clip_(instance.clip_)
		, time_(instance.time_)
		, pose_(instance.pose_)
		, skeleton_(instance.skeleton_)
		, bWasSetSkeleton_(instance.bWasSetSkeleton_) {}


	/**
	 * @brief 크로스 페이드 컨트롤러의 가상 소멸자입니다.
	 */
	virtual ~CrossFadeController() {}


	/**
	 * @brief 크로스 페이드 컨트롤러의 뼈대를 설정합니다.
	 * 
	 * @param skeleton 설정할 스켈레톤(뼈대)입니다.
	 */
	void SetSkeleton(const Skeleton& skeleton);


private:
	/**
	 * @brief 크로스 페이드 타겟 목록입니다.
	 */
	std::vector<CrossFadeTarget> targets_;


	/**
	 * @brief 크로스 페이드의 클립입니다.
	 */
	Clip* clip_ = nullptr;


	/**
	 * @brief 누적 시간 값입니다.
	 */
	float time_ = 0.0f;


	/**
	 * @brief 크로스 페이드 포즈입니다.
	 */
	Pose pose_;


	/**
	 * @brief 크로스 페이드 스켈레톤(뼈대)입니다.
	 */
	Skeleton skeleton_;


	/**
	 * @brief 스켈레톤이 업데이트되었는지 확인합니다.
	 */
	bool bWasSetSkeleton_ = false;
};