#pragma once

#include "Collision2D.h"

#include "Entity2D.h"

class Atlas2D;
class SpriteAnimation;

class Player : public Entity2D
{
public:
	Player();
	virtual ~Player();

	DISALLOW_COPY_AND_ASSIGN(Player);

	virtual void Tick(float deltaSeconds) override;
	virtual void Render() override;
	virtual void Release() override;

	ICollision2D* GetCollision() { return &collisionBound_; }

private:
	Atlas2D* atlas_ = nullptr;

	Rect2D spriteBound_;
	Circle2D collisionBound_;

	SpriteAnimation* animation_ = nullptr;
};