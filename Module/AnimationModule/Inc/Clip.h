#pragma once

#include <string>

#include "TransformTrack.h"


/**
 * @brief �ִϸ��̼� Ʈ���� ������ Ŭ��(Clip)�Դϴ�.
 */
class Clip
{
public:


private:
	/**
	 * @brief Ŭ�� ���� Ʈ������ Ʈ���Դϴ�.
	 */
	std::vector<TransformTrack> tracks_;


	/**
	 * @brief Ŭ���� �̸��Դϴ�.
	 */
	std::string name_;


	/**
	 * @brief Ŭ���� ���� �ð��Դϴ�.
	 */
	float startTime_ = 0.0f;


	/**
	 * @brief Ŭ���� ���� �ð��Դϴ�.
	 */
	float endTime_ = 0.0f;


	/**
	 * @brief Ŭ���� �ݺ� �����Դϴ�.
	 */
	bool bIsLooping_ = false;
};