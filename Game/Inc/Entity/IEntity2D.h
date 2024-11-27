#pragma once

#include "Entity/IEntity.h"

/** 2D ��ƼƼ�� �������̽��Դϴ�. */
class IEntity2D : public IEntity
{
public:
	IEntity2D();
	virtual ~IEntity2D();

	DISALLOW_COPY_AND_ASSIGN(IEntity2D);

	virtual void Tick(float deltaSeconds) = 0;
	virtual void Render() = 0;
	virtual void Release() = 0;

protected:
	/** �������� �� ����� 2D �������Դϴ�. */
	class RenderManager2D* renderManager_ = nullptr;;
};