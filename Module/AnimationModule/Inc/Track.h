#pragma once

#include <vector>

#include "Interpolation.h"
#include "Keyframe.h"


/**
 * @brief �ִϸ��̼� Ű �������� ��Ƴ��� Ʈ���Դϴ�.
 */
template <typename T, uint32_t N>
class Track
{
public:
	/**
	 * @brief �ִϸ��̼� Ʈ���� �⺻ �������Դϴ�.
	 */
	Track() = default;


	/**
	 * @brief �ִϸ��̼� Ʈ���� ���� �������Դϴ�.
	 * 
	 * @param instance ������ �ν��Ͻ��Դϴ�.
	 */
	Track(Track&& instance) noexcept
		: keyframes_(instance.keyframes_)
		, interpolation_(instance.interpolation_) {}


	/**
	 * @brief �ִϸ��̼� Ʈ���� ���� �������Դϴ�.
	 *
	 * @param instance ������ �ν��Ͻ��Դϴ�.
	 */
	Track(const Track&& instance) noexcept 
		: keyframes_(instance.keyframes_)
		, interpolation_(instance.interpolation_) {}


	/**
	 * @brief �ִϸ��̼� Ʈ���� ���� �Ҹ����Դϴ�.
	 */
	virtual ~Track() {}
	

private:
	/**
	 * @brief Ʈ�� ���� Ű ������ ����Դϴ�.
	 */
	std::vector<Keyframe<N>> keyframes_;


	/**
	 * @brief Ű �������� ������ ���� �����Դϴ�.
	 */
	EInterpolation interpolation_ = EInterpolation::LINEAR;
};