#pragma once

#include <string>

#include "TransformTrack.h"


/**
 * @brief �ִϸ��̼� Ʈ���� ������ Ŭ��(Clip)�Դϴ�.
 */
class Clip
{
public:
	/**
	 * @brief Ŭ���� ����Ʈ �������Դϴ�.
	 */
	Clip() = default;


	/**
	 * @brief Ŭ���� ���� �������Դϴ�.
	 * 
	 * @param instance ������ �ν��Ͻ��Դϴ�.
	 */
	Clip(Clip&& instance) noexcept
		: tracks_(instance.tracks_)
		, name_(instance.name_)
		, startTime_(instance.startTime_)
		, endTime_(instance.endTime_)
		, bIsLooping_(instance.bIsLooping_) {}


	/**
	 * @brief Ŭ���� ���� �������Դϴ�.
	 *
	 * @param instance ������ �ν��Ͻ��Դϴ�.
	 */
	Clip(const Clip& instance) noexcept
		: tracks_(instance.tracks_)
		, name_(instance.name_)
		, startTime_(instance.startTime_)
		, endTime_(instance.endTime_)
		, bIsLooping_(instance.bIsLooping_) {}


	/**
	 * @brief Ŭ���� ���� �Ҹ����Դϴ�.
	 */
	virtual ~Clip() {}


private:
	/**
	 * @brief Ŭ�� ���� Ʈ������ Ʈ���Դϴ�.
	 */
	std::vector<TransformTrack> tracks_;


	/**
	 * @brief Ŭ���� �̸��Դϴ�.
	 */
	std::string name_ = "empty";


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
	bool bIsLooping_ = true;
};