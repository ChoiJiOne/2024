#define GLM_ENABLE_EXPERIMENTAL 
#include <glm/gtx/compatibility.hpp>

#include "Entity/Coin.h"
#include "Entity/EntityManager.h"
#include "Entity/Player.h"
#include "GL/GLManager.h"
#include "GL/SpriteAnimator2D.h"
#include "GL/TextureAtlas2D.h"
#include "Utils/Assertion.h"

Coin::Coin(const glm::vec2& startPos, const glm::vec2& endPos)
	: moveStartPos_(startPos)
	, moveEndPos_(endPos)
{
	tickOrder_ = 3;
	renderOrder_ = 4;

	textureAtlas_ = GLManager::GetRef().GetByName<TextureAtlas2D>("TextureAtlas");
	player_ = EntityManager::GetRef().GetByName<Player>("Player");

	renderBound_ = Rect2D(startPos, glm::vec2(32.0f, 32.0f));
	collisionBound_.radius = 16.0f;
	collisionBound_.center = renderBound_.center;
	collisionBound_.center.y += -renderBound_.size.y * 0.5f + collisionBound_.radius;

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
		"Coin_1",
		"Coin_2",
		"Coin_3",
		"Coin_4",
		"Coin_5",
	};
	animator_ = GLManager::GetRef().Create<SpriteAnimator2D>(textureAtlas_, coinClipNames, 0.5f, true);
	
	state_ = EState::MOVE;
	moveTime_ = 0.0f;
	maxMoveTime_ = 2.0f;

	bIsInitialized_ = true;
}

Coin::~Coin()
{
	if (bIsInitialized_)
	{
		Release();
	}
}

void Coin::Tick(float deltaSeconds)
{
	switch (state_)
	{
	case EState::MOVE:
	{
		moveTime_ += deltaSeconds;
		float timeScale = glm::clamp<float>(moveTime_ / maxMoveTime_, 0.0f, 1.0f);

		glm::vec2 movePos = glm::lerp(moveStartPos_, moveEndPos_, timeScale);
		UpdateBounds(movePos);

		if (moveTime_ >= maxMoveTime_)
		{
			state_ = EState::WAIT;
		}
	}
	break;

	case EState::WAIT:
	{
		if (collisionBound_.Intersect(player_->GetCollider()))
		{
			state_ = EState::GAIN;
		}
	}
	break;

	case EState::GAIN:
	{

	}
	break;
	}
	
	animator_->Update(deltaSeconds);
}

void Coin::Render()
{
	if (state_ == EState::GAIN || state_ == EState::NONE)
	{
		return;
	}

	TextureAtlas2D* animationTexture = animator_->GetTextureAtlas();
	const std::string& animationClipName = animator_->GetCurrentClipName();

	renderManager_->DrawTextureAtlas(animationTexture, animationClipName, renderBound_.center, renderBound_.size.x, renderBound_.size.y, 0.0f);
	renderManager_->DrawTextureAtlas(animationTexture, animationClipName, shadow_.bound.center, shadow_.bound.size.x, shadow_.bound.size.y, 0.0f, shadow_.option);
}

void Coin::Release()
{
	CHECK(bIsInitialized_);

	player_ = nullptr;

	if (animator_)
	{
		GLManager::GetRef().Destroy(animator_);
		animator_ = nullptr;
	}

	textureAtlas_ = nullptr;

	bIsInitialized_ = false;
}

void Coin::UpdateBounds(const glm::vec2& position)
{
	renderBound_.center = position;
	
	collisionBound_.center = renderBound_.center;
	collisionBound_.center.y += -renderBound_.size.y * 0.5f + collisionBound_.radius;
	
	shadow_.bound.center = renderBound_.center;
	shadow_.bound.center.y += (-renderBound_.size.y * 0.5f) + (-shadow_.bound.size.y * 0.5f);
}
