#include "Entity/EntityManager.h"
#include "Entity/Player.h"
#include "Entity/Playground.h"
#include "GL/RenderManager2D.h"
#include "Utils/Assertion.h"

Playground::Playground()
{
	tickOrder_ = 3;
	renderOrder_ = 1;

	safeBound_ = Circle2D(glm::vec2(0.0f, 0.0f), 1000.0f);
	warnBound_ = Circle2D(glm::vec2(0.0f, 0.0f), 1050.0f);
	playerStateColors_ =
	{
		{ EPlayerState::SAFE, glm::vec4(0.0f, 1.0f, 0.0f, 1.0f)   },
		{ EPlayerState::WARN, glm::vec4(1.0f, 0.647f, 0.0f, 1.0f) },
		{ EPlayerState::DEAD, glm::vec4(1.0f, 0.0f, 0.0f, 1.0f)   },
	};

	bIsInitialized_ = true;
}

Playground::~Playground()
{
	if (bIsInitialized_)
	{
		Release();
	}
}

void Playground::Tick(float deltaSeconds)
{
	Player* player = EntityManager::GetRef().GetByName<Player>("Player");
	if (!safeBound_.Intersect(player->GetCollider()))
	{
		if (!warnBound_.Intersect(player->GetCollider()))
		{
			playerState_ = EPlayerState::DEAD;
		}
		else
		{
			playerState_ = EPlayerState::WARN;
		}
	}
	else
	{
		playerState_ = EPlayerState::SAFE;
	}
}

void Playground::Render()
{
	renderManager_->DrawCircleWireframe(safeBound_.center, safeBound_.radius, playerStateColors_.at(playerState_));
	renderManager_->DrawCircleWireframe(warnBound_.center, warnBound_.radius, playerStateColors_.at(playerState_));
}

void Playground::Release()
{
	CHECK(bIsInitialized_);

	bIsInitialized_ = false;
}
