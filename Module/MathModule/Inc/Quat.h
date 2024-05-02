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