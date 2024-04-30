#pragma once

#include "Vec2.h"
#include "Vec3.h"
#include "Vec4.h"


/**
 * @brief 3D ��ġ ������ ���� �����Դϴ�.
 */
struct VertexPosition3D
{
	/**
	 * @brief 3D ��ġ ������ ���� ������ �⺻ �������Դϴ�.
	 */
	VertexPosition3D() noexcept : position(0.0f, 0.0f, 0.0f) {}


	/**
	 * @brief 3D ��ġ ������ ���� ������ �������Դϴ�.
	 *
	 * @param p ������ ��ġ�Դϴ�.
	 */
	VertexPosition3D(Vec3f&& p) noexcept : position(p) {}


	/**
	 * @brief 3D ��ġ ������ ���� ������ �������Դϴ�.
	 *
	 * @param p ������ ��ġ�Դϴ�.
	 */
	VertexPosition3D(const Vec3f& p) noexcept : position(p) {}


	/**
	 * @brief 3D ��ġ ������ ���� ������ �������Դϴ�.
	 *
	 * @param x ��ġ�� X��ǥ�Դϴ�.
	 * @param y ��ġ�� Y��ǥ�Դϴ�.
	 * @param z ��ġ�� Z��ǥ�Դϴ�.
	 */
	VertexPosition3D(float x, float y, float z) noexcept : position(x, y, z) {}


	/**
	 * @brief 3D ��ġ ������ ���� ������ �������Դϴ�.
	 *
	 * @param instance ������ ���� �ν��Ͻ��Դϴ�.
	 */
	VertexPosition3D(VertexPosition3D&& instance) noexcept
		: position(instance.position) {}


	/**
	 * @brief 3D ��ġ ������ ���� ������ �������Դϴ�.
	 *
	 * @param instance ������ ���� �ν��Ͻ��Դϴ�.
	 */
	VertexPosition3D(const VertexPosition3D& instance) noexcept
		: position(instance.position) {}


	/**
	 * @brief 3D ��ġ ������ ���� ������ ���� �������Դϴ�.
	 *
	 * @param instance ������ ���� �ν��Ͻ��Դϴ�.
	 *
	 * @return ������ ��ü�� �����ڸ� ��ȯ�մϴ�.
	 */
	VertexPosition3D& operator=(VertexPosition3D&& instance) noexcept
	{
		if (this == &instance) return *this;

		position = instance.position;

		return *this;
	}


	/**
	 * @brief 3D ��ġ ������ ���� ������ ���� �������Դϴ�.
	 *
	 * @param instance ������ ���� �ν��Ͻ��Դϴ�.
	 *
	 * @return ������ ��ü�� �����ڸ� ��ȯ�մϴ�.
	 */
	VertexPosition3D& operator=(const VertexPosition3D& instance) noexcept
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
		return sizeof(VertexPosition3D);
	}


	/**
	 * @brief ������ ��ġ�Դϴ�.
	 */
	Vec3f position;
};


/**
 * @brief 3D ��ġ�� ���� ������ ���� �����Դϴ�.
 */
struct VertexPositionColor3D
{
	/**
	 * @brief 3D ��ġ�� ���� ������ ���� ������ �⺻ �������Դϴ�.
	 */
	VertexPositionColor3D() noexcept
		: position(0.0f, 0.0f, 0.0f)
		, color(0.0f, 0.0f, 0.0f, 0.0f) {}


	/**
	 * @brief 3D ��ġ�� ���� ������ ���� ������ �������Դϴ�.
	 *
	 * @param p ������ ��ġ�Դϴ�.
	 * @param c ������ �����Դϴ�.
	 */
	VertexPositionColor3D(Vec3f&& p, Vec4f&& c) noexcept
		: position(p)
		, color(c) {}


	/**
	 * @brief 3D ��ġ�� ���� ������ ���� ������ �������Դϴ�.
	 *
	 * @param p ������ ��ġ�Դϴ�.
	 * @param c ������ �����Դϴ�.
	 */
	VertexPositionColor3D(const Vec3f& p, const Vec4f& c) noexcept
		: position(p)
		, color(c) {}


	/**
	 * @brief 3D ��ġ�� ���� ������ ���� ������ �������Դϴ�.
	 *
	 * @param x ��ġ�� X��ǥ�Դϴ�.
	 * @param y ��ġ�� Y��ǥ�Դϴ�.
	 * @param z ��ġ�� Z��ǥ�Դϴ�.
	 * @param r ���� ������ R�Դϴ�.
	 * @param g ���� ������ G�Դϴ�.
	 * @param b ���� ������ B�Դϴ�.
	 * @param a ���� ������ A�Դϴ�.
	 */
	VertexPositionColor3D(
		float x, float y, float z,
		float r, float g, float b, float a
	) noexcept
		: position(x, y, z)
		, color(r, g, b, a) {}


	/**
	 * @brief 3D ��ġ�� ���� ������ ���� ������ �������Դϴ�.
	 *
	 * @param instance ������ ���� �ν��Ͻ��Դϴ�.
	 */
	VertexPositionColor3D(VertexPositionColor3D&& instance) noexcept
		: position(instance.position)
		, color(instance.color) {}


	/**
	 * @brief 3D ��ġ�� ���� ������ ���� ������ �������Դϴ�.
	 *
	 * @param instance ������ ���� �ν��Ͻ��Դϴ�.
	 */
	VertexPositionColor3D(const VertexPositionColor3D& instance) noexcept
		: position(instance.position)
		, color(instance.color) {}


	/**
	 * @brief 3D ��ġ�� ���� ������ ���� ������ ���� �������Դϴ�.
	 *
	 * @param instance ������ ���� �ν��Ͻ��Դϴ�.
	 *
	 * @return ������ ��ü�� �����ڸ� ��ȯ�մϴ�.
	 */
	VertexPositionColor3D& operator=(VertexPositionColor3D&& instance) noexcept
	{
		if (this == &instance) return *this;

		position = instance.position;
		color = instance.color;

		return *this;
	}


	/**
	 * @brief 3D ��ġ�� ���� ������ ���� ������ ���� �������Դϴ�.
	 *
	 * @param instance ������ ���� �ν��Ͻ��Դϴ�.
	 *
	 * @return ������ ��ü�� �����ڸ� ��ȯ�մϴ�.
	 */
	VertexPositionColor3D& operator=(const VertexPositionColor3D& instance) noexcept
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
		return sizeof(VertexPositionColor3D);
	}


	/**
	 * @brief ������ ��ġ�Դϴ�.
	 */
	Vec3f position;


	/**
	 * @brief ������ �����Դϴ�.
	 */
	Vec4f color;
};



/**
 * @brief 3D ��ġ�� �ؽ�ó ��ǥ ������ ���� �����Դϴ�.
 */
struct VertexPositionUv3D
{
	/**
	 * @brief 3D ��ġ�� �ؽ�ó ��ǥ ������ ���� ������ �⺻ �������Դϴ�.
	 */
	VertexPositionUv3D() noexcept
		: position(0.0f, 0.0f, 0.0f)
		, uv(0.0f, 0.0f) {}


	/**
	 * @brief 3D ��ġ�� �ؽ�ó ��ǥ ������ ���� ������ �������Դϴ�.
	 *
	 * @param p ������ ��ġ�Դϴ�.
	 * @param tex ������ �����Դϴ�.
	 */
	VertexPositionUv3D(Vec3f&& p, Vec2f&& tex) noexcept
		: position(p)
		, uv(tex) {}


	/**
	 * @brief 3D ��ġ�� �ؽ�ó ��ǥ ������ ���� ������ �������Դϴ�.
	 *
	 * @param p ������ ��ġ�Դϴ�.
	 * @param tex ������ �����Դϴ�.
	 */
	VertexPositionUv3D(const Vec3f& p, const Vec2f& tex) noexcept
		: position(p)
		, uv(tex) {}


	/**
	 * @brief 3D ��ġ�� �ؽ�ó ��ǥ ������ ���� ������ �������Դϴ�.
	 *
	 * @param x ��ġ�� X��ǥ�Դϴ�.
	 * @param y ��ġ�� Y��ǥ�Դϴ�.
	 * @param z ��ġ�� Z��ǥ�Դϴ�.
	 * @param u �ؽ�ó ��ġ�� U��ǥ�Դϴ�.
	 * @param v �ؽ�ó ��ġ�� V��ǥ�Դϴ�.
	 */
	VertexPositionUv3D(
		float x, float y, float z,
		float u, float v
	) noexcept
		: position(x, y, z)
		, uv(u, v) {}


	/**
	 * @brief 3D ��ġ�� �ؽ�ó ��ǥ ������ ���� ������ �������Դϴ�.
	 *
	 * @param instance ������ ���� �ν��Ͻ��Դϴ�.
	 */
	VertexPositionUv3D(VertexPositionUv3D&& instance) noexcept
		: position(instance.position)
		, uv(instance.uv) {}


	/**
	 * @brief 3D ��ġ�� �ؽ�ó ��ǥ ������ ���� ������ �������Դϴ�.
	 *
	 * @param instance ������ ���� �ν��Ͻ��Դϴ�.
	 */
	VertexPositionUv3D(const VertexPositionUv3D& instance) noexcept
		: position(instance.position)
		, uv(instance.uv) {}


	/**
	 * @brief 3D ��ġ�� �ؽ�ó ��ǥ ������ ���� ������ ���� �������Դϴ�.
	 *
	 * @param instance ������ ���� �ν��Ͻ��Դϴ�.
	 *
	 * @return ������ ��ü�� �����ڸ� ��ȯ�մϴ�.
	 */
	VertexPositionUv3D& operator=(VertexPositionUv3D&& instance) noexcept
	{
		if (this == &instance) return *this;

		position = instance.position;
		uv = instance.uv;

		return *this;
	}


	/**
	 * @brief 3D ��ġ�� �ؽ�ó ��ǥ ������ ���� ������ ���� �������Դϴ�.
	 *
	 * @param instance ������ ���� �ν��Ͻ��Դϴ�.
	 *
	 * @return ������ ��ü�� �����ڸ� ��ȯ�մϴ�.
	 */
	VertexPositionUv3D& operator=(const VertexPositionUv3D& instance) noexcept
	{
		if (this == &instance) return *this;

		position = instance.position;
		uv = instance.uv;

		return *this;
	}


	/**
	 * @brief ������ ����Ʈ ���� ���� ����ϴ�.
	 *
	 * @return ������ ����Ʈ ����(Stride) ���� ��ȯ�մϴ�.
	 */
	static uint32_t GetStride()
	{
		return sizeof(VertexPositionUv3D);
	}


	/**
	 * @brief ������ ��ġ�Դϴ�.
	 */
	Vec3f position;


	/**
	 * @brief ������ �����Դϴ�.
	 */
	Vec2f uv;
};



/**
 * @brief 3D ��ġ, ����, �ؽ�ó ��ǥ ������ ���� �����Դϴ�.
 */
struct VertexPositionNormalUv3D
{
	/**
	 * @brief 3D ��ġ, ����, �ؽ�ó ��ǥ ������ ���� ������ ����Ʈ �������Դϴ�.
	 */
	VertexPositionNormalUv3D() noexcept
		: position(0.0f, 0.0f, 0.0f)
		, normal(0.0f, 0.0f, 0.0f)
		, uv(0.0f, 0.0f) {}


	/**
	 * @brief 3D ��ġ, ����, �ؽ�ó ��ǥ ������ ���� ������ �������Դϴ�.
	 *
	 * @param p ������ ��ġ�Դϴ�.
	 * @param n ������ ���� �����Դϴ�.
	 * @param tex ������ �ؽ�ó ��ǥ�Դϴ�.
	 */
	VertexPositionNormalUv3D(Vec3f&& p, Vec3f&& n, Vec2f&& tex) noexcept
		: position(p)
		, normal(n)
		, uv(tex) {}


	/**
	 * @brief 3D ��ġ, ����, �ؽ�ó ��ǥ ������ ���� ������ �������Դϴ�.
	 *
	 * @param position ������ ��ġ�Դϴ�.
	 * @param normal ������ ���� �����Դϴ�.
	 * @param uv ������ �ؽ�ó ��ǥ�Դϴ�.
	 */
	VertexPositionNormalUv3D(const Vec3f& p, const Vec3f& n, const Vec2f& tex) noexcept
		: position(p)
		, normal(n)
		, uv(tex) {}


	/**
	 * @brief 3D ��ġ, ����, �ؽ�ó ��ǥ ������ ���� ������ �������Դϴ�.
	 *
	 * @param px ���� ��ġ�� X��ǥ�Դϴ�.
	 * @param py ���� ��ġ�� Y��ǥ�Դϴ�.
	 * @param pz ���� ��ġ�� Z��ǥ�Դϴ�.
	 * @param nx ���� ���� ������ X�����Դϴ�.
	 * @param ny ���� ���� ������ Y�����Դϴ�.
	 * @param nz ���� ���� ������ Z�����Դϴ�.
	 * @param u ���� �ؽ�ó ��ǥ�� U�����Դϴ�.
	 * @param v ���� �ؽ�ó ��ǥ�� V�����Դϴ�.
	 */
	VertexPositionNormalUv3D(
		float px, float py, float pz,
		float nx, float ny, float nz,
		float u, float v
	) noexcept
		: position(px, py, pz)
		, normal(nx, ny, nz)
		, uv(u, v) {}


	/**
	 * @brief 3D ��ġ, ����, �ؽ�ó ��ǥ ������ ���� ������ ���� �������Դϴ�.
	 *
	 * @param instance ���縦 ������ 3D ��ġ, ����, �ؽ�ó ��ǥ ������ ���� ���� �ν��Ͻ��Դϴ�.
	 */
	VertexPositionNormalUv3D(VertexPositionNormalUv3D&& instance) noexcept
		: position(instance.position)
		, normal(instance.normal)
		, uv(instance.uv) {}


	/**
	 * @brief 3D ��ġ, ����, �ؽ�ó ��ǥ ������ ���� ������ ���� �������Դϴ�.
	 *
	 * @param instance ���縦 ������ 3D ��ġ, ����, �ؽ�ó ��ǥ ������ ���� ���� �ν��Ͻ��Դϴ�.
	 */
	VertexPositionNormalUv3D(const VertexPositionNormalUv3D& instance) noexcept
		: position(instance.position)
		, normal(instance.normal)
		, uv(instance.uv) {}


	/**
	 * @brief 3D ��ġ, ����, �ؽ�ó ��ǥ ������ ���� ������ ���� �������Դϴ�.
	 *
	 * @param instance ���縦 ������ 3D ��ġ, ����, �ؽ�ó ��ǥ ������ ���� ���� �ν��Ͻ��Դϴ�.
	 *
	 * @return ������ ��ü�� �����ڸ� ��ȯ�մϴ�.
	 */
	VertexPositionNormalUv3D& operator=(VertexPositionNormalUv3D&& instance) noexcept
	{
		if (this == &instance) return *this;

		position = instance.position;
		normal = instance.normal;
		uv = instance.uv;

		return *this;
	}


	/**
	 * @brief 3D ��ġ, ����, �ؽ�ó ��ǥ ������ ���� ������ ���� �������Դϴ�.
	 *
	 * @param instance ���縦 ������ 3D ��ġ, ����, �ؽ�ó ��ǥ ������ ���� ���� �ν��Ͻ��Դϴ�.
	 *
	 * @return ������ ��ü�� �����ڸ� ��ȯ�մϴ�.
	 */
	VertexPositionNormalUv3D& operator=(const VertexPositionNormalUv3D& instance) noexcept
	{
		if (this == &instance) return *this;

		position = instance.position;
		normal = instance.normal;
		uv = instance.uv;

		return *this;
	}


	/**
	 * @brief ������ ����Ʈ ���� ���� ����ϴ�.
	 *
	 * @return ������ ����Ʈ ����(Stride) ���� ��ȯ�մϴ�.
	 */
	static uint32_t GetStride()
	{
		return sizeof(VertexPositionNormalUv3D);
	}


	/**
	 * @brief ������ ��ġ�Դϴ�.
	 */
	Vec3f position;


	/**
	 * @brief ������ ���� �����Դϴ�.
	 */
	Vec3f normal;


	/**
	 * @brief ������ �ؽ�ó ��ǥ�Դϴ�.
	 */
	Vec2f uv;
};