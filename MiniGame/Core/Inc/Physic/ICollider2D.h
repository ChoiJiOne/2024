#pragma once

#include <glm/glm.hpp>

/** 2D ���� �浹 ó���� ���� �������̽��Դϴ�. */
struct ICollider2D
{
	/** 2D ���� �浹 ó�� ��ü�� �����Դϴ�. */
	enum class EType
	{
		NONE   = 0x00,
		LINE   = 0x01,
		CIRCLE = 0x02,
		AABB   = 0x03,
		OBB    = 0x04,
	};

	/** 2D ���� �浹 ó���� ���� �������̽��� �⺻ �����ڿ� �� ���� �Ҹ����Դϴ�. */
	ICollider2D() = default;
	virtual ~ICollider2D() {}

	/** 2D ���� �浹 ó�� ��ü�� Ÿ���� ����ϴ�. */
	virtual EType GetType() const = 0;
	
	/** 2D ���� �浹 ó�� ��ü���� �浹 ���θ� ����ϴ�. */
	virtual bool Intersect(const ICollider2D* collider) const = 0;
};