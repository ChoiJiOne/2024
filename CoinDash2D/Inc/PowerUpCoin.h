#pragma once

#include "Collision2D.h"
#include "Entity2D.h"

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

private:
	Player* player_ = nullptr;

	SpriteAnim2D* anim_ = nullptr;

	Circle2D bound_;
};