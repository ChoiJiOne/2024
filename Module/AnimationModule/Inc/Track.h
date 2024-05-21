#pragma once

#include <vector>

#include "Quat.h"

#include "Frame.h"
#include "Interpolation.h"


/**
 * @brief 키 프레임 목록과 보간 정보를 포함한 트랙입니다.
 * 
 * @see https://gabormakesgames.com/blog_animation_tracks.html
 */
template <typename T, uint32_t N>
class Track
{
public:
	/**
	 * @brief 트랙의 생성자입니다.
	 */
	explicit Track();


	/**
	 * @brief 트랙의 복사 생성자입니다.
	 *
	 * @param instance 내부 프로퍼티 복사를 수행할 인스턴스입니다.
	 */
	Track(Track&& instance) noexcept
		: frames_(instance.frames_)
		, interpolation_(instance.interpolation_) {}


	/**
	 * @brief 트랙의 복사 생성자입니다.
	 *
	 * @param instance 내부 프로퍼티 복사를 수행할 인스턴스입니다.
	 */
	Track(const Track& instance) noexcept
		: frames_(instance.frames_)
		, interpolation_(instance.interpolation_) {}


	/**
	 * @brief 트랙의 가상 소멸자입니다.
	 */
	virtual ~Track();


	/**
	 * @brief 트랙의 대입 연산자입니다.
	 *
	 * @param instance 대입 연산을 수행할 인스턴스입니다.
	 *
	 * @return 대입 연산을 수행한 객체의 참조자를 반환합니다.
	 */
	Track& operator=(Track&& instance) noexcept
	{
		if (this == &instance) return *this;

		frames_ = instance.frames_;
		interpolation_ = instance.interpolation_;

		return *this;
	}


	/**
	 * @brief 트랙의 대입 연산자입니다.
	 *
	 * @param instance 대입 연산을 수행할 인스턴스입니다.
	 *
	 * @return 대입 연산을 수행한 객체의 참조자를 반환합니다.
	 */
	Track& operator=(const Track& instance) noexcept
	{
		if (this == &instance) return *this;

		frames_ = instance.frames_;
		interpolation_ = instance.interpolation_;

		return *this;
	}


	/**
	 * @brief 트랙의 프레임 크기를 변경합니다.
	 *
	 * @param size 변경할 트랙의 프레임 크기입니다.
	 */
	void Resize(uint32_t size);


	/**
	 * @brief 트랙의 프레임 크기를 얻습니다.
	 *
	 * @return 트랙의 프레임 크기를 반환합니다.
	 */
	uint32_t GetSize() const { return static_cast<uint32_t>(frames_.size()); }


	/**
	 * @brief 트랙의 보간 방법에 대한 열거형 값을 얻습니다.
	 *
	 * @return 트랙의 보간 방법에 대한 열거형 값을 반환합니다.
	 */
	const EInterpolation& GetInterpolation() const { return interpolation_; }


	/**
	 * @brief 트랙의 보간 방법에 대한 열거형 값을 설정합니다.
	 *
	 * @param interpolation 설정할 트랙의 보간 방법에 대한 열거형입니다.
	 */
	void SetInterpolation(const EInterpolation& interpolation) { interpolation_ = interpolation; }


	/**
	 * @brief 프레임의 시간 시간 값을 얻습니다.
	 *
	 * @return 프레임의 시작 시간 값을 반환합니다.
	 */
	float GetStartTime() const;


	/**
	 * @brief 프레임의 마지막 시간 값을 얻습니다.
	 *
	 * @return 프레임의 마지막 시간 값을 반환합니다.
	 */
	float GetEndTime() const;


	/**
	 * @brief 트랙 샘플링을 수행합니다.
	 *
	 * @param time 샘플링할 시간 값입니다.
	 * @param bIsLooping 반복 여부입니다.
	 *
	 * @return 샘플링된 값을 반환합니다.
	 */
	T Sample(float time, bool bIsLooping);


	/**
	 * @brief 프레임에 대한 참조 값을 얻습니다.
	 *
	 * @param index 프레임 목록의 인덱스입니다.
	 *
	 * @return 인덱스에 대응하는 프레임의 참조자를 반환합니다.
	 */
	Frame<N>& operator[](uint32_t index);


private:
	/**
	 * @brief 상수 샘플링을 수행합니다.
	 *
	 * @param time 샘플링할 시간 값입니다.
	 * @param bIsLooping 반복 여부입니다.
	 *
	 * @return 샘플링된 값을 반환합니다.
	 */
	T SampleConstant(float time, bool bIsLooping);


	/**
	 * @brief 선형(Linear) 샘플링을 수행합니다.
	 *
	 * @param time 샘플링할 시간 값입니다.
	 * @param bIsLooping 반복 여부입니다.
	 *
	 * @return 샘플링된 값을 반환합니다.
	 */
	T SampleLinear(float time, bool bIsLooping);


	/**
	 * @brief 큐빅(Cubic, 3차) 샘플링을 수행합니다.
	 *
	 * @param time 샘플링할 시간 값입니다.
	 * @param bIsLooping 반복 여부입니다.
	 *
	 * @return 샘플링된 값을 반환합니다.
	 */
	T SampleCubic(float time, bool bIsLooping);


	/**
	 * @brief 해밀턴 스플라인 곡선 값을 계산합니다.
	 *
	 * @param time 시간 값입니다.
	 * @param point1 곡선의 첫 번째 지점입니다.
	 * @param slope1 곡선의 첫 번째 기울기입니다.
	 * @param point2 곡선의 두 번째 지점입니다.
	 * @param slope2 곡선의 두 번째 기울기입니다.
	 *
	 * @return 계산된 해밀턴 스플라인 곡선 값을 반환합니다.
	 */
	T Hermite(float time, const T& point1, const T& slope1, const T& point2, const T& slope2);


	/**
	 * @brief 시간 값에 대응하는 프레임 인덱스 값을 얻습니다.
	 *
	 * @param time 프레임 인덱스 값을 얻을 시간 값입니다.
	 * @param bIsLooping 반복 여부입니다.
	 *
	 * @return 시간 값에 대응하는 프레임 인덱스 값을 반환합니다.
	 */
	int32_t FrameIndex(float time, bool bIsLooping);


	/**
	 * @brief 트랙의 시작/끝 프레임 범위 내로 조정합니다.
	 *
	 * @param time 조정할 트랙 시간 값입니다.
	 * @param bIsLooping 반복 여부입니다.
	 *
	 * @return 조정된 시간값을 반환합니다.
	 */
	float AdjustTimeToFitTrack(float time, bool bIsLooping);


	/**
	 * @brief 부동 소수점 배열을 캐스팅합니다.
	 *
	 * @param value 캐스팅할 부동 소수점 배열입니다.
	 *
	 * @return 캐스팅된 값을 반환합니다.
	 */
	T Cast(float* value);


private:
	/**
	 * @brief 트랙 내의 키 프레임 목록입니다.
	 */
	std::vector<Frame<N>> frames_;


	/**
	 * @brief 키 프레임 보간 방법입니다.
	 */
	EInterpolation interpolation_ = EInterpolation::LINEAR;
};


using ScalarTrack = Track<float, 1>;
using VectorTrack = Track<Vec3f, 3>;
using QuaternionTrack = Track<Quat, 4>;