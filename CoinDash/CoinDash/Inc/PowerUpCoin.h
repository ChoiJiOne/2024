#pragma once

#include "Collision2D.h"
#include "Entity2D.h"

class Cactus;
class Player;
class SpriteAnim2D;

class PowerUpCoin : public Entity2D
{
public:
	PowerUpCoin();
	virtual ~PowerUpCoin();

	DISALLOW_COPY_AND_ASSIGN(PowerUpCoin);

	virtual void Tick(float deltaSeconds) override;
	virtual void Render() override;
	virtual void Release() override;

	void Reset();

private:
	Player* player_ = nullptr;
	std::vector<Cactus*> cactus_;

	SpriteAnim2D* anim_ = nullptr;

	bool bIsActive_ = false;
	Circle2D bound_;

	float time_ = 0.0f;
};