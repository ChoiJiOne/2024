#pragma once

#include "Transform.h"

#include "Track.h"


/**
 * @brief ����� ���� Ʈ��(Transform Track)�Դϴ�.
 * 
 * @note �� ���� Ʈ���� �� ���� Ʈ��(��ġ, ȸ��, ������)�� ĸ��ȭ�մϴ�.
 */
class TransformTrack
{
public:
	/**
	 * @brief ����� ���� Ʈ��(Transform Track)�� �⺻ �������Դϴ�
	 */
	TransformTrack() = default;


	/**
	 * @brief ����� ���� Ʈ��(Transform Track)�� ���� �������Դϴ�.
	 * 
	 * @param instance ������ �ν��Ͻ��Դϴ�.
	 */
	TransformTrack(TransformTrack&& instance) noexcept
		: boneID_(instance.boneID_)
		, position_(instance.position_)
		, rotate_(instance.rotate_)
		, scale_(instance.scale_) 
	{
		position_ = instance.position_;

	}


	/**
	 * @brief ����� ���� Ʈ��(Transform Track)�� ���� �������Դϴ�.
	 *
	 * @param instance ������ �ν��Ͻ��Դϴ�.
	 */
	TransformTrack(const TransformTrack& instance) noexcept
		: boneID_(instance.boneID_)
		, position_(instance.position_)
		, rotate_(instance.rotate_)
		, scale_(instance.scale_) {}


	/**
	 * @brief ����� ���� Ʈ��(Transform Track)�� ���� �Ҹ����Դϴ�
	 */
	virtual ~TransformTrack() {}


	/**
	 * @brief ����� ���� Ʈ���� ���� �������Դϴ�.
	 *
	 * @param instance ���� ������ ������ �ν��Ͻ��Դϴ�.
	 *
	 * @return ���� ������ ������ ��ü�� �����ڸ� ��ȯ�մϴ�.
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
	 * @brief ����� ���� Ʈ���� ���� �������Դϴ�.
	 *
	 * @param instance ���� ������ ������ �ν��Ͻ��Դϴ�.
	 *
	 * @return ���� ������ ������ ��ü�� �����ڸ� ��ȯ�մϴ�.
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
	 * @brief ���� ID�� ����ϴ�.
	 * 
	 * @return ���� ID�� ��ȯ�մϴ�.
	 */
	uint32_t GetBoneID() const { return boneID_; }


	/**
	 * @brief ���� ID�� �����մϴ�.
	 * 
	 * @param boneID ������ ���� ID�Դϴ�.
	 */
	void SetBoneID(uint32_t boneID) { boneID_ = boneID; }


	/**
	 * @brief ��ġ Ʈ���� �����ڸ� ����ϴ�.
	 * 
	 * @return ��ġ Ʈ���� �����ڸ� ��ȯ�մϴ�.
	 */
	VectorTrack& GetPositionTrack() { return position_; }


	/**
	 * @brief ��ġ Ʈ���� ��� �����ڸ� ����ϴ�.
	 *
	 * @return ��ġ Ʈ���� ��� �����ڸ� ��ȯ�մϴ�.
	 */
	const VectorTrack& GetPositionTrack() const { return position_; }


	/**
	 * @brief ȸ�� Ʈ���� �����ڸ� ����ϴ�.
	 * 
	 * @return ȸ�� Ʈ���� �����ڸ� ��ȯ�մϴ�.
	 */
	QuaternionTrack& GetRotateTrack() { return rotate_; }


	/**
	 * @brief ȸ�� Ʈ���� ��� �����ڸ� ����ϴ�.
	 *
	 * @return ȸ�� Ʈ���� ��� �����ڸ� ��ȯ�մϴ�.
	 */
	const QuaternionTrack& GetRotateTrack() const { return rotate_; }


	/**
	 * @brief ������ Ʈ���� �����ڸ� ����ϴ�.
	 * 
	 * @return ������ Ʈ���� �����ڸ� ��ȯ�մϴ�.
	 */
	VectorTrack& GetScaleTrack() { return scale_; }


	/**
	 * @brief ������ Ʈ���� ��� �����ڸ� ����ϴ�.
	 *
	 * @return ������ Ʈ���� ��� �����ڸ� ��ȯ�մϴ�.
	 */
	const VectorTrack& GetScaleTrack() const { return scale_; }


	/**
	 * @brief ����� ���� Ʈ���� ��ȿ���� Ȯ���մϴ�.
	 * 
	 * @return ����� ���� Ʈ���� ��ȿ�ϴٸ� true, �׷��� ������ false�� ��ȯ�մϴ�.
	 */
	bool IsValid();
	

private:
	/**
	 * @brief ���� ID�Դϴ�.
	 */
	uint32_t boneID_ = 0;


	/**
	 * @brief ��ġ Ʈ���Դϴ�.
	 */
	VectorTrack position_;


	/**
	 * @brief ȸ�� Ʈ���Դϴ�.
	 */
	QuaternionTrack rotate_;


	/**
	 * @brief ������ Ʈ���Դϴ�.
	 */
	VectorTrack scale_;
};