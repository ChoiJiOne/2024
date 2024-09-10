#pragma once

#include "Collision2D.h"
#include "Entity2D.h"

class Player;
class SpriteAnim2D;

class Coin : public Entity2D
{
public: 
	enum class Status
	{
		ACTIVE = 0x00,
		PICKUP = 0x01,
		DONE   = 0x02,
	};

public:
	Coin(const Circle2D& bound);
	virtual ~Coin();

	DISALLOW_COPY_AND_ASSIGN(Coin);

	virtual void Tick(float deltaSeconds) override;
	virtual void Render() override;
	virtual void Release() override;

	const Status& GetStatus() const { return status_; }
	void SetStatus(const Status& status) { status_ = status; }
	
private:
	Player* player_ = nullptr;

	SpriteAnim2D* anim_ = nullptr;

	Circle2D bound_;
	Status status_ = Status::ACTIVE;
};