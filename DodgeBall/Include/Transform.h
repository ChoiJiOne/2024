#pragma once

#include "Matrix4x4.h"
#include "Vector3.h"


/**
 * @brief ���� �� ���� ������Ʈ�� ��ġ, ȸ��, ������(ũ��)�� �����մϴ�.
 * 
 * @see 
 * - https://docs.unrealengine.com/4.27/ko/Basics/Actors/Transform/
 * - https://learnopengl.com/Guest-Articles/2021/Scene/Scene-Graph
 */
class Transform
{
public:
	/**
	 * @brief ������Ʈ Ʈ�������� �⺻ �������Դϴ�.
	 */
	Transform() = default;


	/**
	 * @brief ������Ʈ Ʈ�������� �������Դϴ�.
	 * 
	 * @param location ������Ʈ�� ��ġ�Դϴ�.
	 * @param rotate ������Ʈ�� ȸ�� �����Դϴ�. ������ �����Դϴ�.
	 * @param scale ������Ʈ�� ũ���Դϴ�.
	 */
	Transform(const Vector3f& location, const Vector3f& rotate, const Vector3f& scale) 
		: location_(location)
		, rotate_(rotate)
		, scale_(scale)
	{
		ComputeWorldMatrix();
	}
	
	
	/**
	 * @brief ������Ʈ Ʈ�������� ���� �������Դϴ�.
	 * 
	 * @param instance ���� ������Ƽ�� ������ �ν��Ͻ��Դϴ�.
	 */
	Transform(Transform&& instance) noexcept
		: location_(instance.location_)
		, rotate_(instance.rotate_)
		, scale_(instance.scale_)
		, worldMatrix_(instance.worldMatrix_) {}


	/**
	 * @brief ������Ʈ Ʈ�������� ���� �������Դϴ�.
	 *
	 * @param instance ���� ������Ƽ�� ������ �ν��Ͻ��Դϴ�.
	 */
	Transform(const Transform& instance) noexcept
		: location_(instance.location_)
		, rotate_(instance.rotate_)
		, scale_(instance.scale_)
		, worldMatrix_(instance.worldMatrix_) {}


	/**
	 * ������Ʈ Ʈ�������� ���� �Ҹ����Դϴ�.
	 */
	virtual ~Transform() {}


	/**
	 * @brief ������Ʈ Ʈ�������� ���� �������Դϴ�.
	 * 
	 * @param instance ���� ������Ƽ�� ������ �ν��Ͻ��Դϴ�.
	 * 
	 * @return ������ ��ü�� �����ڸ� ��ȯ�մϴ�.
	 */
	Transform& operator=(Transform&& instance) noexcept
	{
		if (this == &instance) return *this;

		location_ = instance.location_;
		rotate_ = instance.rotate_;
		scale_ = instance.scale_;
		worldMatrix_ = instance.worldMatrix_;

		return *this;
	}


	/**
	 * @brief ������Ʈ Ʈ�������� ���� �������Դϴ�.
	 *
	 * @param instance ���� ������Ƽ�� ������ �ν��Ͻ��Դϴ�.
	 *
	 * @return ������ ��ü�� �����ڸ� ��ȯ�մϴ�.
	 */
	Transform& operator=(const Transform& instance) noexcept
	{
		if (this == &instance) return *this;

		location_ = instance.location_;
		rotate_ = instance.rotate_;
		scale_ = instance.scale_;
		worldMatrix_ = instance.worldMatrix_;

		return *this;
	}


	/**
	 * @brief ������Ʈ�� ��ġ�� ����ϴ�.
	 * 
	 * @return ������Ʈ�� ��ġ���� ��ȯ�մϴ�.
	 */
	Vector3f GetLocation() { return location_; }


	/**
	 * @brief ������Ʈ�� ��ġ�� ����ϴ�.
	 *
	 * @return ������Ʈ�� ��ġ���� ��ȯ�մϴ�.
	 */
	const Vector3f& GetLocation() const { return location_; }


	/**
	 * @brief ������Ʈ�� ȸ�� ���� ����ϴ�.
	 * 
	 * @return ������Ʈ�� ȸ�� ���� ��ȯ�մϴ�.
	 */
	Vector3f GetRotate() { return rotate_; }


	/**
	 * @brief ������Ʈ�� ȸ�� ���� ����ϴ�.
	 *
	 * @return ������Ʈ�� ȸ�� ���� ��ȯ�մϴ�.
	 */
	const Vector3f& GetRotate() const { return rotate_; }


	/**
	 * @brief ������Ʈ�� ũ�� ���� ����ϴ�.
	 * 
	 * @return ������Ʈ�� ũ�� ���� ��ȯ�մϴ�.
	 */
	Vector3f GetScale() { return scale_; }


	/**
	 * @brief ������Ʈ�� ũ�� ���� ����ϴ�.
	 *
	 * @return ������Ʈ�� ũ�� ���� ��ȯ�մϴ�.
	 */
	const Vector3f& GetScale() const { return scale_; }


	/**
	 * @brief ������Ʈ�� ���� ��� ���� ����ϴ�.
	 * 
	 * @return ������Ʈ�� ���� ��� ���� ��ȯ�մϴ�.
	 */
	Matrix4x4f GetWorldMatrix() { return worldMatrix_; }


	/**
	 * @brief ������Ʈ�� ���� ��� ���� ����ϴ�.
	 *
	 * @return ������Ʈ�� ���� ��� ���� ��ȯ�մϴ�.
	 */
	const Matrix4x4f& GetWorldMatrix() const { return worldMatrix_; }


	/**
	 * @brief ������Ʈ�� ��ġ�� �����մϴ�.
	 * 
	 * @param location ������ ������Ʈ�� ��ġ ���Դϴ�.
	 */
	void SetLocation(const Vector3f& location);


	/**
	 * @brief ������Ʈ�� ȸ�� ���� �����մϴ�.
	 * 
	 * @param rotate ������ ������Ʈ�� ȸ�� ���Դϴ�.
	 */
	void SetRotate(const Vector3f& rotate);


	/**
	 * @brief ������Ʈ�� ������ ���� �����մϴ�.
	 * 
	 * @param scale ������ ������Ʈ�� ������ ���Դϴ�.
	 */
	void SetScale(const Vector3f& scale);


	/**
	 * @brief ������Ʈ�� ��ġ, ȸ��, ũ�� ���� �����մϴ�.
	 * 
	 * @param location ������Ʈ�� ��ġ�Դϴ�.
	 * @param rotate ������Ʈ�� ȸ�� �����Դϴ�. ������ �����Դϴ�.
	 * @param scale ������Ʈ�� ũ���Դϴ�.
	 */
	void SetProperties(const Vector3f& location, const Vector3f& rotate, const Vector3f& scale);


private:
	/**
	 * @brief ���� ����� ����մϴ�.
	 */
	void ComputeWorldMatrix();


private:
	/**
	 * @brief ������Ʈ�� ��ġ�Դϴ�.
	 */
	Vector3f location_;


	/**
	 * @brief ������Ʈ�� ȸ�� �����Դϴ�. ������ �����Դϴ�.
	 */
	Vector3f rotate_;


	/**
	 * @brief ������Ʈ�� ũ���Դϴ�.
	 */
	Vector3f scale_;


	/**
	 * @brief ������Ʈ�� ��ġ*ȸ��*ũ�� ���� ����� ���� ����Դϴ�.
	 */
	Matrix4x4f worldMatrix_;
};