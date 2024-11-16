#pragma once

#include <list>

#include "Entity/IEntity.h"
#include "Physic/Circle2D.h"

/** 클래스의 전방 선언입니다. */
class Coin;

/** 필드의 코인을 관리하는 엔티티입니다. */
class CoinSpawner : public IEntity
{
public:
	CoinSpawner();
	virtual ~CoinSpawner();

	DISALLOW_COPY_AND_ASSIGN(CoinSpawner);

	virtual void Tick(float deltaSeconds) override;
	virtual void Release() override;

private:
	/** 현재 관리 중인 코인입니다. */
	std::list<Coin*> coins_;

	/** 코인이 존재하는 영역 크기입니다. */
	Circle2D bound_;

	/** 현재 코인의 개수입니다. */
	int32_t countCoin_ = 0;
};