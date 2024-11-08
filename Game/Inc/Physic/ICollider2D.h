#pragma once

#include <glm/glm.hpp>

/** 2D ���� �浹 ó���� ���� �������̽��Դϴ�. */
struct ICollider2D
{
	/** 2D ���� �浹 ó�� ��ü�� �����Դϴ�. */
	enum class EType
	{
		NONE   = 0x00,
		POINT  = 0x01,
		LINE   = 0x02,
		CIRCLE = 0x03,
		AABB   = 0x04,
		OBB    = 0x05,
	};

	/** 2D ���� �浹 ó���� ���� �������̽��� �⺻ �����ڿ� �� ���� �Ҹ����Դϴ�. */
	ICollider2D() = default;
	virtual ~ICollider2D() {}

	/** 2D ���� �浹 ó�� ��ü�� Ÿ���� ����ϴ�. */
	virtual EType GetType() const = 0;
	
	/** 2D ���� �浹 ó�� ��ü���� �浹 ���θ� ����ϴ�. */
	virtual bool Intersect(const ICollider2D* collider) const = 0;
};