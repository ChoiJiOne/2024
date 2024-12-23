#pragma once

#include "Collision2D.h"
#include "Entity2D.h"

class Player;
class SpriteAnim2D;

class Coin : public Entity2D
{
public:
	Coin(const Circle2D& bound);
	virtual ~Coin();

	DISALLOW_COPY_AND_ASSIGN(Coin);

	virtual void Tick(float deltaSeconds) override;
	virtual void Render() override;
	virtual void Release() override;

	bool IsPickup() const { return bIsPickup_; }

private:
	Player* player_ = nullptr;

	SpriteAnim2D* anim_ = nullptr;

	Circle2D bound_;
	bool bIsPickup_ = false;
};