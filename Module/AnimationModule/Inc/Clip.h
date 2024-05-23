#pragma once

#include <string>

#include "TransformTrack.h"


/**
 * @brief 애니메이션 트랙의 모음인 클립(Clip)입니다.
 */
class Clip
{
public:


private:
	/**
	 * @brief 클립 내의 트랜스폼 트랙입니다.
	 */
	std::vector<TransformTrack> tracks_;


	/**
	 * @brief 클립의 이름입니다.
	 */
	std::string name_;


	/**
	 * @brief 클립의 시작 시간입니다.
	 */
	float startTime_ = 0.0f;


	/**
	 * @brief 클립의 종료 시간입니다.
	 */
	float endTime_ = 0.0f;


	/**
	 * @brief 클립의 반복 여부입니다.
	 */
	bool bIsLooping_ = false;
};