#include "Assertion.h"
#include "EntityManager.h"

#include "Box.h"
#include "Player.h"
#include "Spawner.h"

Spawner::Spawner() 
	: player_(EntityManager::Get().GetByName<Player>("Player"))
{
	boxSize_ = GameMath::Vec2f(40.0f, 40.0f);
	spawnPosition_ = GameMath::Vec2f(+400.0f, -200.0f) + boxSize_ * 0.5f;

	boxRemoveEvent_ = [&](Box* box)->bool { return box == nullptr; };
	boxSortEvent_ = [](Box* l, Box* r) { return l->GetCollision()->center.x > r->GetCollision()->center.x; };

	bIsInitialized_ = true;
}

Spawner::~Spawner()
{
	if (bIsInitialized_)
	{
		Release();
	}
}

void Spawner::Tick(float deltaSeconds)
{
	if (!IsActive())
	{
		return;
	}

	spawnTime_ -= deltaSeconds;
	if (spawnTime_ <= 0.0f)
	{
		spawnTime_ = GameMath::GenerateRandomFloat(1.5f, 3.0f);
		
		Rect2D bound;
		bound.size = boxSize_;
		bound.center = spawnPosition_;

		uint32_t count = GameMath::GenerateRandomInt(1, 3);
		for (uint32_t index = 0; index < count; ++index)
		{
			bound.center.x = spawnPosition_.x + boxSize_.x * (0.5f + static_cast<float>(index));
			boxes_.push_back(EntityManager::Get().Create<Box>(bound));
		}

		boxes_.sort(boxSortEvent_);
	}

	for (auto& box : boxes_)
	{
		box->Tick(deltaSeconds);
	}

	Cleanup();
}

void Spawner::Render()
{
	for (auto& box : boxes_)
	{
		box->Render();
	}
}

void Spawner::Release()
{
	CHECK(bIsInitialized_);

	player_ = nullptr;

	bIsInitialized_ = false;
}

bool Spawner::IsActive()
{
	Player::EStatus status = player_->GetStatus();
	return status == Player::EStatus::RUN || status == Player::EStatus::JUMP;
}

void Spawner::Cleanup()
{
	for (auto& box : boxes_)
	{
		if (box && !box->CanMove())
		{
			EntityManager::Get().Destroy(box);
			box = nullptr;
		}
	}

	boxes_.remove_if(boxRemoveEvent_);
}