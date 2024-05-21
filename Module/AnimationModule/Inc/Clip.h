#pragma once

#include <string>
#include <vector>

#include "TransformTrack.h"
#include "Pose.h"


/**
 * @brief 애니메이션 트랙의 집합을 나타내는 클립입니다.
 */
class Clip
{
public:
	/**
	 * @brief 클립의 기본 생성자입니다.
	 */
	explicit Clip()
		: startTime_(0.0f)
		, endTime_(0.0f)
		, bIsLooping_(true) {}


	/**
	 * @brief 클립의 가상 소멸자입니다.
	 */
	virtual ~Clip() {}


	/**
	 * @brief 클립의 복사 생성자입니다.
	 * 
	 * @param instance 내부 프로퍼티를 복사할 인스턴스입니다.
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
	 * @param instance 내부 프로퍼티를 복사할 인스턴스입니다.
	 */
	Clip(const Clip& instance) noexcept
		: tracks_(instance.tracks_)
		, name_(instance.name_)
		, startTime_(instance.startTime_)
		, endTime_(instance.endTime_)
		, bIsLooping_(instance.bIsLooping_) {}


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


	/**
	 * @brief 인덱스에 대응하는 트랙의 ID값을 얻습니다.
	 *
	 * @param index 트랙의 ID값을 얻을 인덱스입니다.
	 *
	 * @return 인덱스에 대응하는 트랙의 ID값을 반환합니다.
	 */
	uint32_t GetTrackID(uint32_t index);


	/**
	 * @brief 인덱스에 대응하는 트랙의 ID값을 설정합니다.
	 *
	 * @param index 설정할 트랙의 인덱스입니다.
	 * @param id 설정할 트랙의 ID값입니다.
	 */
	void SetTrackID(uint32_t index, uint32_t id);


	/**
	 * @brief 애니메이션 트랙 집합의 크기를 얻습니다.
	 *
	 * @return 트랙 집합의 크기를 반환합니다.
	 */
	uint32_t GetTrackSize() const { return static_cast<uint32_t>(tracks_.size()); }


	/**
	 * @brief 시간에 대해 포즈를 샘플링합니다.
	 *
	 * @param outPose 샘플링된 포즈를 저장할 값입니다.
	 * @param time 샘플링할 시간 값입니다.
	 *
	 * @return 샘플링된 시간 값을 반환합니다.
	 */
	float Sample(Pose& outPose, float time);


	/**
	 * @brief 인덱스에 대응하는 트랙값을 얻습니다.
	 *
	 * @param index 트랙값을 얻을 인덱스입니다.
	 *
	 * @return 인덱스에 대응하는 트랙값의 참조자를 반환합니다.
	 */
	TransformTrack& operator[](uint32_t index);


	/**
	 * @brief 지속 시간을 다시 계산합니다.
	 */
	void RecomputeDuration();


	/**
	 * @brief 클립의 이름을 얻습니다.
	 *
	 * @return 클립의 이름값을 반환합니다.
	 */
	const std::string& GetName() const { return name_; }


	/**
	 * @brief 클립 이름을 설정합니다.
	 *
	 * @param name 설정할 클립 이름입니다.
	 */
	void SetName(const std::string& name) { name_ = name; }


	/**
	 * @brief 지속 시간 값을 얻습니다.
	 *
	 * @return 지속 시간 값을 반환합니다.
	 */
	float GetDuration() const { return endTime_ - startTime_; }


	/**
	 * @brief 시작 시간 값을 얻습니다.
	 *
	 * @return 시작 시간 값을 반환합니다.
	 */
	float GetStartTime() const { return startTime_; }


	/**
	 * @brief 종료 시간 값을 얻습니다.
	 *
	 * @return 종료 시간 값을 반환합니다.
	 */
	float GetEndTime() const { return endTime_; }


	/**
	 * @brief 반복 여부를 얻습니다.
	 *
	 * @return 반복한다면 true, 그렇지 않으면 false를 반환합니다.
	 */
	bool IsLooping() const { return bIsLooping_; }


	/**
	 * @brief 반복 여부를 설정합니다.
	 *
	 * @param bIsLooping 설정할 반복 여부입니다.
	 */
	void SetLooping(bool bIsLooping) { bIsLooping_ = bIsLooping; }


private:
	/**
	 * @brief 시간 값을 범위 내로 조정합니다.
	 *
	 * @param time 범위를 조정할 시간 값입니다.
	 *
	 * @return 범위가 조정된 시간 값을 반환합니다.
	 */
	float AdjustTimeToFitRange(float time);


private:
	/**
	 * @brief 애니메이션 트랙 집합입니다.
	 */
	std::vector<TransformTrack> tracks_;


	/**
	 * @brief 클립 이름입니다.
	 */
	std::string name_;


	/**
	 * @brief 시작 시간입니다.
	 */
	float startTime_ = 0.0f;


	/**
	 * @brief 종료 시간입니다.
	 */
	float endTime_ = 0.0f;


	/**
	 * @brief 반복 여부입니다.
	 */
	bool bIsLooping_ = true;
};