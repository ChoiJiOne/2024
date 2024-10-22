#pragma once

#include "IEntity.h"

/** 3D ��ƼƼ�� �������̽��Դϴ�. */
class IEntity3D : public IEntity
{
public:
	IEntity3D() {}
	virtual ~IEntity3D() {}

	DISALLOW_COPY_AND_ASSIGN(IEntity3D);

	virtual void Tick(float deltaSeconds) = 0;
	virtual void Release() = 0;
};