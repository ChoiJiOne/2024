#include "Assertion.h"
#include "EntityManager.h"

#include "Box.h"
#include "Player.h"
#include "Reward.h"
#include "Spawner.h"

Spawner::Spawner() 
	: player_(EntityManager::Get().GetByName<Player>("Player"))
{
	boxSize_ = Vec2f(50.0f, 50.0f);
	spawnPosition_ = Vec2f(+400.0f, -200.0f) + boxSize_ * 0.5f;

	boxSortEvent_ = [](Box* l, Box* r)->bool { return l->GetCollision()->center.x > r->GetCollision()->center.x; };
	boxRemoveEvent_ = [&](Box* box)->bool { return box == nullptr; };
	rewardSortEvent_ = [](Reward* l, Reward* r)->bool { return l->GetCollision()->center.x > r->GetCollision()->center.x; };
	rewardRemoveEvent_ = [&](Reward* reward)->bool { return reward == nullptr; };

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
	Player::EStatus status = player_->GetStatus();
	if (status == Player::EStatus::IDLE)
	{
		return;
	}

	spawnTime_ -= deltaSeconds;
	if (status != Player::EStatus::HURT && spawnTime_ <= 0.0f)
	{
		spawnTime_ = GameMath::GenerateRandomFloat(1.5f, 3.0f);
		
		Rect2D boxBound;
		boxBound.size = boxSize_;
		boxBound.center = spawnPosition_;

		Circle2D rewardBound;
		rewardBound.radius = 20.0f;

		uint32_t count = GameMath::GenerateRandomInt(1, 3);
		Reward::Type type = (count == 1) ? Reward::GetRandomType() : Reward::Type::CHERRY;
		for (uint32_t index = 0; index < count; ++index)
		{
			boxBound.center.x = spawnPosition_.x + boxSize_.x * (0.5f + static_cast<float>(index));
			boxes_.push_back(EntityManager::Get().Create<Box>(boxBound));

			rewardBound.center = boxBound.center;
			rewardBound.center.y += 80.0f;
			rewards_.push_back(EntityManager::Get().Create<Reward>(rewardBound, type));
		}

		boxes_.sort(boxSortEvent_);
		rewards_.sort(rewardSortEvent_);
	}

	for (auto& box : boxes_)
	{
		box->Tick(deltaSeconds);
	}

	for (auto& reward : rewards_)
	{
		reward->Tick(deltaSeconds);
	}

	Cleanup();
}

void Spawner::Render()
{
	for (auto& box : boxes_)
	{
		box->Render();
	}

	for (auto& reward : rewards_)
	{
		reward->Render();
	}
}

void Spawner::Release()
{
	CHECK(bIsInitialized_);

	player_ = nullptr;

	bIsInitialized_ = false;
}

void Spawner::Reset()
{
	for (auto& box : boxes_)
	{
		if (box && box->GetStatus() == Box::EStatus::DONE)
		{
			EntityManager::Get().Destroy(box);
			box = nullptr;
		}
	}

	for (auto& reward : rewards_)
	{
		if (reward && reward->GetStatus() == Reward::EStatus::DONE)
		{
			EntityManager::Get().Destroy(reward);
			reward = nullptr;
		}
	}

	boxes_.clear();
	rewards_.clear();
	spawnTime_ = 0.0f;
}

void Spawner::Cleanup()
{
	for (auto& box : boxes_)
	{
		if (box && box->GetStatus() == Box::EStatus::DONE)
		{
			EntityManager::Get().Destroy(box);
			box = nullptr;
		}
	}

	for (auto& reward : rewards_)
	{
		if (reward && reward->GetStatus() == Reward::EStatus::DONE)
		{
			EntityManager::Get().Destroy(reward);
			reward = nullptr;
		}
	}

	boxes_.remove_if(boxRemoveEvent_);
	rewards_.remove_if(rewardRemoveEvent_);
}