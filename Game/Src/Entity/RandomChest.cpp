#include "Entity/Coin.h"
#include "Entity/Fire.h"
#include "Entity/RandomChest.h"
#include "Entity/EntityManager.h"
#include "Entity/Player.h"
#include "Entity/Playground.h"
#include "GL/GLManager.h"
#include "GL/SpriteAnimator2D.h"
#include "GL/TextureAtlas2D.h"
#include "Scene/GamePlayScene.h"
#include "Scene/SceneManager.h"
#include "Utils/Assertion.h"
#include "Utils/Math.h"

RandomChest::RandomChest(const glm::vec2& position)
{
	tickOrder_ = 5;
	renderOrder_ = 1;
	
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

	std::vector<std::string> coinChestClipNames =
	{
		"Chest_1",
		"Chest_2",
		"Chest_3",
		"Chest_4",
		"Chest_5",
		"Chest_6",
		"Chest_7",
	};
	animator_ = GLManager::GetRef().Create<SpriteAnimator2D>(textureAtlas_, coinChestClipNames, 1.0f, false);

	waitTime_ = 0.0f;
	maxWaitTime_ = 2.0f;
	bIsGenerate_ = false;
	minFireSpeed_ = 100.0f;
	maxFireSpeed_ = 400.0f;

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
		if (animationClipName == "Chest_4" && !bIsGenerate_)
		{
			glm::vec2 postiton = renderBound_.center;
			glm::vec2 direction = glm::normalize(player_->GetCollider()->center - postiton);
			float speed = GenerateRandomFloat(minFireSpeed_, maxFireSpeed_);

			Fire* fire = EntityManager::GetRef().Create<Fire>(postiton, direction, speed);
			fires_.push_back(fire);

			gamePlayScene_->AddUpdateEntity(fire);
			gamePlayScene_->AddRenderEntity(fire);




			glm::vec2 startPos = renderBound_.center;
			glm::vec2 endPos = GenerateRandomDisk(playground_->GetSafeBound()->radius);

			Coin* coin = EntityManager::GetRef().Create<Coin>(startPos, endPos);
			coins_.push_back(coin);

			gamePlayScene_->AddUpdateEntity(coin);
			gamePlayScene_->AddRenderEntity(coin);

			bIsGenerate_ = true;
		}
		else if (animationClipName == "Chest_7")
		{
			animator_->Reset();
			bIsGenerate_ = false;
			state_ = EState::WAIT;
		}
	}
	break;
	}

	for (auto& coin : coins_)
	{
		if (coin && coin->GetState() == Coin::EState::GAIN)
		{
			gamePlayScene_->RemoveUpdateEntity(coin);
			gamePlayScene_->RemoveRenderEntity(coin);
			EntityManager::GetRef().Destroy(coin);
			coin = nullptr;
		}
	}

	for (auto& fire : fires_)
	{
		if (fire && fire->GetState() == Fire::EState::DONE)
		{
			gamePlayScene_->RemoveUpdateEntity(fire);
			gamePlayScene_->RemoveRenderEntity(fire);
			EntityManager::GetRef().Destroy(fire);
			fire = nullptr;
		}
	}

	coins_.remove_if([&](Coin* coin) { return coin == nullptr; });
	fires_.remove_if([&](Fire* fire) { return fire == nullptr; });
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
