#pragma once

#include "IEntity.h"

/** UI ��ƼƼ�� �������̽��Դϴ�. */
class IEntityUI : public IEntity
{
public:
	IEntityUI() {}
	virtual ~IEntityUI() {}

	DISALLOW_COPY_AND_ASSIGN(IEntityUI);

	virtual void Tick(float deltaSeconds) = 0;
	virtual void Release() = 0;
};