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
	 * @brief ���̷���(����)�� �������Դϴ�.
	 * 
	 * @param restPose �޽� �����Դϴ�.
	 * @param bindPose ���ε� �����Դϴ�.
	 * @param jointNames ����(Bone) �̸� ����Դϴ�.
	 */
	Skeleton(const Pose& restPose, const Pose& bindPose, const std::vector<std::string>& jointNames);


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


	/**
	 * @brief ���ε� ��� ����ϴ�.
	 * 
	 * @return ���ε� ������ �����ڸ� ��ȯ�մϴ�.
	 */
	Pose& GetBindPose() { return bindPose_; }


	/**
	 * @brief �޽� ��� ����ϴ�.
	 * 
	 * @return �޽� ������ �����ڸ� ��ȯ�մϴ�.
	 */
	Pose& GetRestPose() { return restPose_; }


	/**
	 * @brief �� ���ε� ���� ����� ����ϴ�.
	 * 
	 * @return �� ���ε� ���� ����� ���� �����ڸ� ��ȯ�մϴ�.
	 */
	std::vector<Mat4x4>& GetInvBindPose() { return invBindPose_; }


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