#pragma once

#include <string>

#include "TransformTrack.h"


/**
 * @brief 애니메이션 트랙의 모음인 클립(Clip)입니다.
 */
class Clip
{
public:
	/**
	 * @brief 클립의 디폴트 생성자입니다.
	 */
	Clip() = default;


	/**
	 * @brief 클립의 복사 생성자입니다.
	 * 
	 * @param instance 복사할 인스턴스입니다.
	 */
	Clip(Clip&& instance) noexcept
		: tracks_(instance.tracks_)
		, name_(instance.name_)
		, startTime_(instance.startTime_)
		, endTime_(instance.endTime_)
		, bIsLooping_(instance.bIsLooping_) {}


	/**
	 * @brief 클립의 복사 생성자입니다.
	 *
	 * @param instance 복사할 인스턴스입니다.
	 */
	Clip(const Clip& instance) noexcept
		: tracks_(instance.tracks_)
		, name_(instance.name_)
		, startTime_(instance.startTime_)
		, endTime_(instance.endTime_)
		, bIsLooping_(instance.bIsLooping_) {}


	/**
	 * @brief 클립의 가상 소멸자입니다.
	 */
	virtual ~Clip() {}


	/**
	 * @brief 클립의 대입 연산자입니다.
	 * 
	 * @param instance 대입 연산을 수행할 인스턴스입니다.
	 * 
	 * @return 대입 연산을 수행한 객체의 참조자를 반환합니다.
	 */
	Clip& operator=(Clip&& instance) noexcept
	{
		if (this == &instance) return *this;

		tracks_ = instance.tracks_;
		name_ = instance.name_;
		startTime_ = instance.startTime_;
		endTime_ = instance.endTime_;
		bIsLooping_ = instance.bIsLooping_;

		return *this;
	}


	/**
	 * @brief 클립의 대입 연산자입니다.
	 *
	 * @param instance 대입 연산을 수행할 인스턴스입니다.
	 *
	 * @return 대입 연산을 수행한 객체의 참조자를 반환합니다.
	 */
	Clip& operator=(const Clip& instance) noexcept
	{
		if (this == &instance) return *this;

		tracks_ = instance.tracks_;
		name_ = instance.name_;
		startTime_ = instance.startTime_;
		endTime_ = instance.endTime_;
		bIsLooping_ = instance.bIsLooping_;

		return *this;
	}


private:
	/**
	 * @brief 클립 내의 트랜스폼 트랙입니다.
	 */
	std::vector<TransformTrack> tracks_;


	/**
	 * @brief 클립의 이름입니다.
	 */
	std::string name_ = "empty";


	/**
	 * @brief 클립의 시작 시간입니다.
	 */
	float startTime_ = 0.0f;


	/**
	 * @brief 클립의 종료 시간입니다.
	 */
	float endTime_ = 0.0f;


	/**
	 * @brief 클립의 반복 여부입니다.
	 */
	bool bIsLooping_ = true;
};