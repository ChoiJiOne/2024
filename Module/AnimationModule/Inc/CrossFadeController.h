#pragma once

#include <vector>

#include "CrossFadeTarget.h"
#include "Skeleton.h"


/**
 * @brief ��� �����ϴ� ũ�ν� ���̵� ��Ʈ�ѷ��Դϴ�.
 */
class CrossFadeController
{
public:
	/**
	 * @brief ũ�ν� ���̵� ��Ʈ�ѷ��� ����Ʈ �������Դϴ�
	 */
	CrossFadeController() = default;


	/**
	 * @brief ũ�ν� ���̵� ��Ʈ�ѷ��� �����Դϴ�.
	 * 
	 * @param skeleton ���̷���(����)�Դϴ�.
	 */
	CrossFadeController(const Skeleton& skeleton);


	/**
	 * @brief ũ�ν� ���̵� ��Ʈ�ѷ��� ���� �������Դϴ�.
	 * 
	 * @param instance ������ �ν��Ͻ��Դϴ�.
	 */
	CrossFadeController(CrossFadeController&& instance) noexcept
		: targets_(instance.targets_)
		, clip_(instance.clip_)
		, time_(instance.time_)
		, pose_(instance.pose_)
		, skeleton_(instance.skeleton_)
		, bWasSetSkeleton_(instance.bWasSetSkeleton_) {}


	/**
	 * @brief ũ�ν� ���̵� ��Ʈ�ѷ��� ���� �������Դϴ�.
	 *
	 * @param instance ������ �ν��Ͻ��Դϴ�.
	 */
	CrossFadeController(const CrossFadeController& instance) noexcept
		: targets_(instance.targets_)
		, clip_(instance.clip_)
		, time_(instance.time_)
		, pose_(instance.pose_)
		, skeleton_(instance.skeleton_)
		, bWasSetSkeleton_(instance.bWasSetSkeleton_) {}


	/**
	 * @brief ũ�ν� ���̵� ��Ʈ�ѷ��� ���� �Ҹ����Դϴ�.
	 */
	virtual ~CrossFadeController() {}


	/**
	 * @brief ũ�ν� ���̵� ��Ʈ�ѷ��� ���� �������Դϴ�.
	 * 
	 * @param instance ���� ������ ������ �ν��Ͻ��Դϴ�.
	 * 
	 * @return ���� ������ ������ ��ü�� �����ڸ� ��ȯ�մϴ�.
	 */
	CrossFadeController& operator=(CrossFadeController&& instance) noexcept
	{
		if (this == &instance) return *this;

		targets_ = instance.targets_;
		clip_ = instance.clip_;
		time_ = instance.time_;
		pose_ = instance.pose_;
		skeleton_ = instance.skeleton_;
		bWasSetSkeleton_ = instance.bWasSetSkeleton_;

		return *this;
	}


	/**
	 * @brief ũ�ν� ���̵� ��Ʈ�ѷ��� ���� �������Դϴ�.
	 *
	 * @param instance ���� ������ ������ �ν��Ͻ��Դϴ�.
	 *
	 * @return ���� ������ ������ ��ü�� �����ڸ� ��ȯ�մϴ�.
	 */
	CrossFadeController& operator=(const CrossFadeController& instance) noexcept
	{
		if (this == &instance) return *this;

		targets_ = instance.targets_;
		clip_ = instance.clip_;
		time_ = instance.time_;
		pose_ = instance.pose_;
		skeleton_ = instance.skeleton_;
		bWasSetSkeleton_ = instance.bWasSetSkeleton_;

		return *this;
	}


	/**
	 * @brief ũ�ν� ���̵� ��Ʈ�ѷ��� ���븦 �����մϴ�.
	 * 
	 * @param skeleton ������ ���̷���(����)�Դϴ�.
	 */
	void SetSkeleton(const Skeleton& skeleton);


	/**
	 * @brief ���� ũ�ν� ���̵� ��Ʈ�ѷ��� ���븦 ����ϴ�.
	 * 
	 * @return ���� ũ�ν� ���̵� ��Ʈ�ѷ��� ���븦 ��ȯ�մϴ�.
	 */
	Skeleton& GetSkeleton() { return skeleton_; }


	/**
	 * @brief ���� ��� ����ϴ�.
	 * 
	 * @return ���� ������ �����ڸ� ��ȯ�մϴ�.
	 */
	Pose& GetCurrentPose() { return pose_; }


	/**
	 * @brief ���� Ŭ���� ����ϴ�.
	 * 
	 * @return ���� Ŭ���� ��ȯ�մϴ�.
	 */
	Clip* GetCurrentClip() { return clip_; }


	/**
	 * @brief ���� �÷��� �ð� ���� ����ϴ�.
	 * 
	 * @return ���� �÷��� �ð� ���� ��ȯ�մϴ�.
	 */
	float GetTime() const { return time_; }


	/**
	 * @brief Ȱ��ȭ�� ũ�ν� ���̵带 �����ϰ� Ŭ�� �� ��� �ð��� �缳���մϴ�.
	 * 
	 * @param target �缳���� Ŭ���Դϴ�.
	 */
	void Play(Clip* target);


	/**
	 * @brief �ִϸ��̼� Ŭ���� ���� �ð��� ���̵� ��Ͽ� �߰��մϴ�.
	 * 
	 * @param target ���̵� ��Ͽ� �߰��� �ִϸ��̼� Ŭ���Դϴ�.
	 * @param fadeTime �ִϸ��̼� Ŭ�� ���̵� �ð��Դϴ�.
	 */
	void FadeTo(Clip* target, float fadeTime);


	/**
	 * @brief ũ�ν� ���̵� ��Ʈ�ѷ��� ������Ʈ�մϴ�.
	 * 
	 * @param deltaSeconds �ʴ��� ��Ÿ �ð����Դϴ�.
	 */
	void Update(float deltaSeconds);


private:
	/**
	 * @brief ũ�ν� ���̵� Ÿ�� ����Դϴ�.
	 */
	std::vector<CrossFadeTarget> targets_;


	/**
	 * @brief ũ�ν� ���̵��� Ŭ���Դϴ�.
	 */
	Clip* clip_ = nullptr;


	/**
	 * @brief ���� �ð� ���Դϴ�.
	 */
	float time_ = 0.0f;


	/**
	 * @brief ũ�ν� ���̵� �����Դϴ�.
	 */
	Pose pose_;


	/**
	 * @brief ũ�ν� ���̵� ���̷���(����)�Դϴ�.
	 */
	Skeleton skeleton_;


	/**
	 * @brief ���̷����� ������Ʈ�Ǿ����� Ȯ���մϴ�.
	 */
	bool bWasSetSkeleton_ = false;
};