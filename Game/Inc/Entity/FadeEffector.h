#pragma once

#include <glm/glm.hpp>

#include "Entity/IEntity.h"

/** 페이드 효과를 제어하는 엔티티입니다. */
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