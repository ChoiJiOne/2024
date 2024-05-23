#pragma once

#include <string>

#include "TransformTrack.h"
#include "Pose.h"


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


	/**
	 * @brief 인덱스에 대응하는 트랙의 뼈대 ID를 얻습니다.
	 * 
	 * @param index 트랙의 뼈대 ID를 얻을 인덱스입니다.
	 * 
	 * @return 인덱스에 대응하는 트랙의 뼈대 ID를 반환합니다.
	 */
	uint32_t GetBoneID(uint32_t index) { return tracks_[index].GetBoneID(); }


	/**
	 * @brief 인덱스에 대응하는 트랙의 뼈대 ID를 설정합니다.
	 * 
	 * @param index 설정할 트랙의 인덱스입니다.
	 * @param boneID 설정할 뼈대 ID입니다.
	 */
	void SetBoneID(uint32_t index, uint32_t boneID) { tracks_[index].SetBoneID(boneID); }


	/**
	 * @brief 트랙의 크기를 얻습니다.
	 * 
	 * @return 트랙의 크기를 반환합니다.
	 */
	uint32_t Size() const { return static_cast<uint32_t>(tracks_.size()); }


	/**
	 * @brief 클립의 이름을 얻습니다.
	 * 
	 * @return 클립의 이름 값을 반환합니다.
	 */
	const std::string& GetName() const { return name_; }


	/**
	 * @brief 클립의 이름을 설정합니다.
	 * 
	 * @param name 설정할 클립의 이름입니다.
	 */
	void SetName(const std::string& name) { name_ = name; }

	
	/**
	 * @brief 클립의 지속 시간 값을 얻습니다.
	 * 
	 * @return 클립의 지속 시간 값을 반환합니다.
	 */
	float GetDuration() { endTime_ - startTime_; }

	
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