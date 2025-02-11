#pragma once

#include "IEntity.h"

/** 2D ��ƼƼ �������̽��Դϴ�. */
class Entity2D : public IEntity
{
public:
	Entity2D() = default;
	virtual ~Entity2D() {}

	DISALLOW_COPY_AND_ASSIGN(Entity2D);

	virtual void Tick(float deltaSeconds) = 0;
	virtual void Render() = 0;
	virtual void Release() = 0;
};