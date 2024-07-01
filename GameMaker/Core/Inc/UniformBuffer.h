#pragma once

#include <cstdint>

#include "IResource.h"


namespace GameMaker
{
/**
 * @brief ������ �����Դϴ�.
 */
class UniformBuffer
{
public:
	/**
	 * @brief ������ ������ ��� �����Դϴ�.
	 *
	 * @see https://registry.khronos.org/OpenGL-Refpages/gl2.1/xhtml/glBufferData.xml
	 */
	enum class EUsage
	{
		STREAM  = 0x88E0,
		STATIC  = 0x88E4,
		DYNAMIC = 0x88E8,
	};
};

}