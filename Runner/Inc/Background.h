#pragma once

#include "Collision2D.h"

#include "Entity2D.h"

class Atlas2D;
class Camera2D;
class Player;

class Background : public Entity2D
{
public:
	Background();
	virtual ~Background();

	DISALLOW_COPY_AND_ASSIGN(Background);

	virtual void Tick(float deltaSeconds) override;
	virtual void Render() override;
	virtual void Release() override;

	bool CanMove() { return bCanMove_; }
	void SetMovable(bool bCanMove) { bCanMove_ = bCanMove; }

private:
	bool GetMovable();

private:
	Player* player_ = nullptr;
	Camera2D* camera_ = nullptr;
	Atlas2D* atlas_ = nullptr;
	std::array<Rect2D, 2> rects_;

	bool bCanMove_ = false;
	float scrollSpeed_ = 100.0f;
};