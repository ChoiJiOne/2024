#pragma once

#include <vector>

#include "Clip.h"
#include "Pose.h"
#include "Skeleton.h"


/**
 * @brief 애니메이션 블랜딩을 위한 크로스 페이드 컨트롤러입니다.
 */
class CrossFadeContoller
{
public:
	/**
	 * @brief 크로스 페이드 컨트롤러의 기본 생성자입니다.
	 */
	explicit CrossFadeContoller() {}


	/**
	 * @brief 크로스 페이드 컨트롤러의 생성자입니다.
	 *
	 * @param skeleton 컨트롤러의 대상이 되는 뼈대입니다.
	 */
	explicit CrossFadeContoller(Skeleton&& skeleton)
		: skeleton_(skeleton)
		, clip_(nullptr)
		, time_(0.0f) {}


	/**
	 * @brief 크로스 페이드 컨트롤러의 생성자입니다.
	 *
	 * @param skeleton 컨트롤러의 대상이 되는 뼈대입니다.
	 */
	explicit CrossFadeContoller(const Skeleton& skeleton)
		: skeleton_(skeleton)
		, clip_(nullptr)
		, time_(0.0f) {}


	/**
	 * @brief 크로스 페이드 컨트롤러의 가상 소멸자입니다.
	 */
	virtual ~CrossFadeContoller() {}

	
	/**
	 * @brief 애니메이션 플레이를 시작합니다.
	 *
	 * @param target 애니메이션을 플레이할 타겟 클립입니다.
	 *
	 * @note 이 메서드를 실행하면 활성 크로스페이드는 삭제됩니다.
	 */
	void Play(Clip* target);


	/**
	 * @brief 페이드 타겟이 유효한지 확인하고 유효하면 페이드 타겟 목록에 추가합니다.
	 *
	 * @param target 애니메이션을 플레이할 타겟 클립입니다.
	 * @param fadeSeconds 초단위 페이드 시간 값입니다.
	 */
	void FadeTo(Clip* target, float fadeSeconds);


	/**
	 * @brief 크로스 페이드 컨트롤러를 업데이트합니다.
	 *
	 * @param deltaSeconds 업데이트할 초 단위 델타 시간 값입니다.
	 */
	void Update(float deltaSeconds);


	/**
	 * @brief 크로스 페이드 컨트롤러의 현재 포즈 참조자를 얻습니다.
	 *
	 * @return 크로스 페이드 컨트롤러의 현재 포즈 참조자를 반환합니다.
	 */
	Pose& GetCurrentPose() { return pose_; }


	/**
	 * @brief 크로스 페이드 컨트롤러의 현재 클립을 얻습니다.
	 *
	 * @return 크로스 페이드 컨트롤러의 현재 클립을 반환합니다.
	 */
	Clip* GetCurrentClip() { return clip_; }


	/**
	 * @brief 크로스 페이드 컨트롤러의 뼈대를 얻습니다.
	 *
	 * @return 크로스 페이드 컨트롤러의 뼈대를 반환합니다.
	 */
	Skeleton& GetSkeleton() { return skeleton_; }


private:
	/**
	 * @brief 크로스 페이드 타겟입니다.
	 */
	struct CrossFadeTarget
	{
		Pose pose;
		Clip* clip;
		float time;
		float duration;
		float elapsed;
	};


private:
	/**
	 * @brief 컨트롤러의 타겟 목록입니다.
	 */
	std::vector<CrossFadeTarget> targets_;


	/**
	 * @brief 컨트롤러의 애니메이션 클립입니다.
	 */
	Clip* clip_ = nullptr;


	/**
	 * @brief 타겟의 애니메이션 시간입니다.
	 */
	float time_ = 0.0f;


	/**
	 * @brief 컨트롤러의 애니메이션 포즈입니다.
	 */
	Pose pose_;


	/**
	 * @brief 컨트롤러가 대상으로 삼는 뼈대입니다.
	 */
	Skeleton skeleton_;
};