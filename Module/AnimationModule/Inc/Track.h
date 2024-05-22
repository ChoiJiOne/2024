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


	/**
	 * @brief 애니메이션 트랙의 대입 연산자입니다.
	 * 
	 * @param instance 대입 연산을 수행할 인스턴스입니다.
	 * 
	 * @return 대입 연산을 수행한 객체의 참조자를 반환합니다.
	 */
	Track& operator=(Track&& instance) noexcept
	{
		if (this == &instance) return *this;

		keyframes_ = instance.keyframes_;
		interpolation_ = instance.interpolation_;

		return *this;
	}


	/**
	 * @brief 애니메이션 트랙의 대입 연산자입니다.
	 *
	 * @param instance 대입 연산을 수행할 인스턴스입니다.
	 *
	 * @return 대입 연산을 수행한 객체의 참조자를 반환합니다.
	 */
	Track& operator=(const Track& instance) noexcept
	{
		if (this == &instance) return *this;

		keyframes_ = instance.keyframes_;
		interpolation_ = instance.interpolation_;

		return *this;
	}


	/**
	 * @brief 키 프레임 목록의 크기를 변경합니다.
	 * 
	 * @param size 변경할 키 프레임 목록의 크기입니다.
	 */
	void Resize(uint32_t size) { keyframes_.resize(size); }


	/**
	 * @brief 키 프레임 목록의 크기를 얻습니다.
	 * 
	 * @return 키 프레임 목록의 크기를 반환합니다.
	 */
	uint32_t Size() const { return static_cast<uint32_t>(keyframes_.size()); }


	/**
	 * @brief 키 프레임을 보간할 때의 유형을 얻습니다.
	 * 
	 * @return 키 프레임을 보간할 때의 유형 값을 반환합니다.
	 */
	const EInterpolation& GetInterpolation() const { return interpolation_; }


	/**
	 * @brief 키 프레임을 보간할 때의 유형을 설정합니다.
	 * 
	 * @param interpolation 설정할 키 프레임 보간 유형입니다.
	 */
	void SetInterpolation(const EInterpolation& interpolation) { interpolation_ = interpolation; }


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