#pragma once

#include <list>

#include "Entity2D.h"

class Camera;
class Coin;
class Player;

class CoinSpawner : public Entity2D
{
public:
	CoinSpawner();
	virtual ~CoinSpawner();

	DISALLOW_COPY_AND_ASSIGN(CoinSpawner);

	virtual void Tick(float deltaSeconds) override;
	virtual void Render() override;
	virtual void Release() override;

private:
	Camera* camera_ = nullptr;
	Player* player_ = nullptr;

	int32_t maxNumCoin_ = 0;
	std::list<Coin*> coins_;
};