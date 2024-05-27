#pragma once

#include "Clip.h"
#include "Pose.h"


/**
 * @brief �ִϸ��̼� ���̵� �� ���ø��� ������ ���� ���Դϴ�.
 */
class CrossFadeTarget
{
public:
	/**
	 * @brief ũ�ν� ���̵� Ÿ���� �⺻ �������Դϴ�.
	 */
	CrossFadeTarget() = default;


	/**
	 * @brief ũ�ν� ���̵� Ÿ���� �������Դϴ�.
	 * 
	 * @param ũ�ν� ���̵� Ÿ���� Ŭ���Դϴ�.
	 * @param ũ�ν� ���̵� Ÿ���� �����Դϴ�.
	 * @param ũ�ν� ���̵� Ÿ���� �ִϸ��̼� ���� �ð��Դϴ�.
	 */
	CrossFadeTarget(Clip* target, const Pose& pose, float duration)
		: clip_(target)
		, pose_(pose)
		, time_(target->GetStartTime())
		, duration_(duration)
		, elapsed_(0.0f) {}


	/**
	 * @brief ũ�ν� ���̵� Ÿ���� ���� �������Դϴ�.
	 * 
	 * @param instance ������ �ν��Ͻ��Դϴ�.
	 */
	CrossFadeTarget(CrossFadeTarget&& instance) noexcept
		: pose_(instance.pose_)
		, clip_(instance.clip_)
		, time_(instance.time_)
		, duration_(instance.duration_)
		, elapsed_(instance.elapsed_) {}


	/**
	 * @brief ũ�ν� ���̵� Ÿ���� ���� �������Դϴ�.
	 *
	 * @param instance ������ �ν��Ͻ��Դϴ�.
	 */
	CrossFadeTarget(const CrossFadeTarget& instance) noexcept
		: pose_(instance.pose_)
		, clip_(instance.clip_)
		, time_(instance.time_)
		, duration_(instance.duration_)
		, elapsed_(instance.elapsed_) {}


private:
	/**
	 * @brief �ִϸ��̼� ���̵� �� ���ø��� �����Դϴ�.
	 */
	Pose pose_;


	/**
	 * @brief ������ �ִϸ��̼� Ŭ���Դϴ�.
	 */
	Clip* clip_ = nullptr;


	/**
	 * @brief ���� �ð����Դϴ�.
	 */
	float time_ = 0.0f;


	/**
	 * @brief �ִϸ��̼� ���� �ð��Դϴ�.
	 */
	float duration_ = 0.0f;


	/**
	 * @brief �ִϸ��̼� �÷��� ��� �ð��Դϴ�.
	 */
	float elapsed_ = 0.0f;
};