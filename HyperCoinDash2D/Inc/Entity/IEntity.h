#pragma once

#include "Macro.h"

/** 엔티티 인터페이스로, 게임 내의 엔티티들은 반드시 이 인터페이스를 상속받아야 합니다. */
class IEntity
{
public:
	IEntity() = default;
	virtual ~IEntity() {}

	DISALLOW_COPY_AND_ASSIGN(IEntity);

	virtual void Tick(float deltaSeconds) = 0;
	virtual void Release() = 0;

	bool IsInitialized() const { return bIsInitialized_; }

protected:
	bool bIsInitialized_ = false;
};