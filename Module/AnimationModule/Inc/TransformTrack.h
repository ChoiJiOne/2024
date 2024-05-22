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
	

private:
	/**
	 * @brief ���� ID�Դϴ�.
	 */
	uint32_t boneID_;


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