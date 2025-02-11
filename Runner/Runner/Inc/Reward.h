#pragma once

#include "Collision2D.h"

#include "Entity2D.h"

class Atlas2D;
class Camera2D;
class Player;
class SpriteAnimation;

class Reward : public Entity2D
{
public:
	enum class Type
	{
		CHERRY = 0x00,
		GEM    = 0x01,
	};

	enum class EStatus
	{
		ACTIVE = 0x00,
		PICKUP = 0x01,
		DONE   = 0x02,
	};

public:
	Reward(const Circle2D& bound, const Type& type);
	virtual ~Reward();

	DISALLOW_COPY_AND_ASSIGN(Reward);

	virtual void Tick(float deltaSeconds) override;
	virtual void Render() override;
	virtual void Release() override;

	Circle2D* GetCollision() { return &bound_; }

	const EStatus& GetStatus() const { return status_; }
	void SetStatus(const EStatus& status) { status_ = status; }

	bool CanMove() { return bCanMove_; }
	void SetMovable(bool bCanMove) { bCanMove_ = bCanMove; }

	static Type GetRandomType();

private:
	void LoadAnimations();
	bool GetMovable();

private:
	Player* player_ = nullptr;
	Camera2D* camera_ = nullptr;
	Atlas2D* atlas_ = nullptr;

	Type type_ = Type::CHERRY;

	Circle2D bound_;

	EStatus status_ = EStatus::ACTIVE;
	std::map<EStatus, SpriteAnimation*> animations_;

	bool bCanMove_ = false;
};