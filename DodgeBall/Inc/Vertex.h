#pragma once

#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"

/**
 * @brief ����(Vertex)�Դϴ�.
 */
struct Vertex
{
	/**
	 * @brief ��ġ ������ ���� ������ �⺻ �������Դϴ�.
	 */
	Vertex() noexcept
		: position(0.0f, 0.0f, 0.0f)
		, normal(0.0f, 0.0f, 0.0f)
		, texture(0.0f, 0.0f) {}


	/**
	 * @brief ��ġ ������ ���� ������ �������Դϴ�.
	 *
	 * @param p ������ ��ġ�Դϴ�.
	 * @param n ������ ���� �����Դϴ�.
	 * @param uv ������ �ؼ��Դϴ�.
	 */
	Vertex(Vector3f&& p, Vector3f&& n, Vector2f&& uv) noexcept
		: position(p)
		, normal(n)
		, texture(uv) {}


	/**
	 * @brief ��ġ ������ ���� ������ �������Դϴ�.
	 *
	 * @param p ������ ��ġ�Դϴ�.
	 * @param n ������ ���� �����Դϴ�.
	 * @param uv ������ �ؼ��Դϴ�.
	 */
	Vertex(const Vector3f& p, const Vector3f& n, const Vector2f& uv) noexcept
		: position(p)
		, normal(n)
		, texture(uv) {}


	/**
	 * @brief ��ġ ������ ���� ������ �������Դϴ�.
	 *
	 * @param instance ������ ���� �ν��Ͻ��Դϴ�.
	 */
	Vertex(Vertex&& instance) noexcept
		: position(instance.position)
		, normal(instance.normal)
		, texture(instance.texture) {}


	/**
	 * @brief ��ġ ������ ���� ������ �������Դϴ�.
	 *
	 * @param instance ������ ���� �ν��Ͻ��Դϴ�.
	 */
	Vertex(const Vertex& instance) noexcept
		: position(instance.position)
		, normal(instance.normal)
		, texture(instance.texture) {}


	/**
	 * @brief ��ġ ������ ���� ������ ���� �������Դϴ�.
	 *
	 * @param instance ������ ���� �ν��Ͻ��Դϴ�.
	 *
	 * @return ������ ��ü�� �����ڸ� ��ȯ�մϴ�.
	 */
	Vertex& operator=(Vertex&& instance) noexcept
	{
		if (this == &instance) return *this;

		position = instance.position;
		normal = instance.normal;
		texture = instance.texture;

		return *this;
	}


	/**
	 * @brief ��ġ ������ ���� ������ ���� �������Դϴ�.
	 *
	 * @param instance ������ ���� �ν��Ͻ��Դϴ�.
	 *
	 * @return ������ ��ü�� �����ڸ� ��ȯ�մϴ�.
	 */
	Vertex& operator=(const Vertex& instance) noexcept
	{
		if (this == &instance) return *this;

		position = instance.position;
		normal = instance.normal;
		texture = instance.texture;

		return *this;
	}


	/**
	 * @brief ������ ����Ʈ ���� ���� ����ϴ�.
	 *
	 * @return ������ ����Ʈ ����(Stride) ���� ��ȯ�մϴ�.
	 */
	static uint32_t GetStride()
	{
		return sizeof(Vertex);
	}


	/**
	 * @brief ������ ��ġ�Դϴ�.
	 */
	Vector3f position;


	/**
	 * @brief ������ ���� �����Դϴ�.
	 */
	Vector3f normal;


	/**
	 * @brief ������ �ؼ��Դϴ�.
	 */
	Vector2f texture;
};