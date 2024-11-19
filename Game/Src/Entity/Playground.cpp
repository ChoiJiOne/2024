#include "Entity/EntityManager.h"
#include "Entity/Player.h"
#include "Entity/Playground.h"
#include "GL/RenderManager2D.h"
#include "Utils/Assertion.h"

Playground::Playground()
{
	tickOrder_ = 3;
	renderOrder_ = 1;

	player_ = EntityManager::GetRef().GetByName<Player>("Player");

	safeBound_ = Circle2D(glm::vec2(0.0f, 0.0f), 1000.0f);
	warnBound_ = Circle2D(glm::vec2(0.0f, 0.0f), 1050.0f);
	playerStateColors_ =
	{
		{ EPlayerState::SAFE, glm::vec4(0.0f, 1.0f, 0.0f, 1.0f)   },
		{ EPlayerState::WARN, glm::vec4(1.0f, 0.647f, 0.0f, 1.0f) },
		{ EPlayerState::DEAD, glm::vec4(1.0f, 0.0f, 0.0f, 1.0f)   },
	};

	warnStayTime_ = 0.0f;
	maxWarnStayTime_ = 3.0f;
	deadDamage_ = 50.0f;

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
	if (!safeBound_.Intersect(player_->GetCollider()))
	{
		warnStayTime_ += deltaSeconds;
		if (!warnBound_.Intersect(player_->GetCollider()) && warnStayTime_ >= maxWarnStayTime_)
		{
			warnStayTime_ -= maxWarnStayTime_;

			float hp = player_->GetHP();
			hp -= deadDamage_;
			player_->SetHP(hp);

			playerState_ = EPlayerState::DEAD;
		}
		else
		{
			playerState_ = EPlayerState::WARN;
		}
	}
	else
	{
		warnStayTime_ = 0.0f;
		playerState_ = EPlayerState::SAFE;
	}
}

void Playground::Render()
{
	renderManager_->DrawCircleWireframe(safeBound_.center, safeBound_.radius, playerStateColors_.at(playerState_));
}

void Playground::Release()
{
	CHECK(bIsInitialized_);

	player_ = nullptr;

	bIsInitialized_ = false;
}
