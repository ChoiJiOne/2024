#pragma once

#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"


/**
 * @brief 정점(Vertex)입니다.
 */
struct Vertex
{
	/**
	 * @brief 위치 정보를 가진 정점의 기본 생성자입니다.
	 */
	Vertex() noexcept
		: position(0.0f, 0.0f, 0.0f)
		, normal(0.0f, 0.0f, 0.0f)
		, texture(0.0f, 0.0f)
		, tangent(0.0f, 0.0f, 0.0f)
		, bitangent(0.0f, 0.0f, 0.0f)
		, color(0.0f, 0.0f, 0.0f, 0.0f) {}


	/**
	 * @brief 위치 정보를 가진 정점의 생성자입니다.
	 *
	 * @param p 정점의 위치입니다.
	 * @param n 정점의 법선 벡터입니다.
	 * @param uv 정점의 텍셀입니다.
	 * @param t 정점의 접선 벡터입니다.
	 * @param b 정점의 쌍벡터입니다.
	 * @param c 정점의 색상입니다.
	 */
	Vertex(Vector3f&& p, Vector3f&& n, Vector2f&& uv, Vector3f&& t, Vector3f&& b, Vector4f&& c) noexcept
		: position(p) 
		, normal(n)
		, texture(uv)
		, tangent(t)
		, bitangent(b)
		, color(c) {}


	/**
	 * @brief 위치 정보를 가진 정점의 생성자입니다.
	 *
	 * @param p 정점의 위치입니다.
	 * @param n 정점의 법선 벡터입니다.
	 * @param uv 정점의 텍셀입니다.
	 * @param t 정점의 접선 벡터입니다.
	 * @param b 정점의 쌍벡터입니다.
	 * @param c 정점의 색상입니다.
	 */
	Vertex(const Vector3f& p, const Vector3f& n, const Vector2f& uv, const Vector3f& t, const Vector3f& b, const Vector4f& c) noexcept
		: position(p)
		, normal(n)
		, texture(uv)
		, tangent(t)
		, bitangent(b)
		, color(c) {}

	
	/**
	 * @brief 위치 정보를 가진 정점의 생성자입니다.
	 *
	 * @param instance 복사할 정점 인스턴스입니다.
	 */
	Vertex(Vertex&& instance) noexcept
		: position(instance.position)
		, normal(instance.normal)
		, texture(instance.texture)
		, tangent(instance.tangent)
		, bitangent(instance.bitangent)
		, color(instance.color) {}


	/**
	 * @brief 위치 정보를 가진 정점의 생성자입니다.
	 *
	 * @param instance 복사할 정점 인스턴스입니다.
	 */
	Vertex(const Vertex& instance) noexcept
		: position(instance.position)
		, normal(instance.normal)
		, texture(instance.texture)
		, tangent(instance.tangent)
		, bitangent(instance.bitangent)
		, color(instance.color) {}


	/**
	 * @brief 위치 정보를 가진 정점의 대입 연산자입니다.
	 *
	 * @param instance 대입할 정점 인스턴스입니다.
	 *
	 * @return 대입한 객체의 참조자를 반환합니다.
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
	 * @brief 위치 정보를 가진 정점의 대입 연산자입니다.
	 *
	 * @param instance 대입할 정점 인스턴스입니다.
	 *
	 * @return 대입한 객체의 참조자를 반환합니다.
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
	 * @brief 정점의 바이트 보폭 값을 얻습니다.
	 *
	 * @return 정점의 파이트 보폭(Stride) 값을 반환합니다.
	 */
	static uint32_t GetStride()
	{
		return sizeof(Vertex);
	}


	/**
	 * @brief 정점의 위치입니다.
	 */
	Vector3f position;


	/**
	 * @brief 정점의 법선 벡터입니다.
	 */
	Vector3f normal;


	/**
	 * @brief 정점의 텍셀입니다.
	 */
	Vector2f texture;


	/**
	 * @brief 정점의 접선 벡터입니다.
	 */
	Vector3f tangent;


	/**
	 * @brief 정점의 쌍벡터입니다.
	 */
	Vector3f bitangent;


	/**
	 * @brief 정점의 색상입니다.
	 */
	Vector4f color;
};