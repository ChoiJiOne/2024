#pragma once

#include <functional>
#include <vector>
#include <list>

#include "Entity2D.h"

class Cactus;
class Camera2D;
class Coin;
class Player;
class Sound;

class CoinSpawner : public Entity2D
{
public:
	CoinSpawner();
	virtual ~CoinSpawner();

	DISALLOW_COPY_AND_ASSIGN(CoinSpawner);

	virtual void Tick(float deltaSeconds) override;
	virtual void Render() override;
	virtual void Release() override;

	void Reset();

private:
	void Cleanup();
	void GenerateCoins();

private:
	Camera2D* camera_ = nullptr;
	Player* player_ = nullptr;
	std::vector<Cactus*> cactus_;

	int32_t maxNumCoin_ = 0;
	std::list<Coin*> coins_;

	std::function<bool(Coin* coin)> coinRemoveEvent_ = nullptr;

	Sound* level_ = nullptr;
};