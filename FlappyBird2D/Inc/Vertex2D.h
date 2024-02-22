#pragma once

#include "Vec2.h"
#include "Vec3.h"
#include "Vec4.h"


/**
 * @brief 2D ��ġ�� ���� ������ ���� �����Դϴ�.
 */
struct VertexPositionColor2D
{
	/**
	 * @brief 2D ��ġ�� ���� ������ ���� ������ �⺻ �������Դϴ�.
	 */
	VertexPositionColor2D() noexcept 
		: position(0.0f, 0.0f)
		, color(0.0f, 0.0f, 0.0f, 0.0f) {}


	/**
	 * @brief 2D ��ġ�� ���� ������ ���� ������ �������Դϴ�.
	 *
	 * @param p ������ ��ġ�Դϴ�.
	 * @param c ������ �����Դϴ�.
	 */
	VertexPositionColor2D(Vec2f&& p, Vec4f&& c) noexcept
		: position(p)
		, color(c) {}


	/**
	 * @brief 2D ��ġ�� ���� ������ ���� ������ �������Դϴ�.
	 *
	 * @param p ������ ��ġ�Դϴ�.
	 * @param c ������ �����Դϴ�.
	 */
	VertexPositionColor2D(const Vec2f& p, const Vec4f& c) noexcept
		: position(p)
		, color(c) {}


	/**
	 * @brief 2D ��ġ�� ���� ������ ���� ������ �������Դϴ�.
	 *
	 * @param x ��ġ�� X��ǥ�Դϴ�.
	 * @param y ��ġ�� Y��ǥ�Դϴ�.
	 * @param r ���� ������ R�Դϴ�.
	 * @param g ���� ������ G�Դϴ�.
	 * @param b ���� ������ B�Դϴ�.
	 * @param a ���� ������ A�Դϴ�.
	 */
	VertexPositionColor2D(
		float x, float y, float z,
		float r, float g, float b, float a
	) noexcept
		: position(x, y)
		, color(r, g, b, a) {}


	/**
	 * @brief 2D ��ġ�� ���� ������ ���� ������ �������Դϴ�.
	 *
	 * @param instance ������ ���� �ν��Ͻ��Դϴ�.
	 */
	VertexPositionColor2D(VertexPositionColor2D&& instance) noexcept
		: position(instance.position)
		, color(instance.color) {}


	/**
	 * @brief 2D ��ġ�� ���� ������ ���� ������ �������Դϴ�.
	 *
	 * @param instance ������ ���� �ν��Ͻ��Դϴ�.
	 */
	VertexPositionColor2D(const VertexPositionColor2D& instance) noexcept
		: position(instance.position)
		, color(instance.color) {}


	/**
	 * @brief 2D ��ġ�� ���� ������ ���� ������ ���� �������Դϴ�.
	 *
	 * @param instance ������ ���� �ν��Ͻ��Դϴ�.
	 *
	 * @return ������ ��ü�� �����ڸ� ��ȯ�մϴ�.
	 */
	VertexPositionColor2D& operator=(VertexPositionColor2D&& instance) noexcept
	{
		if (this == &instance) return *this;

		position = instance.position;
		color = instance.color;

		return *this;
	}


	/**
	 * @brief 2D ��ġ�� ���� ������ ���� ������ ���� �������Դϴ�.
	 *
	 * @param instance ������ ���� �ν��Ͻ��Դϴ�.
	 *
	 * @return ������ ��ü�� �����ڸ� ��ȯ�մϴ�.
	 */
	VertexPositionColor2D& operator=(const VertexPositionColor2D& instance) noexcept
	{
		if (this == &instance) return *this;

		position = instance.position;
		color = instance.color;

		return *this;
	}


	/**
	 * @brief ������ ����Ʈ ���� ���� ����ϴ�.
	 *
	 * @return ������ ����Ʈ ����(Stride) ���� ��ȯ�մϴ�.
	 */
	static uint32_t GetStride()
	{
		return sizeof(VertexPositionColor2D);
	}


	/**
	 * @brief ������ ��ġ�Դϴ�.
	 */
	Vec2f position;


	/**
	 * @brief ������ �����Դϴ�.
	 */
	Vec4f color;
};