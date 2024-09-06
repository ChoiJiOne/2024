#pragma once

#include "Collision2D.h"

#include "Entity2D.h"

class Atlas2D;
class Camera;
class Player;

class Box : public Entity2D
{
public:
	Box(const Rect2D& bound);
	virtual ~Box();

	DISALLOW_COPY_AND_ASSIGN(Box);

	virtual void Tick(float deltaSeconds) override;
	virtual void Render() override;
	virtual void Release() override;

	Rect2D* GetCollision() { return &bound_; }

	bool CanMove() { return bCanMove_; }
	void SetMovable(bool bCanMove) { bCanMove_ = bCanMove; }

private:
	Player* player_ = nullptr;
	Camera* camera_ = nullptr;
	Atlas2D* atlas_ = nullptr;

	Rect2D bound_;

	bool bCanMove_ = false;
};