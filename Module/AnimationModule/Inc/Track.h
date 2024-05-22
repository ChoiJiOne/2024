#pragma once

#include <vector>

#include "Vec.h"
#include "Quat.h"

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


	/**
	 * @brief �ִϸ��̼� Ʈ���� ���� �������Դϴ�.
	 * 
	 * @param instance ���� ������ ������ �ν��Ͻ��Դϴ�.
	 * 
	 * @return ���� ������ ������ ��ü�� �����ڸ� ��ȯ�մϴ�.
	 */
	Track& operator=(Track&& instance) noexcept
	{
		if (this == &instance) return *this;

		keyframes_ = instance.keyframes_;
		interpolation_ = instance.interpolation_;

		return *this;
	}


	/**
	 * @brief �ִϸ��̼� Ʈ���� ���� �������Դϴ�.
	 *
	 * @param instance ���� ������ ������ �ν��Ͻ��Դϴ�.
	 *
	 * @return ���� ������ ������ ��ü�� �����ڸ� ��ȯ�մϴ�.
	 */
	Track& operator=(const Track& instance) noexcept
	{
		if (this == &instance) return *this;

		keyframes_ = instance.keyframes_;
		interpolation_ = instance.interpolation_;

		return *this;
	}


	/**
	 * @brief Ű ������ ����� ũ�⸦ �����մϴ�.
	 * 
	 * @param size ������ Ű ������ ����� ũ���Դϴ�.
	 */
	void Resize(uint32_t size) { keyframes_.resize(size); }


	/**
	 * @brief Ű ������ ����� ũ�⸦ ����ϴ�.
	 * 
	 * @return Ű ������ ����� ũ�⸦ ��ȯ�մϴ�.
	 */
	uint32_t Size() const { return static_cast<uint32_t>(keyframes_.size()); }


	/**
	 * @brief Ű �������� ������ ���� ������ ����ϴ�.
	 * 
	 * @return Ű �������� ������ ���� ���� ���� ��ȯ�մϴ�.
	 */
	const EInterpolation& GetInterpolation() const { return interpolation_; }


	/**
	 * @brief Ű �������� ������ ���� ������ �����մϴ�.
	 * 
	 * @param interpolation ������ Ű ������ ���� �����Դϴ�.
	 */
	void SetInterpolation(const EInterpolation& interpolation) { interpolation_ = interpolation; }


	/**
	 * @brief Ű �������� ���� �ð��� ����ϴ�.
	 * 
	 * @return Ű �������� ���� �ð� ���� ��ȯ�մϴ�.
	 */
	float GetStartTime() const { return keyframes_.front().time; }


	/**
	 * @brief Ű �������� �� �ð��� ����ϴ�.
	 * 
	 * @return Ű �������� �� �ð� ���� ��ȯ�մϴ�.
	 */
	float GetEndTime() const { return keyframes_.back().time; }


	/**
	 * @brief �ε����� Ű ������ ����� �����մϴ�.
	 * 
	 * @param index Ű ������ ����� �ε����Դϴ�.
	 * 
	 * @return �ε����� �����ϴ� Ű ������ ���� ��ȯ�մϴ�.
	 */
	Keyframe<N>& operator[](uint32_t index);


	/**
	 * @brief �ð� ���� �°� Ʈ���� ���ø��մϴ�.
	 * 
	 * @param time Ʈ���� ���ø��� �ð� ���Դϴ�.
	 * @param bIsLooping Ʈ���� �ݺ� �����Դϴ�.
	 * 
	 * @return ���ø��� ���� ��ȯ�մϴ�.
	 */
	T Sample(float time, bool bIsLooping);


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