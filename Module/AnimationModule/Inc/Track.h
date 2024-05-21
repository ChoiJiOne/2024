#pragma once

#include <vector>

#include "Quat.h"

#include "Frame.h"
#include "Interpolation.h"


/**
 * @brief Ű ������ ��ϰ� ���� ������ ������ Ʈ���Դϴ�.
 * 
 * @see https://gabormakesgames.com/blog_animation_tracks.html
 */
template <typename T, uint32_t N>
class Track
{
public:
	/**
	 * @brief Ʈ���� �������Դϴ�.
	 */
	explicit Track();


	/**
	 * @brief Ʈ���� ���� �������Դϴ�.
	 *
	 * @param instance ���� ������Ƽ ���縦 ������ �ν��Ͻ��Դϴ�.
	 */
	Track(Track&& instance) noexcept
		: frames_(instance.frames_)
		, interpolation_(instance.interpolation_) {}


	/**
	 * @brief Ʈ���� ���� �������Դϴ�.
	 *
	 * @param instance ���� ������Ƽ ���縦 ������ �ν��Ͻ��Դϴ�.
	 */
	Track(const Track& instance) noexcept
		: frames_(instance.frames_)
		, interpolation_(instance.interpolation_) {}


	/**
	 * @brief Ʈ���� ���� �Ҹ����Դϴ�.
	 */
	virtual ~Track();


	/**
	 * @brief Ʈ���� ���� �������Դϴ�.
	 *
	 * @param instance ���� ������ ������ �ν��Ͻ��Դϴ�.
	 *
	 * @return ���� ������ ������ ��ü�� �����ڸ� ��ȯ�մϴ�.
	 */
	Track& operator=(Track&& instance) noexcept
	{
		if (this == &instance) return *this;

		frames_ = instance.frames_;
		interpolation_ = instance.interpolation_;

		return *this;
	}


	/**
	 * @brief Ʈ���� ���� �������Դϴ�.
	 *
	 * @param instance ���� ������ ������ �ν��Ͻ��Դϴ�.
	 *
	 * @return ���� ������ ������ ��ü�� �����ڸ� ��ȯ�մϴ�.
	 */
	Track& operator=(const Track& instance) noexcept
	{
		if (this == &instance) return *this;

		frames_ = instance.frames_;
		interpolation_ = instance.interpolation_;

		return *this;
	}


	/**
	 * @brief Ʈ���� ������ ũ�⸦ �����մϴ�.
	 *
	 * @param size ������ Ʈ���� ������ ũ���Դϴ�.
	 */
	void Resize(uint32_t size);


	/**
	 * @brief Ʈ���� ������ ũ�⸦ ����ϴ�.
	 *
	 * @return Ʈ���� ������ ũ�⸦ ��ȯ�մϴ�.
	 */
	uint32_t GetSize() const { return static_cast<uint32_t>(frames_.size()); }


	/**
	 * @brief Ʈ���� ���� ����� ���� ������ ���� ����ϴ�.
	 *
	 * @return Ʈ���� ���� ����� ���� ������ ���� ��ȯ�մϴ�.
	 */
	const EInterpolation& GetInterpolation() const { return interpolation_; }


	/**
	 * @brief Ʈ���� ���� ����� ���� ������ ���� �����մϴ�.
	 *
	 * @param interpolation ������ Ʈ���� ���� ����� ���� �������Դϴ�.
	 */
	void SetInterpolation(const EInterpolation& interpolation) { interpolation_ = interpolation; }


	/**
	 * @brief �������� �ð� �ð� ���� ����ϴ�.
	 *
	 * @return �������� ���� �ð� ���� ��ȯ�մϴ�.
	 */
	float GetStartTime() const;


	/**
	 * @brief �������� ������ �ð� ���� ����ϴ�.
	 *
	 * @return �������� ������ �ð� ���� ��ȯ�մϴ�.
	 */
	float GetEndTime() const;


	/**
	 * @brief Ʈ�� ���ø��� �����մϴ�.
	 *
	 * @param time ���ø��� �ð� ���Դϴ�.
	 * @param bIsLooping �ݺ� �����Դϴ�.
	 *
	 * @return ���ø��� ���� ��ȯ�մϴ�.
	 */
	T Sample(float time, bool bIsLooping);


	/**
	 * @brief �����ӿ� ���� ���� ���� ����ϴ�.
	 *
	 * @param index ������ ����� �ε����Դϴ�.
	 *
	 * @return �ε����� �����ϴ� �������� �����ڸ� ��ȯ�մϴ�.
	 */
	Frame<N>& operator[](uint32_t index);


private:
	/**
	 * @brief ��� ���ø��� �����մϴ�.
	 *
	 * @param time ���ø��� �ð� ���Դϴ�.
	 * @param bIsLooping �ݺ� �����Դϴ�.
	 *
	 * @return ���ø��� ���� ��ȯ�մϴ�.
	 */
	T SampleConstant(float time, bool bIsLooping);


	/**
	 * @brief ����(Linear) ���ø��� �����մϴ�.
	 *
	 * @param time ���ø��� �ð� ���Դϴ�.
	 * @param bIsLooping �ݺ� �����Դϴ�.
	 *
	 * @return ���ø��� ���� ��ȯ�մϴ�.
	 */
	T SampleLinear(float time, bool bIsLooping);


	/**
	 * @brief ť��(Cubic, 3��) ���ø��� �����մϴ�.
	 *
	 * @param time ���ø��� �ð� ���Դϴ�.
	 * @param bIsLooping �ݺ� �����Դϴ�.
	 *
	 * @return ���ø��� ���� ��ȯ�մϴ�.
	 */
	T SampleCubic(float time, bool bIsLooping);


	/**
	 * @brief �ع��� ���ö��� � ���� ����մϴ�.
	 *
	 * @param time �ð� ���Դϴ�.
	 * @param point1 ��� ù ��° �����Դϴ�.
	 * @param slope1 ��� ù ��° �����Դϴ�.
	 * @param point2 ��� �� ��° �����Դϴ�.
	 * @param slope2 ��� �� ��° �����Դϴ�.
	 *
	 * @return ���� �ع��� ���ö��� � ���� ��ȯ�մϴ�.
	 */
	T Hermite(float time, const T& point1, const T& slope1, const T& point2, const T& slope2);


	/**
	 * @brief �ð� ���� �����ϴ� ������ �ε��� ���� ����ϴ�.
	 *
	 * @param time ������ �ε��� ���� ���� �ð� ���Դϴ�.
	 * @param bIsLooping �ݺ� �����Դϴ�.
	 *
	 * @return �ð� ���� �����ϴ� ������ �ε��� ���� ��ȯ�մϴ�.
	 */
	int32_t FrameIndex(float time, bool bIsLooping);


	/**
	 * @brief Ʈ���� ����/�� ������ ���� ���� �����մϴ�.
	 *
	 * @param time ������ Ʈ�� �ð� ���Դϴ�.
	 * @param bIsLooping �ݺ� �����Դϴ�.
	 *
	 * @return ������ �ð����� ��ȯ�մϴ�.
	 */
	float AdjustTimeToFitTrack(float time, bool bIsLooping);


	/**
	 * @brief �ε� �Ҽ��� �迭�� ĳ�����մϴ�.
	 *
	 * @param value ĳ������ �ε� �Ҽ��� �迭�Դϴ�.
	 *
	 * @return ĳ���õ� ���� ��ȯ�մϴ�.
	 */
	T Cast(float* value);


private:
	/**
	 * @brief Ʈ�� ���� Ű ������ ����Դϴ�.
	 */
	std::vector<Frame<N>> frames_;


	/**
	 * @brief Ű ������ ���� ����Դϴ�.
	 */
	EInterpolation interpolation_ = EInterpolation::LINEAR;
};


using ScalarTrack = Track<float, 1>;
using VectorTrack = Track<Vec3f, 3>;
using QuaternionTrack = Track<Quat, 4>;