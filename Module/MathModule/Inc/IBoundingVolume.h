#pragma once

#include <cstdint>


/**
 * @brief 충돌 가능한 3D 경계 볼룸 인터페이스입니다.
 * 
 * @note 충돌 가능한 3D 경계 볼륨은 이 인터페이스를 반드시 상속 받아야 합니다.
 */
class IBoundingVolume
{
public:
	/**
	 * @brief 3D 경계 볼륨의 종류입니다.
	 */
	enum class EType : int32_t
	{
		NONE   = 0x00,
		BOX    = 0x01,
		SPHERE = 0x02,
	};


public:
	/**
	 * @brief 충돌 가능한 3D 경계 볼룸 인터페이스의 기본 생성자입니다.
	 */
	IBoundingVolume() = default;


	/**
	 * @brief 충돌 가능한 3D 경계 볼룸 인터페이스의 가상 소멸자입니다.
	 */
	virtual ~IBoundingVolume() {}


	/**
	 * @brief 3D 경계 볼륨의 종류를 얻습니다.
	 *
	 * @return  3D 경계 볼륨의 종류를 반환합니다.
	 */
	virtual EType GetType() const = 0;


	/**
	 * @brief 다른 3D 경계 볼륨과 충돌하는지 확인합니다.
	 *
	 * @param boundingVolume 검출을 확인할 3D 경계 볼륨입니다.
	 *
	 * @return 다른 3D 경계와 충돌한다면 true, 그렇지 않으면 false를 반환합니다.
	 */
	virtual bool Intersect(const IBoundingVolume* boundVolume) const = 0;
};