#pragma once

#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"


/**
 * @brief ��ġ ������ ���� ����(Vertex)�Դϴ�.
 */
struct VertexPosition
{
	/**
	 * @brief ��ġ ������ ���� ������ �⺻ �������Դϴ�.
	 */
	VertexPosition() noexcept
		: position(0.0f, 0.0f, 0.0f) {}


	/**
	 * @brief ��ġ ������ ���� ������ �������Դϴ�.
	 *
	 * @param p ������ ��ġ�Դϴ�.
	 */
	VertexPosition(Vector3f&& p) noexcept
		: position(p) {}


	/**
	 * @brief ��ġ ������ ���� ������ �������Դϴ�.
	 *
	 * @param p ������ ��ġ�Դϴ�.
	 */
	VertexPosition(const Vector3f& p) noexcept
		: position(p) {}


	/**
	 * @brief ��ġ ������ ���� ������ �������Դϴ�.
	 *
	 * @param x ��ġ�� X��ǥ�Դϴ�.
	 * @param y ��ġ�� Y��ǥ�Դϴ�.
	 * @param z ��ġ�� Z��ǥ�Դϴ�.
	 */
	VertexPosition(float x, float y, float z) noexcept
		: position(x, y, z) {}


	/**
	 * @brief ��ġ ������ ���� ������ �������Դϴ�.
	 *
	 * @param instance ������ ���� �ν��Ͻ��Դϴ�.
	 */
	VertexPosition(VertexPosition&& instance) noexcept
		: position(instance.position) {}


	/**
	 * @brief ��ġ ������ ���� ������ �������Դϴ�.
	 *
	 * @param instance ������ ���� �ν��Ͻ��Դϴ�.
	 */
	VertexPosition(const VertexPosition& instance) noexcept
		: position(instance.position) {}


	/**
	 * @brief ��ġ ������ ���� ������ ���� �������Դϴ�.
	 *
	 * @param instance ������ ���� �ν��Ͻ��Դϴ�.
	 *
	 * @return ������ ��ü�� �����ڸ� ��ȯ�մϴ�.
	 */
	VertexPosition& operator=(VertexPosition&& instance) noexcept
	{
		if (this == &instance) return *this;

		position = instance.position;

		return *this;
	}


	/**
	 * @brief ��ġ ������ ���� ������ ���� �������Դϴ�.
	 *
	 * @param instance ������ ���� �ν��Ͻ��Դϴ�.
	 *
	 * @return ������ ��ü�� �����ڸ� ��ȯ�մϴ�.
	 */
	VertexPosition& operator=(const VertexPosition& instance) noexcept
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
		return sizeof(VertexPosition);
	}


	/**
	 * @brief ������ ��ġ�Դϴ�.
	 */
	Vector3f position;
};


/**
 * @brief ��ġ�� ���� ������ ���� ����(Vertex)�Դϴ�.
 */
struct VertexPositionColor
{
	/**
	 * @brief ��ġ�� ���� ������ ���� ������ �⺻ �������Դϴ�.
	 */
	VertexPositionColor() noexcept
		: position(0.0f, 0.0f, 0.0f)
		, color(0.0f, 0.0f, 0.0f, 0.0f) {}


	/**
	 * @brief ��ġ�� ���� ������ ���� ������ �������Դϴ�.
	 *
	 * @param p ������ ��ġ�Դϴ�.
	 * @param c ������ �����Դϴ�.
	 */
	VertexPositionColor(Vector3f&& p, Vector4f&& c) noexcept
		: position(p)
		, color(c) {}


	/**
	 * @brief ��ġ�� ���� ������ ���� ������ �������Դϴ�.
	 *
	 * @param p ������ ��ġ�Դϴ�.
	 * @param c ������ �����Դϴ�.
	 */
	VertexPositionColor(const Vector3f& p, const Vector4f& c) noexcept
		: position(p)
		, color(c) {}


	/**
	 * @brief ��ġ�� ���� ������ ���� ������ �������Դϴ�.
	 *
	 * @param x ��ġ�� X��ǥ�Դϴ�.
	 * @param y ��ġ�� Y��ǥ�Դϴ�.
	 * @param z ��ġ�� Z��ǥ�Դϴ�.
	 * @param r ���� ������ R�Դϴ�.
	 * @param g ���� ������ G�Դϴ�.
	 * @param b ���� ������ B�Դϴ�.
	 * @param a ���� ������ A�Դϴ�.
	 */
	VertexPositionColor(
		float x, float y, float z,
		float r, float g, float b, float a
	) noexcept
		: position(x, y, z)
		, color(r, g, b, a) {}


	/**
	 * @brief ��ġ�� ���� ������ ���� ������ �������Դϴ�.
	 *
	 * @param instance ������ ���� �ν��Ͻ��Դϴ�.
	 */
	VertexPositionColor(VertexPositionColor&& instance) noexcept
		: position(instance.position)
		, color(instance.color) {}


	/**
	 * @brief ��ġ�� ���� ������ ���� ������ �������Դϴ�.
	 *
	 * @param instance ������ ���� �ν��Ͻ��Դϴ�.
	 */
	VertexPositionColor(const VertexPositionColor& instance) noexcept
		: position(instance.position)
		, color(instance.color) {}


	/**
	 * @brief ��ġ�� ���� ������ ���� ������ ���� �������Դϴ�.
	 *
	 * @param instance ������ ���� �ν��Ͻ��Դϴ�.
	 *
	 * @return ������ ��ü�� �����ڸ� ��ȯ�մϴ�.
	 */
	VertexPositionColor& operator=(VertexPositionColor&& instance) noexcept
	{
		if (this == &instance) return *this;

		position = instance.position;
		color = instance.color;

		return *this;
	}


	/**
	 * @brief ��ġ�� ���� ������ ���� ������ ���� �������Դϴ�.
	 *
	 * @param instance ������ ���� �ν��Ͻ��Դϴ�.
	 *
	 * @return ������ ��ü�� �����ڸ� ��ȯ�մϴ�.
	 */
	VertexPositionColor& operator=(const VertexPositionColor& instance) noexcept
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
		return sizeof(VertexPositionColor);
	}


	/**
	 * @brief ������ ��ġ�Դϴ�.
	 */
	Vector3f position;


	/**
	 * @brief ������ �����Դϴ�.
	 */
	Vector4f color;
};


/**
 * @brief ��ġ�� �ؽ�ó ������ ���� ����(Vertex)�Դϴ�.
 */
struct VertexPositionTexture
{
	/**
	 * @brief ��ġ�� �ؽ�ó ������ ���� ������ �⺻ �������Դϴ�.
	 */
	VertexPositionTexture() noexcept
		: position(0.0f, 0.0f, 0.0f)
		, texture(0.0f, 0.0f) {}


	/**
	 * @brief ��ġ�� �ؽ�ó ������ ���� ������ �������Դϴ�.
	 *
	 * @param p ������ ��ġ�Դϴ�.
	 * @param uv ������ �ؽ�ó ��ġ�Դϴ�.
	 */
	VertexPositionTexture(Vector3f&& p, Vector2f&& uv) noexcept
		: position(p)
		, texture(uv) {}


	/**
	 * @brief ��ġ�� �ؽ�ó ������ ���� ������ �������Դϴ�.
	 *
	 * @param p ������ ��ġ�Դϴ�.
	 * @param uv ������ �ؽ�ó ��ġ�Դϴ�.
	 */
	VertexPositionTexture(const Vector3f& p, const Vector2f& uv) noexcept
		: position(p)
		, texture(uv) {}


	/**
	 * @brief ��ġ�� �ؽ�ó ������ ���� ������ �������Դϴ�.
	 *
	 * @param x ��ġ�� X��ǥ�Դϴ�.
	 * @param y ��ġ�� Y��ǥ�Դϴ�.
	 * @param z ��ġ�� Z��ǥ�Դϴ�.
	 * @param u �ؽ�ó ��ġ�� U��ǥ�Դϴ�.
	 * @param v �ؽ�ó ��ġ�� V��ǥ�Դϴ�.
	 */
	VertexPositionTexture(
		float x, float y, float z,
		float u, float v
	) noexcept
		: position(x, y, z)
		, texture(u, v) {}


	/**
	 * @brief ��ġ�� �ؽ�ó ������ ���� ������ �������Դϴ�.
	 *
	 * @param instance ������ ���� �ν��Ͻ��Դϴ�.
	 */
	VertexPositionTexture(VertexPositionTexture&& instance) noexcept
		: position(instance.position)
		, texture(instance.texture) {}


	/**
	 * @brief ��ġ�� �ؽ�ó ������ ���� ������ �������Դϴ�.
	 *
	 * @param instance ������ ���� �ν��Ͻ��Դϴ�.
	 */
	VertexPositionTexture(const VertexPositionTexture& instance) noexcept
		: position(instance.position)
		, texture(instance.texture) {}


	/**
	 * @brief ��ġ�� �ؽ�ó ������ ���� ������ ���� �������Դϴ�.
	 *
	 * @param instance ������ ���� �ν��Ͻ��Դϴ�.
	 *
	 * @return ������ ��ü�� �����ڸ� ��ȯ�մϴ�.
	 */
	VertexPositionTexture& operator=(VertexPositionTexture&& instance) noexcept
	{
		if (this == &instance) return *this;

		position = instance.position;
		texture = instance.texture;

		return *this;
	}


	/**
	 * @brief ��ġ�� �ؽ�ó ������ ���� ������ ���� �������Դϴ�.
	 *
	 * @param instance ������ ���� �ν��Ͻ��Դϴ�.
	 *
	 * @return ������ ��ü�� �����ڸ� ��ȯ�մϴ�.
	 */
	VertexPositionTexture& operator=(const VertexPositionTexture& instance) noexcept
	{
		if (this == &instance) return *this;

		position = instance.position;
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
		return sizeof(VertexPositionTexture);
	}


	/**
	 * @brief ������ ��ġ�Դϴ�.
	 */
	Vector3f position;


	/**
	 * @brief ������ �ؽ�ó ��ǥ�Դϴ�.
	 */
	Vector2f texture;
};


/**
 * @brief ��ġ�� ���� ������ ���� ����(Vertex)�Դϴ�.
 */
struct VertexPositionNormal
{
	/**
	 * @brief ��ġ�� ���� ������ ���� ������ �⺻ �������Դϴ�.
	 */
	VertexPositionNormal() noexcept
		: position(0.0f, 0.0f, 0.0f)
		, normal(0.0f, 0.0f, 0.0f) {}


	/**
	 * @brief ��ġ�� ���� ������ ���� ������ �������Դϴ�.
	 *
	 * @param p ������ ��ġ�Դϴ�.
	 * @param n ������ �����Դϴ�.
	 */
	VertexPositionNormal(Vector3f&& p, Vector3f&& n) noexcept
		: position(p)
		, normal(n) {}


	/**
	 * @brief ��ġ�� ���� ������ ���� ������ �������Դϴ�.
	 *
	 * @param p ������ ��ġ�Դϴ�.
	 * @param n ������ �����Դϴ�.
	 */
	VertexPositionNormal(const Vector3f& p, const Vector3f& n) noexcept
		: position(p)
		, normal(n) {}


	/**
	 * @brief ��ġ�� ���� ������ ���� ������ �������Դϴ�.
	 *
	 * @param x ��ġ�� X��ǥ�Դϴ�.
	 * @param y ��ġ�� Y��ǥ�Դϴ�.
	 * @param z ��ġ�� Z��ǥ�Դϴ�.
	 * @param nx ������ X��ǥ�Դϴ�.
	 * @param ny ������ Y��ǥ�Դϴ�.
	 * @param nz ������ Z��ǥ�Դϴ�.
	 */
	VertexPositionNormal(
		float x, float y, float z,
		float nx, float ny, float nz
	) noexcept
		: position(x, y, z)
		, normal(nx, ny, nz) {}


	/**
	 * @brief ��ġ�� ���� ������ ���� ������ �������Դϴ�.
	 *
	 * @param instance ������ ���� �ν��Ͻ��Դϴ�.
	 */
	VertexPositionNormal(VertexPositionNormal&& instance) noexcept
		: position(instance.position)
		, normal(instance.normal) {}


	/**
	 * @brief ��ġ�� ���� ������ ���� ������ �������Դϴ�.
	 *
	 * @param instance ������ ���� �ν��Ͻ��Դϴ�.
	 */
	VertexPositionNormal(const VertexPositionNormal& instance) noexcept
		: position(instance.position)
		, normal(instance.normal) {}


	/**
	 * @brief ��ġ�� ���� ������ ���� ������ ���� �������Դϴ�.
	 *
	 * @param instance ������ ���� �ν��Ͻ��Դϴ�.
	 *
	 * @return ������ ��ü�� �����ڸ� ��ȯ�մϴ�.
	 */
	VertexPositionNormal& operator=(VertexPositionNormal&& instance) noexcept
	{
		if (this == &instance) return *this;

		position = instance.position;
		normal = instance.normal;

		return *this;
	}


	/**
	 * @brief ��ġ�� ���� ������ ���� ������ ���� �������Դϴ�.
	 *
	 * @param instance ������ ���� �ν��Ͻ��Դϴ�.
	 *
	 * @return ������ ��ü�� �����ڸ� ��ȯ�մϴ�.
	 */
	VertexPositionNormal& operator=(const VertexPositionNormal& instance) noexcept
	{
		if (this == &instance) return *this;

		position = instance.position;
		normal = instance.normal;

		return *this;
	}


	/**
	 * @brief ������ ����Ʈ ���� ���� ����ϴ�.
	 *
	 * @return ������ ����Ʈ ����(Stride) ���� ��ȯ�մϴ�.
	 */
	static uint32_t GetStride()
	{
		return sizeof(VertexPositionNormal);
	}


	/**
	 * @brief ������ ��ġ�Դϴ�.
	 */
	Vector3f position;


	/**
	 * @brief ������ ���� ��ǥ�Դϴ�.
	 */
	Vector3f normal;
};