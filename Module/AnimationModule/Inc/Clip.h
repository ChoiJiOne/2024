#pragma once

#include <string>

#include "TransformTrack.h"
#include "Pose.h"


/**
 * @brief �ִϸ��̼� Ʈ���� ������ Ŭ��(Clip)�Դϴ�.
 */
class Clip
{
public:
	/**
	 * @brief Ŭ���� ����Ʈ �������Դϴ�.
	 */
	Clip() = default;


	/**
	 * @brief Ŭ���� ���� �������Դϴ�.
	 * 
	 * @param instance ������ �ν��Ͻ��Դϴ�.
	 */
	Clip(Clip&& instance) noexcept
		: tracks_(instance.tracks_)
		, name_(instance.name_)
		, startTime_(instance.startTime_)
		, endTime_(instance.endTime_)
		, bIsLooping_(instance.bIsLooping_) {}


	/**
	 * @brief Ŭ���� ���� �������Դϴ�.
	 *
	 * @param instance ������ �ν��Ͻ��Դϴ�.
	 */
	Clip(const Clip& instance) noexcept
		: tracks_(instance.tracks_)
		, name_(instance.name_)
		, startTime_(instance.startTime_)
		, endTime_(instance.endTime_)
		, bIsLooping_(instance.bIsLooping_) {}


	/**
	 * @brief Ŭ���� ���� �Ҹ����Դϴ�.
	 */
	virtual ~Clip() {}


	/**
	 * @brief Ŭ���� ���� �������Դϴ�.
	 * 
	 * @param instance ���� ������ ������ �ν��Ͻ��Դϴ�.
	 * 
	 * @return ���� ������ ������ ��ü�� �����ڸ� ��ȯ�մϴ�.
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
	 * @brief Ŭ���� ���� �������Դϴ�.
	 *
	 * @param instance ���� ������ ������ �ν��Ͻ��Դϴ�.
	 *
	 * @return ���� ������ ������ ��ü�� �����ڸ� ��ȯ�մϴ�.
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
	 * @brief �ε����� �����ϴ� Ʈ���� ���� ID�� ����ϴ�.
	 * 
	 * @param index Ʈ���� ���� ID�� ���� �ε����Դϴ�.
	 * 
	 * @return �ε����� �����ϴ� Ʈ���� ���� ID�� ��ȯ�մϴ�.
	 */
	uint32_t GetBoneID(uint32_t index);


	/**
	 * @brief �ε����� �����ϴ� Ʈ���� ���� ID�� �����մϴ�.
	 * 
	 * @param index ������ Ʈ���� �ε����Դϴ�.
	 * @param boneID ������ ���� ID�Դϴ�.
	 */
	void SetBoneID(uint32_t index, uint32_t boneID);


	/**
	 * @brief Ʈ���� ũ�⸦ ����ϴ�.
	 * 
	 * @return Ʈ���� ũ�⸦ ��ȯ�մϴ�.
	 */
	uint32_t Size() const { return static_cast<uint32_t>(tracks_.size()); }


	/**
	 * @brief Ŭ���� �̸��� ����ϴ�.
	 * 
	 * @return Ŭ���� �̸� ���� ��ȯ�մϴ�.
	 */
	const std::string& GetName() const { return name_; }


	/**
	 * @brief Ŭ���� �̸��� �����մϴ�.
	 * 
	 * @param name ������ Ŭ���� �̸��Դϴ�.
	 */
	void SetName(const std::string& name) { name_ = name; }

	
	/**
	 * @brief Ŭ���� ���� �ð� ���� ����ϴ�.
	 * 
	 * @return Ŭ���� ���� �ð� ���� ��ȯ�մϴ�.
	 */
	float GetDuration() { endTime_ - startTime_; }


	/**
	 * @brief Ŭ���� ���� �ð� ���� ����ϴ�.
	 * 
	 * @return Ŭ���� ���� �ð� ���� ��ȯ�մϴ�.
	 */
	float GetStartTime() { return startTime_; }


	/**
	 * @brief Ŭ���� ���� �ð� ���� ����ϴ�.
	 * 
	 * @return Ŭ���� ���� �ð� ���� ��ȯ�մϴ�.
	 */
	float GetEndTime() { return endTime_; }


	/**
	 * @brief Ŭ���� �ݺ� ���θ� ����ϴ�.
	 * 
	 * @return Ŭ���� �ݺ��ȴٸ� true, �׷��� ������ false�� ��ȯ�մϴ�.
	 */
	bool IsLooping() { return bIsLooping_; }


	/**
	 * @brief Ŭ���� �ݺ� ���θ� �����մϴ�.
	 * 
	 * @param bIsLooping ������ Ŭ���� �ݺ� �����Դϴ�.
	 */
	void SetLooping(bool bIsLooping) { bIsLooping_ = bIsLooping; }


	/**
	 * @brief ���� ID ���� �����ϴ� Ʈ������ Ʈ���� ����ϴ�.
	 * 
	 * @param boneID Ʈ������ Ʈ���� ���� ���� ID ���Դϴ�.
	 * 
	 * @return ���� ID ���� �����ϴ� Ʈ������ Ʈ���Դϴ�.
	 */
	TransformTrack& operator[](uint32_t boneID);

	
private:
	/**
	 * @brief Ŭ�� ���� Ʈ������ Ʈ���Դϴ�.
	 */
	std::vector<TransformTrack> tracks_;


	/**
	 * @brief Ŭ���� �̸��Դϴ�.
	 */
	std::string name_ = "empty";


	/**
	 * @brief Ŭ���� ���� �ð��Դϴ�.
	 */
	float startTime_ = 0.0f;


	/**
	 * @brief Ŭ���� ���� �ð��Դϴ�.
	 */
	float endTime_ = 0.0f;


	/**
	 * @brief Ŭ���� �ݺ� �����Դϴ�.
	 */
	bool bIsLooping_ = true;
};