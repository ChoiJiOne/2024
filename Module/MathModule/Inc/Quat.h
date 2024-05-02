#pragma once

#include "Mat4x4.h"
#include "MathModule.h"
#include "Vec3.h"


/**
 * @brief ���ʹϾ��Դϴ�.
 * 
 * @see 
 * - https://gabormakesgames.com/quaternions.html
 * - https://en.wikipedia.org/wiki/Quaternion
 * - https://github.com/mmp/pbrt-v3/blob/master/src/core/quaternion.h
 */
struct Quat
{
	/**
	 * @brief ���ʹϾ��� �پ��� ���� �����Դϴ�.
	 */
	union
	{
		struct
		{
			float x;
			float y;
			float z;
			float w;
		};
		struct 
		{
			Vec3f v;
			float w;
		};
		float data[4];
	};
};