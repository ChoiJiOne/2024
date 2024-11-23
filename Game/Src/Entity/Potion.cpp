#define GLM_ENABLE_EXPERIMENTAL 
#include <glm/gtx/compatibility.hpp>

#include "Entity/EntityManager.h"
#include "Entity/Potion.h"
#include "Entity/Player.h"
#include "GL/GLManager.h"
#include "GL/TextureAtlas2D.h"
#include "Utils/Assertion.h"

Potion::Potion(const glm::vec2& startPos, const glm::vec2& endPos, const EColor& color)
	: IObject(IObject::EType::POTION)
	, moveStartPos_(startPos)
	, moveEndPos_(endPos)
	, color_(color)
{
	tickOrder_ = 3;
	renderOrder_ = 4;

	textureAtlas_ = GLManager::GetRef().GetByName<TextureAtlas2D>("TextureAtlas");

	renderBound_.center = startPos;
	if (color_ == EColor::BLUE || color_ == EColor::RED)
	{
		renderBound_.size = glm::vec2(32.0f, 32.0f);
	}
	else
	{
		renderBound_.size = glm::vec2(48.0f, 48.0f);
	}

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

	state_ = EState::MOVE;
	moveTime_ = 0.0f;
	maxMoveTime_ = 2.0f;

	heal_ = 10.0f;

	colorNames_ =
	{
		{ EColor::RED,        "PotionRed"   },
		{ EColor::BLUE,       "PotionsBlue" },
		{ EColor::RED_POWER,  "PotionRed"   },
		{ EColor::BLUE_POWER, "PotionsBlue" },
	};

	outlineColors_ =
	{
		{ EColor::RED_POWER,  glm::vec4(1.0f, 0.2f, 0.2f, 1.0f) },
		{ EColor::BLUE_POWER, glm::vec4(0.2f, 0.2f, 1.0f, 1.0f) },
	};
}

Potion::~Potion()
{
	if (bIsInitialized_)
	{
		Release();
	}
}

void Potion::Tick(float deltaSeconds)
{
	switch (state_)
	{
	case EState::MOVE:
	{
		Move(deltaSeconds);
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
			switch (color_)
			{
			case EColor::RED:
			{
				float hp = player_->GetHP();
				hp += heal_;
				player_->SetHP(hp);
			}
			break;

			case EColor::BLUE:
			{
				float mp = player_->GetMP();
				mp += heal_;
				player_->SetMP(mp);
			}
			break;

			case EColor::RED_POWER:
			{
				float maxHp = player_->GetMaxHP();
				maxHp += heal_;
				player_->SetMaxHP(maxHp);

				float hp = player_->GetHP();
				hp = maxHp;
				player_->SetHP(hp);
			}
			break;

			case EColor::BLUE_POWER:
			{
				float maxMp = player_->GetMaxMP();
				maxMp += heal_;
				player_->SetMaxMP(maxMp);

				float mp = player_->GetMP();
				mp = maxMp;
				player_->SetMP(mp);
			}
			break;
			}

			state_ = EState::DONE;
		}
	}
	break;

	case EState::DONE:
	{

	}
	break;
	}
}

void Potion::Render()
{
	if (state_ == EState::DONE || state_ == EState::NONE)
	{
		return;
	}

	if (color_ == EColor::BLUE || color_ == EColor::RED)
	{
		renderManager_->DrawTextureAtlas(textureAtlas_, colorNames_.at(color_), renderBound_.center, renderBound_.size.x, renderBound_.size.y, 0.0f);
	}
	else
	{
		renderManager_->DrawTextureAtlas(textureAtlas_, colorNames_.at(color_), renderBound_.center, renderBound_.size.x, renderBound_.size.y, 0.0f, outlineColors_.at(color_));
	}
	
	renderManager_->DrawTextureAtlas(textureAtlas_, colorNames_.at(color_), shadow_.bound.center, shadow_.bound.size.x, shadow_.bound.size.y, 0.0f, shadow_.option);
}

void Potion::Release()
{
	textureAtlas_ = nullptr;

	IObject::Release();
}

void Potion::Move(float deltaSeconds)
{
	moveTime_ += deltaSeconds;
	float timeScale = glm::clamp<float>(moveTime_ / maxMoveTime_, 0.0f, 1.0f);
	glm::vec2 movePos = glm::lerp(moveStartPos_, moveEndPos_, timeScale);

	renderBound_.center = movePos;

	collisionBound_.center = renderBound_.center;
	collisionBound_.center.y += -renderBound_.size.y * 0.5f + collisionBound_.radius;

	shadow_.bound.center = renderBound_.center;
	shadow_.bound.center.y += (-renderBound_.size.y * 0.5f) + (-shadow_.bound.size.y * 0.5f);
}