#pragma once

#include "IEntity.h"

/** 2D ��ƼƼ�� �������̽��Դϴ�. */
class IEntity2D : public IEntity
{
public:
	IEntity2D() = default;
	virtual ~IEntity2D() {}

	DISALLOW_COPY_AND_ASSIGN(IEntity2D);

	virtual void Tick(float deltaSeconds) = 0;
	virtual void Render() = 0;
	virtual void Release() = 0;
};