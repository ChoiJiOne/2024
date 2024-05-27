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
	 * @brief ũ�ν� ���̵� ��Ʈ�ѷ��� ���븦 �����մϴ�.
	 * 
	 * @param skeleton ������ ���̷���(����)�Դϴ�.
	 */
	void SetSkeleton(const Skeleton& skeleton);


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