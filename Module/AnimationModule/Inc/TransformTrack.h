#pragma once

#include "Transform.h"

#include "Track.h"


/**
 * @brief 트랜스폼 트랙입니다.
 *
 * @see https://gabormakesgames.com/blog_animation_transformtracks.html
 */
class TransformTrack
{
public:
	/**
	 * @brief 트랜스폼 트랙의 생성자입니다.
	 */
	explicit TransformTrack() {}


	/**
	 * @brief 트랜스폼 트랙의 복사 생성자입니다.
	 *
	 * @param instance 내부 프로퍼티 복사를 수행할 인스턴스입니다.
	 */
	TransformTrack::TransformTrack(TransformTrack&& instance) noexcept
		: boneID_(instance.boneID_)
		, position_(instance.position_)
		, rotate_(instance.rotate_)
		, scale_(instance.scale_) {}


	/**
	 * @brief 트랜스폼 트랙의 복사 생성자입니다.
	 *
	 * @param instance 내부 프로퍼티 복사를 수행할 인스턴스입니다.
	 */
	TransformTrack::TransformTrack(const TransformTrack& instance) noexcept
		: boneID_(instance.boneID_)
		, position_(instance.position_)
		, rotate_(instance.rotate_)
		, scale_(instance.scale_) {}


	/**
	 * @brief 트랜스폼 트랙의 가상 소멸자입니다.
	 */
	virtual ~TransformTrack() {}


	/**
	 * @brief 트랜스폼 트랙의 대입 연산자입니다.
	 *
	 * @param instance 대입 연산을 수행할 인스턴스입니다.
	 *
	 * @return 대입 연산을 수행한 객체의 참조자를 반환합니다.
	 */
	TransformTrack& operator=(TransformTrack&& instance) noexcept
	{
		if (this == &instance) return *this;

		boneID_ = instance.boneID_;
		position_ = instance.position_;
		rotate_ = instance.rotate_;
		scale_ = instance.scale_;

		return *this;
	}


	/**
	 * @brief 트랜스폼 트랙의 대입 연산자입니다.
	 *
	 * @param instance 대입 연산을 수행할 인스턴스입니다.
	 *
	 * @return 대입 연산을 수행한 객체의 참조자를 반환합니다.
	 */
	TransformTrack& operator=(const TransformTrack& instance) noexcept
	{
		if (this == &instance) return *this;

		boneID_ = instance.boneID_;
		position_ = instance.position_;
		rotate_ = instance.rotate_;
		scale_ = instance.scale_;

		return *this;
	}


	/**
	 * @brief 뼈대 ID 값을 얻습니다.
	 *
	 * @return 뼈대 ID값을 반환합니다.
	 */
	const uint32_t& GetBoneID() const { return boneID_; }


	/**
	 * @brief 뼈대 ID 값을 얻습니다.
	 *
	 * @return 뼈대 ID값을 반환합니다.
	 */
	uint32_t& GetBoneID() { return boneID_; }


	/**
	 * @brief 뼈대 ID를 설정합니다.
	 *
	 * @param boneID 설정할 뼈대 ID값입니다.
	 */
	void SetBoneID(const uint32_t& boneID) { boneID_ = boneID; }


	/**
	 * @brief 위치 트랙값을 얻습니다.
	 *
	 * @return 위치 트랙값을 반환합니다.
	 */
	const VectorTrack& GetPositionTrack() const { return position_; }


	/**
	 * @brief 위치 트랙값을 얻습니다.
	 *
	 * @return 위치 트랙값을 반환합니다.
	 */
	VectorTrack& GetPositionTrack() { return position_; }


	/**
	 * @brief 회전 트랙값을 얻습니다.
	 *
	 * @return 회전 트랙값을 반환합니다.
	 */
	const QuaternionTrack& GetRotateTrack() const { return rotate_; }


	/**
	 * @brief 회전 트랙값을 얻습니다.
	 *
	 * @return 회전 트랙값을 반환합니다.
	 */
	QuaternionTrack& GetRotateTrack() { return rotate_; }


	/**
	 * @brief 스케일 트랙값을 얻습니다.
	 *
	 * @return 스케일 트랙값을 반환합니다.
	 */
	const VectorTrack& GetScaleTrack() const { return scale_; }


	/**
	 * @brief 스케일 트랙값을 얻습니다.
	 *
	 * @return 스케일 트랙값을 반환합니다.
	 */
	VectorTrack& GetScaleTrack() { return scale_; }


	/**
	 * @brief 트랙의 시작 시간 값을 얻습니다.
	 *
	 * @return 트랙의 시작 시간 값을 반환합니다.
	 */
	float GetStartTime();


	/**
	 * @brief 트랙의 종료 시간 값을 얻습니다.
	 *
	 * @return 트랙의 종료 시간 값을 반환합니다.
	 */
	float GetEndTime();


	/**
	 * @brief 트랙의 유효성을 검사합니다.
	 *
	 * @return 트랙의 값이 유효하다면 true, 그렇지 않으면 false를 반환합니다.
	 */
	bool IsValid();


	/**
	 * @brief 트랙의 샘플링을 수행합니다.
	 *
	 * @param transform 샘플링할 트랜스폼입니다.
	 * @param time 샘플링할 시간 값입니다.
	 * @param bIsLooping 반복 여부입니다.
	 *
	 * @return 샘플링된 트랜스폼을 반환합니다.
	 */
	Transform Sample(const Transform& transform, float time, bool bIsLooping);


private:
	/**
	 * @brief 변환에 대한 뼈대(본) 아이디입니다.
	 */
	uint32_t boneID_ = 0;


	/**
	 * @brief 위치 트랙입니다.
	 */
	VectorTrack position_;


	/**
	 * @brief 회전 트랙입니다.
	 */
	QuaternionTrack rotate_;


	/**
	 * @brief 스케일 트랙입니다.
	 */
	VectorTrack scale_;
};