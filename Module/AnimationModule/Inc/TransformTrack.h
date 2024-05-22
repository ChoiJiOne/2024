#pragma once

#include "Transform.h"

#include "Track.h"


/**
 * @brief 고수준 변형 트랙(Transform Track)입니다.
 * 
 * @note 이 변형 트랙은 세 가지 트랙(위치, 회전, 스케일)을 캡슐화합니다.
 */
class TransformTrack
{
public:
	/**
	 * @brief 고수준 변형 트랙(Transform Track)의 기본 생성자입니다
	 */
	TransformTrack() = default;


	/**
	 * @brief 고수준 변형 트랙(Transform Track)의 가상 소멸자입니다
	 */
	virtual ~TransformTrack() {}
	

private:
	/**
	 * @brief 뼈대 ID입니다.
	 */
	uint32_t boneID_;


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