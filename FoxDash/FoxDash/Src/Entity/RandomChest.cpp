#include "Entity/Coin.h"
#include "Entity/EntityManager.h"
#include "Entity/Fire.h"
#include "Entity/IObject.h"
#include "Entity/RandomChest.h"
#include "Entity/Potion.h"
#include "Entity/Player.h"
#include "Entity/Playground.h"
#include "Game/GameManager.h"
#include "GL/GLManager.h"
#include "GL/SpriteAnimator2D.h"
#include "GL/TextureAtlas2D.h"
#include "Scene/GamePlayScene.h"
#include "Scene/SceneManager.h"
#include "Utils/Assertion.h"
#include "Utils/Math.h"

RandomChest::RandomChest(const glm::vec2& position)
{
	textureAtlas_ = GLManager::GetRef().GetByName<TextureAtlas2D>("TextureAtlas");
	player_ = EntityManager::GetRef().GetByName<Player>("Player");
	playground_ = EntityManager::GetRef().GetByName<Playground>("Playground");
	gamePlayScene_ = SceneManager::GetRef().GetByName<GamePlayScene>("GamePlayScene");

	renderBound_ = Rect2D(position, glm::vec2(64.0f, 64.0f));
	collisionBound_ = renderBound_;
	collisionBound_.size.y *= 0.5f;

	shadow_.scale = 0.5f;
	shadow_.bound = renderBound_;
	shadow_.bound.size.y *= shadow_.scale;
	shadow_.bound.center.y += (-renderBound_.size.y * 0.5f) + (-shadow_.bound.size.y * 0.5f);
	shadow_.option.blend = glm::vec3(0.0f, 0.0f, 0.0f);
	shadow_.option.factor = 1.0f;
	shadow_.option.transparent = 0.3f;
	shadow_.option.bIsFlipV = true;

	std::vector<std::string> chestClipNames =
	{
		"Chest_1",
		"Chest_2",
		"Chest_3",
		"Chest_4",
		"Chest_5",
		"Chest_6",
		"Chest_7",
	};
	animator_ = GLManager::GetRef().Create<SpriteAnimator2D>(textureAtlas_, chestClipNames, 1.0f, false);

	waitTime_ = 0.0f;
	maxWaitTime_ = GameManager::GetRef().GetConfigValue<float>("RandomChest.maxWaitTime");
	bIsGenerateObject_ = false;
	minFireSpeed_ = GameManager::GetRef().GetConfigValue<float>("RandomChest.minFireSpeed");
	maxFireSpeed_ = GameManager::GetRef().GetConfigValue<float>("RandomChest.maxFireSpeed");
	minFireLifeTime_ = GameManager::GetRef().GetConfigValue<float>("RandomChest.minFireLifeTime");
	maxFireLifeTime_ = GameManager::GetRef().GetConfigValue<float>("RandomChest.maxFireLifeTime");

	bIsInitialized_ = true;
}

RandomChest::~RandomChest()
{
	if (bIsInitialized_)
	{
		Release();
	}
}

void RandomChest::Tick(float deltaSeconds)
{
	switch (state_)
	{
	case EState::WAIT:
	{
		waitTime_ += deltaSeconds;
		if (waitTime_ >= maxWaitTime_)
		{
			waitTime_ -= maxWaitTime_;
			state_ = EState::GENERATE;
		}
	}
	break;

	case EState::GENERATE:
	{
		animator_->Update(deltaSeconds);

		const std::string& animationClipName = animator_->GetCurrentClipName();
		if (animationClipName == "Chest_4" && !bIsGenerateObject_)
		{
			IObject* randomObject = GenerateRandomObject();

			objects_.push_back(randomObject);
			gamePlayScene_->AddEntity(randomObject, 5, 8);

			bIsGenerateObject_ = true;
		}
		else if (animationClipName == "Chest_7")
		{
			animator_->Reset();
			bIsGenerateObject_ = false;
			state_ = EState::WAIT;
		}
	}
	break;
	}

	CleanupObjects();
}

void RandomChest::Render()
{
	TextureAtlas2D* animationTexture = animator_->GetTextureAtlas();
	const std::string& animationClipName = animator_->GetCurrentClipName();

	renderManager_->DrawTextureAtlas(animationTexture, animationClipName, renderBound_.center, renderBound_.size.x, renderBound_.size.y, 0.0f);
	renderManager_->DrawTextureAtlas(animationTexture, animationClipName, shadow_.bound.center, shadow_.bound.size.x, shadow_.bound.size.y, 0.0f, shadow_.option);
}

void RandomChest::Release()
{
	CHECK(bIsInitialized_);
	
	if (animator_)
	{
		GLManager::GetRef().Destroy(animator_);
		animator_ = nullptr;
	}

	playground_ = nullptr;
	player_ = nullptr;
	textureAtlas_ = nullptr;

	bIsInitialized_ = false;
}

bool RandomChest::IsRange(int32_t num, int32_t minNum, int32_t maxNum)
{
	int32_t minNumber = glm::min<float>(minNum, maxNum);
	int32_t maxNumber = glm::max<float>(minNum, maxNum);

	return (minNumber <= num) && (num <= maxNumber);
}

IObject* RandomChest::GenerateRandomObject()
{
	EntityManager& entityManager = EntityManager::GetRef();
	int32_t randomSelect = GenerateRandomInt(MIN_RANDOM_SELECT, MAX_RANDOM_SELECT);

	if (IsRange(randomSelect, 1, 50)) // 약 50%
	{
		glm::vec2 postiton = renderBound_.center;
		glm::vec2 direction = glm::normalize(player_->GetCollider()->center - postiton);
		float speed = GenerateRandomFloat(minFireSpeed_, maxFireSpeed_);
		float lifeTime = GenerateRandomFloat(minFireLifeTime_, maxFireLifeTime_);

		return entityManager.Create<Fire>(postiton, direction, speed, lifeTime);
	}
	else if (IsRange(randomSelect, 51, 94)) // 약 44%
	{
		glm::vec2 startPos = renderBound_.center;
		glm::vec2 endPos = GenerateRandomDisk(playground_->GetSafeBound()->radius);

		return entityManager.Create<Coin>(startPos, endPos);
	}
	else
	{
		glm::vec2 startPos = renderBound_.center;
		glm::vec2 endPos = GenerateRandomDisk(playground_->GetSafeBound()->radius);

		int32_t start = 0;
		int32_t end = 0;
		if (IsRange(randomSelect, 95, 99)) // 약 5%
		{
			start = static_cast<int32_t>(Potion::EColor::RED);
			end = static_cast<int32_t>(Potion::EColor::BLUE);
		}
		else // 약 1%
		{
			start = static_cast<int32_t>(Potion::EColor::RED_POWER);
			end = static_cast<int32_t>(Potion::EColor::BLUE_POWER);
		}

		Potion::EColor color = static_cast<Potion::EColor>(GenerateRandomInt(start, end));
		return entityManager.Create<Potion>(startPos, endPos, color);
	}

	return nullptr;
}

void RandomChest::CleanupObjects()
{
	for (auto& object : objects_)
	{
		if (object && object->GetState() == IObject::EState::DONE)
		{
			gamePlayScene_->RemoveEntity(object);
			EntityManager::GetRef().Destroy(object);
			object = nullptr;
		}
	}
	
	objects_.remove_if([&](IObject* object) { return object == nullptr; });
}
