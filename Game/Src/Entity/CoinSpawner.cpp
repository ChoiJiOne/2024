#include <glm/gtc/random.hpp>

#include "Entity/Coin.h"
#include "Entity/CoinSpawner.h"
#include "Entity/EntityManager.h"
#include "GL/GLManager.h"
#include "GL/SpriteAnimator2D.h"
#include "GL/TextureAtlas2D.h"
#include "Scene/GamePlayScene.h"
#include "Scene/SceneManager.h"
#include "Utils/Assertion.h"

CoinSpawner::CoinSpawner(const glm::vec2& position)
{
	tickOrder_ = 5;
	renderOrder_ = 1;
	
	textureAtlas_ = GLManager::GetRef().GetByName<TextureAtlas2D>("TextureAtlas");

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

	std::vector<std::string> coinClipNames =
	{
		"CoinChest_1",
		"CoinChest_2",
		"CoinChest_3",
		"CoinChest_4",
		"CoinChest_5",
		"CoinChest_6",
		"CoinChest_7",
	};
	animator_ = GLManager::GetRef().Create<SpriteAnimator2D>(textureAtlas_, coinClipNames, 1.0f, false);

	bIsInitialized_ = true;
}

CoinSpawner::~CoinSpawner()
{
	if (bIsInitialized_)
	{
		Release();
	}
}

void CoinSpawner::Tick(float deltaSeconds)
{
	animator_->Update(deltaSeconds);
}

void CoinSpawner::Render()
{
	TextureAtlas2D* animationTexture = animator_->GetTextureAtlas();
	const std::string& animationClipName = animator_->GetCurrentClipName();

	renderManager_->DrawTextureAtlas(animationTexture, animationClipName, renderBound_.center, renderBound_.size.x, renderBound_.size.y, 0.0f);
	renderManager_->DrawTextureAtlas(animationTexture, animationClipName, shadow_.bound.center, shadow_.bound.size.x, shadow_.bound.size.y, 0.0f, shadow_.option);
}

void CoinSpawner::Release()
{
	CHECK(bIsInitialized_);
	
	if (animator_)
	{
		GLManager::GetRef().Destroy(animator_);
		animator_ = nullptr;
	}

	textureAtlas_ = nullptr;

	bIsInitialized_ = false;
}
