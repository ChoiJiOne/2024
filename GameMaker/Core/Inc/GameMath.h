#pragma once

#include <cstdint>
#include <limits>


namespace GameMaker
{
	/**
	 * @brief ����(��) ���Դϴ�.
	 */
	const float PI = 3.141592654f;


	/**
	 * @brief 2����(2��) ���Դϴ�.
	 */
	const float TWO_PI = 6.283185307f;


	/**
	 * @brief ����(��) �� ���� ���Դϴ�.
	 */
	const float ONE_DIV_PI = 0.318309886f;


	/**
	 * @brief 2����(2��) �� ���� ���Դϴ�.
	 */
	const float ONE_DIV_2PI = 0.159154943f;


	/**
	 * @brief ����(��) �� �ݰ�(��/2)�Դϴ�.
	 */
	const float PI_DIV_2 = 1.570796327f;


	/**
	 * @brief ����(��) �� ���� �� ��(��/4)�Դϴ�.
	 */
	const float PI_DIV_4 = 0.785398163f;


	/**
	 * @brief ���Ƿ�(��) ���Դϴ�.
	 */
	const float EPSILON = 1.192092896e-07F;


	/**
	 * @brief ���� ���Ѵ� ���Դϴ�.
	 */
	const float INFINITY = std::numeric_limits<float>::infinity();


	/**
	 * @brief ���� ���Ѵ� ���Դϴ�.
	 */
	const float N_INFINITY = -std::numeric_limits<float>::infinity();
}