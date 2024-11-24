#pragma once

#include <glm/glm.hpp>

#include "Entity/IEntity.h"

/** ���̵� ȿ���� �����ϴ� ��ƼƼ�Դϴ�. */
class FadeEffector : public IEntity
{
public:
	FadeEffector();
	virtual ~FadeEffector();

	DISALLOW_COPY_AND_ASSIGN(FadeEffector);

	virtual void Tick(float deltaSeconds) override;
	virtual void Release() override;

private:

};