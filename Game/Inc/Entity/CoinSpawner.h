#pragma once

#include <list>

#include "Entity/IEntity.h"
#include "Physic/Circle2D.h"

/** Ŭ������ ���� �����Դϴ�. */
class Coin;

/** �ʵ��� ������ �����ϴ� ��ƼƼ�Դϴ�. */
class CoinSpawner : public IEntity
{
public:
	CoinSpawner();
	virtual ~CoinSpawner();

	DISALLOW_COPY_AND_ASSIGN(CoinSpawner);

	virtual void Tick(float deltaSeconds) override;
	virtual void Release() override;

private:
	/** ���� ���� ���� �����Դϴ�. */
	std::list<Coin*> coins_;

	/** ������ �����ϴ� ���� ũ���Դϴ�. */
	Circle2D bound_;

	/** ���� ������ �����Դϴ�. */
	int32_t countCoin_ = 0;
};