#pragma once

#include "Collision2D.h"

#include "Entity2D.h"

class Atlas2D;
class Camera2D;
class Player;

class Floor : public Entity2D
{
public:
	Floor();
	virtual ~Floor();

	DISALLOW_COPY_AND_ASSIGN(Floor);

	virtual void Tick(float deltaSeconds) override;
	virtual void Render() override;
	virtual void Release() override;

	bool CanMove() { return bCanMove_; }
	void SetMovable(bool bCanMove) { bCanMove_ = bCanMove; }

private:
	void ResetBlocks();
	bool GetMovable();

private:
	static const uint32_t MAX_BLOCK_SIZE = 21;

	Player* player_ = nullptr;
	Camera2D* camera_ = nullptr;
	Atlas2D* atlas_ = nullptr;

	Rect2D floor_;
	std::array<Rect2D, MAX_BLOCK_SIZE> blocks_;
	
	bool bCanMove_ = false;
};