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

private:
	void LoadAnimations();

private:
	IApp* app_ = nullptr;

	Atlas2D* atlas_ = nullptr;

	Rect2D spriteBound_;
	Rect2D originSpriteBound_;
	Circle2D collisionBound_;
	Circle2D originCollisionBound_;

	float jumpSpeed_ = 0.0f;

	EStatus status_ = EStatus::IDLE;
	std::map<EStatus, SpriteAnimation*> animations_;
};