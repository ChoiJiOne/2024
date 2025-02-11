#pragma once

#include <glm/glm.hpp>

/** 2D 물리 충돌 처리를 위한 인터페이스입니다. */
struct ICollider2D
{
	/** 2D 물리 충돌 처리 객체의 종류입니다. */
	enum class EType
	{
		NONE   = 0x00,
		LINE   = 0x01,
		CIRCLE = 0x02,
		AABB   = 0x03,
		OBB    = 0x04,
	};

	/** 2D 물리 충돌 처리를 위한 인터페이스의 기본 생성자와 빈 가상 소멸자입니다. */
	ICollider2D() = default;
	virtual ~ICollider2D() {}

	/** 2D 물리 충돌 처리 객체의 타입을 얻습니다. */
	virtual EType GetType() const = 0;
	
	/** 2D 물리 충돌 처리 객체간의 충돌 여부를 얻습니다. */
	virtual bool Intersect(const ICollider2D* collider) const = 0;
};