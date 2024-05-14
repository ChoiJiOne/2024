#pragma once

#include "IBoundingVolume.h"
#include "Vec3.h"


/**
 * @brief 경계 구(Sphere)입니다.
 */
class BoundingSphere3D : public IBoundingVolume
{
public:
	/**
	 * @brief 경계 구의 기본 생성자입니다.
	 */
	BoundingSphere3D() = default;


	/**
	 * @brief 경계 구의 생성자입니다.
	 *
	 * @param center 경계 구의 중심 좌표입니다.
	 * @param radius 경계 구의 반지름 길이입니다.
	 */
	BoundingSphere3D(const Vec3f& center, float radius)
		: center_(center)
		, radius_(radius) {}


	/**
	 * @brief 경계 구의 복사 생성자입니다.
	 *
	 * @param instance 내부 프로퍼티를 복사할 인스턴스입니다.
	 */
	BoundingSphere3D(BoundingSphere3D&& instance) noexcept
		: center_(instance.center_)
		, radius_(instance.radius_) {}


	/**
	 * @brief 경계 구의 복사 생성자입니다.
	 *
	 * @param instance 내부 프로퍼티를 복사할 인스턴스입니다.
	 */
	BoundingSphere3D(const BoundingSphere3D& instance) noexcept
		: center_(instance.center_)
		, radius_(instance.radius_) {}


	/**
	 * @brief 경계 구의 가상 소멸자입니다.
	 */
	virtual ~BoundingSphere3D() {}


	/**
	 * @brief 경계 구의 대입 연산자입니다.
	 *
	 * @param instance 내부 프로퍼티를 복사할 인스턴스입니다.
	 *
	 * @return 대입한 객체의 참조자를 반환합니다.
	 */
	BoundingSphere3D& operator=(BoundingSphere3D&& instance) noexcept
	{
		if (this == &instance) return *this;

		center_ = instance.center_;
		radius_ = instance.radius_;

		return *this;
	}


	/**
	 * @brief 경계 구의 대입 연산자입니다.
	 *
	 * @param instance 내부 프로퍼티를 복사할 인스턴스입니다.
	 *
	 * @return 대입한 객체의 참조자를 반환합니다.
	 */
	BoundingSphere3D& operator=(const BoundingSphere3D& instance) noexcept
	{
		if (this == &instance) return *this;

		center_ = instance.center_;
		radius_ = instance.radius_;

		return *this;
	}


	/**
	 * @brief 경계 구의 중심 좌표를 얻습니다.
	 *
	 * @return 경계 구의 중심 좌표를 반환합니다.
	 */
	const Vec3f& GetCenter() const { return center_; }


	/**
	 * @brief 경계 구의 반지름 길이를 얻습니다.
	 *
	 * @return 경계 구의 반지름 길이를 반환합니다.
	 */
	const float& GetRadius() const { return radius_; }


	/**
	 * @brief 경계 구의 중심 좌표를 설정합니다.
	 *
	 * @param center 설정할 경계 구의 중심좌표입니다.
	 */
	void SetCenter(const Vec3f& center) { center_ = center; }


	/**
	 * @brief 경계 구의 반지름 길이를 설정합니다.
	 *
	 * @param radius 설정할 경계 구의 반지름 길이입니다.
	 */
	void SetRadius(const float& radius) { radius_ = radius; }


	/**
	 * @brief 경계 구의 형태 열거형 값을 얻습니다.
	 *
	 * @return 경계 구의 형태 열거형 값을 반환합니다.
	 */
	virtual EType GetType() const override { return EType::SPHERE; }


	/**
	 * @brief 다른 3D 경계 볼륨과 충돌하는지 확인합니다.
	 *
	 * @param boundingVolume 검출을 확인할 3D 경계 볼륨입니다.
	 *
	 * @return 다른 3D 경계와 충돌한다면 true, 그렇지 않으면 false를 반환합니다.
	 */
	virtual bool Intersect(const IBoundingVolume* boundingVolume) const override;


private:
	/**
	 * @brief 다른 경계 축 정렬 상자와 충돌하는지 확인합니다.
	 *
	 * @param boundingVolume 검출을 확인할 3D 경계 볼륨입니다.
	 *
	 * @return 다른 경계 축 정렬 상자와 충돌한다면 true, 그렇지 않으면 false를 반환합니다.
	 */
	bool IntersectBoundingBox3D(const IBoundingVolume* boundingVolume) const;


	/**
	 * @brief 다른 구 영역과 충돌하는지 확인합니다.
	 *
	 * @param boundingVolume 검출을 확인할 3D 경계 볼륨입니다.
	 *
	 * @return 다른 구 영역과 충돌한다면 true, 그렇지 않으면 false를 반환합니다.
	 */
	bool IntersectBoundingSphere3D(const IBoundingVolume* boundingVolume) const;


private:
	/**
	 * @brief 경계 구의 중심 좌표입니다.
	 */
	Vec3f center_;


	/**
	 * @brief 경계 구의 반지름 길이입니다.
	 */
	float radius_;
};