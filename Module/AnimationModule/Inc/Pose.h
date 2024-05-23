#pragma once

#include <vector>

#include "Transform.h"


/**
 * @brief �ִϸ��̼�ȭ�� ĳ������ ��ݿ��� ��� ������ ��ȭ�� �����ϴ� Ŭ�����Դϴ�.
 */
class Pose
{
public:


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