#include <glm/gtc/random.hpp>

#include "Entity/EntityManager.h"
#include "Entity/FireSpawner.h"
#include "Entity/Playground.h"
#include "GL/GLManager.h"
#include "GL/SpriteAnimator2D.h"
#include "GL/TextureAtlas2D.h"
#include "Scene/GamePlayScene.h"
#include "Scene/SceneManager.h"
#include "Utils/Assertion.h"

FireSpawner::FireSpawner(const glm::vec2& position)
{
	tickOrder_ = 5;
	renderOrder_ = 1;

	textureAtlas_ = GLManager::GetRef().GetByName<TextureAtlas2D>("TextureAtlas");
	playground_ = EntityManager::GetRef().GetByName<Playground>("Playground");

	renderBound_ = Rect2D(position, glm::vec2(64.0f, 128.0f));
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

	std::vector<std::string> burnClipNames =
	{
		"Burning_1",
		"Burning_2",
		"Burning_3",
		"Burning_4",
		"Burning_5",
		"Burning_6",
		"Burning_7",
		"Burning_8",
	};
	animator_ = GLManager::GetRef().Create<SpriteAnimator2D>(textureAtlas_, burnClipNames, 1.0f, true);

	bIsInitialized_ = true;
}

FireSpawner::~FireSpawner()
{
	if (bIsInitialized_)
	{
		Release();
	}
}

void FireSpawner::Tick(float deltaSeconds)
{
	animator_->Update(deltaSeconds);
}

void FireSpawner::Render()
{
	TextureAtlas2D* animationTexture = animator_->GetTextureAtlas();
	const std::string& animationClipName = animator_->GetCurrentClipName();

	renderManager_->DrawTextureAtlas(animationTexture, animationClipName, renderBound_.center, renderBound_.size.x, renderBound_.size.y, 0.0f);
	renderManager_->DrawTextureAtlas(animationTexture, animationClipName, shadow_.bound.center, shadow_.bound.size.x, shadow_.bound.size.y, 0.0f, shadow_.option);

}

void FireSpawner::Release()
{
	CHECK(bIsInitialized_);

	if (animator_)
	{
		GLManager::GetRef().Destroy(animator_);
		animator_ = nullptr;
	}

	playground_ = nullptr;
	textureAtlas_ = nullptr;

	bIsInitialized_ = false;
}