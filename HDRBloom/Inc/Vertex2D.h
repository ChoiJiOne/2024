#pragma once

#include "Vec2.h"
#include "Vec3.h"
#include "Vec4.h"


/**
 * @brief 2D ��ġ ������ ���� �����Դϴ�.
 */
struct VertexPosition2D
{
	/**
	 * @brief 2D ��ġ ������ ���� ������ �⺻ �������Դϴ�.
	 */
	VertexPosition2D() noexcept : position(0.0f, 0.0f) {}


	/**
	 * @brief 2D ��ġ ������ ���� ������ �������Դϴ�.
	 *
	 * @param p ������ ��ġ�Դϴ�.
	 */
	VertexPosition2D(Vec2f&& p) noexcept : position(p) {}


	/**
	 * @brief 2D ��ġ ������ ���� ������ �������Դϴ�.
	 *
	 * @param p ������ ��ġ�Դϴ�.
	 */
	VertexPosition2D(const Vec2f& p) noexcept : position(p) {}


	/**
	 * @brief 2D ��ġ ������ ���� ������ �������Դϴ�.
	 *
	 * @param x ��ġ�� X��ǥ�Դϴ�.
	 * @param y ��ġ�� Y��ǥ�Դϴ�.
	 */
	VertexPosition2D(float x, float y) noexcept : position(x, y) {}


	/**
	 * @brief 2D ��ġ ������ ���� ������ �������Դϴ�.
	 *
	 * @param instance ������ ���� �ν��Ͻ��Դϴ�.
	 */
	VertexPosition2D(VertexPosition2D&& instance) noexcept
		: position(instance.position) {}


	/**
	 * @brief 2D ��ġ ������ ���� ������ �������Դϴ�.
	 *
	 * @param instance ������ ���� �ν��Ͻ��Դϴ�.
	 */
	VertexPosition2D(const VertexPosition2D& instance) noexcept
		: position(instance.position) {}


	/**
	 * @brief 2D ��ġ ������ ���� ������ ���� �������Դϴ�.
	 *
	 * @param instance ������ ���� �ν��Ͻ��Դϴ�.
	 *
	 * @return ������ ��ü�� �����ڸ� ��ȯ�մϴ�.
	 */
	VertexPosition2D& operator=(VertexPosition2D&& instance) noexcept
	{
		if (this == &instance) return *this;

		position = instance.position;

		return *this;
	}


	/**
	 * @brief 2D ��ġ ������ ���� ������ ���� �������Դϴ�.
	 *
	 * @param instance ������ ���� �ν��Ͻ��Դϴ�.
	 *
	 * @return ������ ��ü�� �����ڸ� ��ȯ�մϴ�.
	 */
	VertexPosition2D& operator=(const VertexPosition2D& instance) noexcept
	{
		if (this == &instance) return *this;

		position = instance.position;

		return *this;
	}


	/**
	 * @brief ������ ����Ʈ ���� ���� ����ϴ�.
	 *
	 * @return ������ ����Ʈ ����(Stride) ���� ��ȯ�մϴ�.
	 */
	static uint32_t GetStride()
	{
		return sizeof(VertexPosition2D);
	}


	/**
	 * @brief ������ ��ġ�Դϴ�.
	 */
	Vec2f position;
};