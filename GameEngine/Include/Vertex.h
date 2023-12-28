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
		, texture(0.0f, 0.0f)
		, tangent(0.0f, 0.0f, 0.0f)
		, bitangent(0.0f, 0.0f, 0.0f)
		, color(0.0f, 0.0f, 0.0f, 0.0f) {}


	/**
	 * @brief ��ġ ������ ���� ������ �������Դϴ�.
	 *
	 * @param p ������ ��ġ�Դϴ�.
	 * @param n ������ ���� �����Դϴ�.
	 * @param uv ������ �ؼ��Դϴ�.
	 * @param t ������ ���� �����Դϴ�.
	 * @param b ������ �ֺ����Դϴ�.
	 * @param c ������ �����Դϴ�.
	 */
	Vertex(Vector3f&& p, Vector3f&& n, Vector2f&& uv, Vector3f&& t, Vector3f&& b, Vector4f&& c) noexcept
		: position(p) 
		, normal(n)
		, texture(uv)
		, tangent(t)
		, bitangent(b)
		, color(c) {}


	/**
	 * @brief ��ġ ������ ���� ������ �������Դϴ�.
	 *
	 * @param p ������ ��ġ�Դϴ�.
	 * @param n ������ ���� �����Դϴ�.
	 * @param uv ������ �ؼ��Դϴ�.
	 * @param t ������ ���� �����Դϴ�.
	 * @param b ������ �ֺ����Դϴ�.
	 * @param c ������ �����Դϴ�.
	 */
	Vertex(const Vector3f& p, const Vector3f& n, const Vector2f& uv, const Vector3f& t, const Vector3f& b, const Vector4f& c) noexcept
		: position(p)
		, normal(n)
		, texture(uv)
		, tangent(t)
		, bitangent(b)
		, color(c) {}

	
	/**
	 * @brief ��ġ ������ ���� ������ �������Դϴ�.
	 *
	 * @param instance ������ ���� �ν��Ͻ��Դϴ�.
	 */
	Vertex(Vertex&& instance) noexcept
		: position(instance.position)
		, normal(instance.normal)
		, texture(instance.texture)
		, tangent(instance.tangent)
		, bitangent(instance.bitangent)
		, color(instance.color) {}


	/**
	 * @brief ��ġ ������ ���� ������ �������Դϴ�.
	 *
	 * @param instance ������ ���� �ν��Ͻ��Դϴ�.
	 */
	Vertex(const Vertex& instance) noexcept
		: position(instance.position)
		, normal(instance.normal)
		, texture(instance.texture)
		, tangent(instance.tangent)
		, bitangent(instance.bitangent)
		, color(instance.color) {}


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
		tangent = instance.tangent;
		bitangent = instance.bitangent;
		color = instance.color;

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
		tangent = instance.tangent;
		bitangent = instance.bitangent;
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


	/**
	 * @brief ������ ���� �����Դϴ�.
	 */
	Vector3f tangent;


	/**
	 * @brief ������ �ֺ����Դϴ�.
	 */
	Vector3f bitangent;


	/**
	 * @brief ������ �����Դϴ�.
	 */
	Vector4f color;
};