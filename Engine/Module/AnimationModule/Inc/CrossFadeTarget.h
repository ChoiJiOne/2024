#pragma once

#include "Clip.h"
#include "Pose.h"


/**
 * @brief �ִϸ��̼� ���̵� �� ���ø��� ������ ���� ���Դϴ�.
 */
struct CrossFadeTarget
{
	/**
	 * @brief ũ�ν� ���̵� Ÿ���� �⺻ �������Դϴ�.
	 */
	CrossFadeTarget() = default;


	/**
	 * @brief ũ�ν� ���̵� Ÿ���� �������Դϴ�.
	 * 
	 * @param targetClip ũ�ν� ���̵� Ÿ���� Ŭ���Դϴ�.
	 * @param targetPose ũ�ν� ���̵� Ÿ���� �����Դϴ�.
	 * @param targetDuration ũ�ν� ���̵� Ÿ���� �ִϸ��̼� ���� �ð��Դϴ�.
	 */
	CrossFadeTarget(Clip* targetClip, const Pose& targetPose, float targetDuration)
		: clip(targetClip)
		, pose(targetPose)
		, time(targetClip->GetStartTime())
		, duration(targetDuration)
		, elapsed(0.0f) {}


	/**
	 * @brief ũ�ν� ���̵� Ÿ���� ���� �������Դϴ�.
	 * 
	 * @param instance ������ �ν��Ͻ��Դϴ�.
	 */
	CrossFadeTarget(CrossFadeTarget&& instance) noexcept
		: pose(instance.pose)
		, clip(instance.clip)
		, time(instance.time)
		, duration(instance.duration)
		, elapsed(instance.elapsed) {}


	/**
	 * @brief ũ�ν� ���̵� Ÿ���� ���� �������Դϴ�.
	 *
	 * @param instance ������ �ν��Ͻ��Դϴ�.
	 */
	CrossFadeTarget(const CrossFadeTarget& instance) noexcept
		: pose(instance.pose)
		, clip(instance.clip)
		, time(instance.time)
		, duration(instance.duration)
		, elapsed(instance.elapsed) {}


	/**
	 * @brief ũ�ν� ���̵��� ���� �Ҹ����Դϴ�.
	 */
	virtual ~CrossFadeTarget() {}


	/**
	 * @brief ũ�ν� ���̵� Ÿ���� ���� �������Դϴ�.
	 * 
	 * @param instance ���� ������ ������ �ν��Ͻ��Դϴ�.
	 * 
	 * @return ���� ������ ������ ��ü�� �����ڸ� ��ȯ�մϴ�.
	 */
	CrossFadeTarget& operator=(CrossFadeTarget&& instance) noexcept
	{
		if (this == &instance) return *this;

		pose = instance.pose;
		clip = instance.clip;
		time = instance.time;
		duration = instance.duration;
		elapsed = instance.elapsed;

		return *this;
	}


	/**
	 * @brief ũ�ν� ���̵� Ÿ���� ���� �������Դϴ�.
	 *
	 * @param instance ���� ������ ������ �ν��Ͻ��Դϴ�.
	 *
	 * @return ���� ������ ������ ��ü�� �����ڸ� ��ȯ�մϴ�.
	 */
	CrossFadeTarget& operator=(const CrossFadeTarget& instance) noexcept
	{
		if (this == &instance) return *this;

		pose = instance.pose;
		clip = instance.clip;
		time = instance.time;
		duration = instance.duration;
		elapsed = instance.elapsed;

		return *this;
	}


	/**
	 * @brief �ִϸ��̼� ���̵� �� ���ø��� �����Դϴ�.
	 */
	Pose pose;


	/**
	 * @brief ������ �ִϸ��̼� Ŭ���Դϴ�.
	 */
	Clip* clip = nullptr;


	/**
	 * @brief ���� �ð����Դϴ�.
	 */
	float time = 0.0f;


	/**
	 * @brief �ִϸ��̼� ���� �ð��Դϴ�.
	 */
	float duration = 0.0f;


	/**
	 * @brief �ִϸ��̼� �÷��� ��� �ð��Դϴ�.
	 */
	float elapsed = 0.0f;
};