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