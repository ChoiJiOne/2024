#pragma once

#include "IEntity.h"

/** 2D 엔티티 인터페이스입니다. */
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