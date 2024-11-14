#pragma once

#include "Utils/Macro.h"

/** 엔티티 인터페이스로, 게임 내의 엔티티들은 반드시 이 인터페이스를 상속받아야 합니다. */
class IEntity
{
public:
	IEntity() = default;
	virtual ~IEntity() {}

	DISALLOW_COPY_AND_ASSIGN(IEntity);

	virtual void Tick(float deltaSeconds) = 0;
	virtual void Release() = 0;

	/** 엔티티가 초기화 되었는지 확인합니다. */
	bool IsInitialized() const { return bIsInitialized_; }

	/** 엔티티의 업데이트 순위 값을 설정합니다. */
	void SetTickOrder(uint32_t tickOrder) { tickOrder_ = tickOrder; }

	/** 엔티티의 업데이트 순위 값을 얻습니다. */
	uint32_t GetTickOrder() const { return tickOrder_; }

protected:
	/** 엔티티가 초기화 되었는지 확인합니다. */
	bool bIsInitialized_ = false;

private:
	/** 엔티티의 업데이트 순위 값입니다. 이 값은 낮을수록 우선순위가 높아집니다. */
	uint32_t tickOrder_ = 0;
};