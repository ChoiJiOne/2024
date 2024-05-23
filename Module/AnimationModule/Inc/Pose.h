#pragma once

#include <vector>

#include "Transform.h"


/**
 * @brief �ִϸ��̼�ȭ�� ĳ������ ��ݿ��� ��� ������ ��ȭ�� �����ϴ� Ŭ�����Դϴ�.
 */
class Pose
{
public:
	/**
	 * @brief ���� Ŭ������ ����Ʈ �������Դϴ�.
	 */
	Pose() = default;


	/**
	 * @brief ���� Ŭ������ ���� �������Դϴ�.
	 * 
	 * @param instance ������ �ν��Ͻ��Դϴ�.
	 */
	Pose(Pose&& instance) noexcept
		: joints_(instance.joints_)
		, parents_(instance.parents_) {}


	/**
	 * @brief ���� Ŭ������ ���� �������Դϴ�.
	 *
	 * @param instance ������ �ν��Ͻ��Դϴ�.
	 */
	Pose(const Pose& instance) noexcept
		: joints_(instance.joints_)
		, parents_(instance.parents_) {}


	/**
	 * @brief ���� Ŭ������ ���� �Ҹ����Դϴ�.
	 */
	virtual ~Pose() {}


private:
	/**
	 * @brief ���� ��ȯ ����Դϴ�.
	 */
	std::vector<Transform> joints_;


	/**
	 * @brief ������ �θ� �ε��� ����Դϴ�.
	 */
	std::vector<int32_t> parents_;
};