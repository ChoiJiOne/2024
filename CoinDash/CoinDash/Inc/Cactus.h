#pragma once

#include "Collision2D.h"

#include "Entity2D.h"

class Atlas2D;
class Player;
class Sound;

class Cactus : public Entity2D
{
public:
	Cactus(const Rect2D& bound);
	virtual ~Cactus();

	DISALLOW_COPY_AND_ASSIGN(Cactus);

	virtual void Tick(float deltaSeconds) override;
	virtual void Render() override;
	virtual void Release() override;

	ICollision2D* GetBound() { return &collisionBound_; }

private:
	Player* player_ = nullptr;
	Atlas2D* atlas_ = nullptr;

	Rect2D spriteBound_;
	Rect2D collisionBound_;

	Sound* hitSound_ = nullptr;
};