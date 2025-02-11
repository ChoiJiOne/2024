#pragma once

#include "Collision2D.h"

#include "Entity2D.h"

class Atlas2D;
class Camera2D;
class Player;

class Box : public Entity2D
{
public:
	enum class EStatus
	{
		ACTIVE = 0x00,
		DONE = 0x01,
	};

public:
	Box(const Rect2D& bound);
	virtual ~Box();

	DISALLOW_COPY_AND_ASSIGN(Box);

	virtual void Tick(float deltaSeconds) override;
	virtual void Render() override;
	virtual void Release() override;

	Rect2D* GetCollision() { return &bound_; }

	const EStatus& GetStatus() const { return status_; }
	void SetStatus(const EStatus& status) { status_ = status; }
	
	bool CanMove() { return bCanMove_; }
	void SetMovable(bool bCanMove) { bCanMove_ = bCanMove; }

private:
	bool GetMovable();

private:
	Player* player_ = nullptr;
	Camera2D* camera_ = nullptr;
	Atlas2D* atlas_ = nullptr;

	Rect2D bound_;

	EStatus status_ = EStatus::ACTIVE;
	bool bCanMove_ = false;
};