#pragma once

#include <functional>
#include <list>

#include "Collision2D.h"

#include "Entity2D.h"

class Box;
class Player;

class Spawner : public Entity2D
{
public:
	Spawner();
	virtual ~Spawner();

	DISALLOW_COPY_AND_ASSIGN(Spawner);

	virtual void Tick(float deltaSeconds) override;
	virtual void Render() override;
	virtual void Release() override;

private:
	bool IsActive();
	void Cleanup();

private:
	Player* player_ = nullptr;

	std::list<Box*> boxes_;

	GameMath::Vec2f spawnPosition_;
	GameMath::Vec2f boxSize_;

	float spawnTime_ = 0.0f;

	std::function<bool(Box*, Box*)> boxSortEvent_;
	std::function<bool(Box* box)> boxRemoveEvent_;
};