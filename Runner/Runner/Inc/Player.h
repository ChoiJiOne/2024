#pragma once

#include <map>

#include "Collision2D.h"

#include "Entity2D.h"

class Atlas2D;
class IApp;
class SpriteAnimation;

class Player : public Entity2D
{
public:
	enum class EStatus
	{
		IDLE = 0x00,
		RUN  = 0x01,
		JUMP = 0x02,
		HURT = 0x03,
		STOP = 0x04,
	};

public:
	Player();
	virtual ~Player();

	DISALLOW_COPY_AND_ASSIGN(Player);

	virtual void Tick(float deltaSeconds) override;
	virtual void Render() override;
	virtual void Release() override;

	ICollision2D* GetCollision() { return &collisionBound_; }

	const EStatus& GetStatus() const { return status_; }
	void SetStatus(const EStatus& status) { status_ = status; }

	float GetSpeed() const { return speed_; }

	void PickupCherry();
	void PickupGem();

	int32_t GetNumPickupCherry() const { return numPickupCherry_; }
	int32_t GetNumPickupGem() const { return numPickupGem_; }

	void Reset();

private:
	void LoadAnimations();

private:
	IApp* app_ = nullptr;

	Atlas2D* atlas_ = nullptr;

	Rect2D spriteBound_;
	Rect2D originSpriteBound_;
	Circle2D collisionBound_;
	Circle2D originCollisionBound_;

	float speed_ = 0.0f;
	float jumpSpeed_ = 0.0f;

	EStatus status_ = EStatus::IDLE;
	std::map<EStatus, SpriteAnimation*> animations_;

	int32_t numPickupCherry_ = 0;
	int32_t numPickupGem_ = 0;
};