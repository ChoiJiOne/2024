#pragma once

#include <vector>

#include "Interpolation.h"
#include "Keyframe.h"


/**
 * @brief 애니메이션 키 프레임을 모아놓은 트랙입니다.
 */
template <typename T, uint32_t N>
class Track
{
public:
	/**
	 * @brief 애니메이션 트랙의 기본 생성자입니다.
	 */
	Track() = default;


	/**
	 * @brief 애니메이션 트랙의 복사 생성자입니다.
	 * 
	 * @param instance 복사할 인스턴스입니다.
	 */
	Track(Track&& instance) noexcept
		: keyframes_(instance.keyframes_)
		, interpolation_(instance.interpolation_) {}


	/**
	 * @brief 애니메이션 트랙의 복사 생성자입니다.
	 *
	 * @param instance 복사할 인스턴스입니다.
	 */
	Track(const Track&& instance) noexcept 
		: keyframes_(instance.keyframes_)
		, interpolation_(instance.interpolation_) {}


	/**
	 * @brief 애니메이션 트랙의 가상 소멸자입니다.
	 */
	virtual ~Track() {}
	

private:
	/**
	 * @brief 트랙 내의 키 프레임 목록입니다.
	 */
	std::vector<Keyframe<N>> keyframes_;


	/**
	 * @brief 키 프레임을 보간할 때의 유형입니다.
	 */
	EInterpolation interpolation_ = EInterpolation::LINEAR;
};