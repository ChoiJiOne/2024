#pragma once

#include <map>

#include "Collision2D.h"
#include "Entity2D.h"

class Camera;
class IApp;
class SpriteAnim2D;

class Player : public Entity2D
{
public:
	enum class Status
	{
		IDLE = 0x00,
		RUN  = 0x01,
		HURT = 0x02,
	};

public:
	Player();
	virtual ~Player();

	DISALLOW_COPY_AND_ASSIGN(Player);

	virtual void Tick(float deltaSeconds) override;
	virtual void Render() override;
	virtual void Release() override;

	const Status& GetStatus() const { return status_; }
	void SetStatus(const Status& status) { status_ = status; }

	ICollision2D* GetCollisionBound() { return &collisionBound_; }

	void PickupCoin();
	void PickupPowerUpCoin();

private:
	void Move(float deltaSeconds);
	void UpdatePowerUpBar();
	
private:
	IApp* app_ = nullptr;
	Camera* camera_ = nullptr;
	
	Status status_ = Status::IDLE;
	std::map<Status, SpriteAnim2D*> anims_;

	Point2D center_;
	Rect2D spriteBound_;
	Rect2D collisionBound_;

	GameMath::Vec2f direction_;
	float speed_ = 0.0f;

	bool bIsFlipH_ = false;

	int32_t numCoin_ = 0;
	GameMath::Vec4f messageColor_ = GameMath::Vec4f(0.0f, 0.0f, 0.0f, 1.0f);

	bool bIsPowerUp_ = false;
	float normalSpeed_ = 200.0f;
	float maxPowerUpSpeed_ = 350.0f;
	float maxPowerUpTime_ = 5.0f;
	float powerUpTime_ = 0.0f;
	
	Rect2D powerUpBar_;
	Rect2D remainBar_;
	GameMath::Vec4f powerUpBarColor_;
	GameMath::Vec4f remainBarColor_;
};