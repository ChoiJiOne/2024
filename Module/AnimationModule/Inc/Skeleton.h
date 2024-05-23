#pragma once

#include <string>
#include <vector>

#include "Mat.h"

#include "Pose.h"


/**
 * @brief ���̷���(����)�Դϴ�.
 */
class Skeleton
{
public:
	/**
	 * @brief ���̷���(����)�� ����Ʈ �������Դϴ�.
	 */
	Skeleton() = default;


	/**
	 * @brief ���̷���(����)�� ���� �������Դϴ�.
	 * 
	 * @param instance ������ �ν��Ͻ��Դϴ�.
	 */
	Skeleton(Skeleton&& instance) noexcept
		: restPose_(instance.restPose_)
		, bindPose_(instance.bindPose_)
		, invBindPose_(instance.invBindPose_)
		, jointNames_(instance.jointNames_) {}


	/**
	 * @brief ���̷���(����)�� ���� �������Դϴ�.
	 * 
	 * @param instance ������ �ν��Ͻ��Դϴ�.
	 */
	Skeleton(const Skeleton& instance) noexcept
		: restPose_(instance.restPose_)
		, bindPose_(instance.bindPose_)
		, invBindPose_(instance.invBindPose_)
		, jointNames_(instance.jointNames_) {}


	/**
	 * @brief ���̷���(����)�� ���� �Ҹ����Դϴ�.
	 */
	virtual ~Skeleton() {}


private:
	/**
	 * @brief ������ Rest �����Դϴ�.
	 */
	Pose restPose_;


	/**
	 * @brief ������ Bind �����Դϴ�.
	 */
	Pose bindPose_;


	/**
	 * @brief �� ���ε� ���� ��� ����Դϴ�.
	 */
	std::vector<Mat4x4> invBindPose_;


	/**
	 * @brief ����(Bone) �̸� ����Դϴ�.
	 */
	std::vector<std::string> jointNames_;
};