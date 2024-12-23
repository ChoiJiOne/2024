#define GLM_ENABLE_EXPERIMENTAL 
#include <glm/gtx/compatibility.hpp>

#include "Audio/AudioManager.h"
#include "Audio/Sound.h"
#include "Entity/Coin.h"
#include "Entity/CoinCollector.h"
#include "Entity/EntityManager.h"
#include "Entity/GamePlayRecorder.h"
#include "Entity/Player.h"
#include "Game/GameManager.h"
#include "GL/GLManager.h"
#include "GL/SpriteAnimator2D.h"
#include "GL/TextureAtlas2D.h"
#include "Utils/Assertion.h"

Coin::Coin(const glm::vec2& startPos, const glm::vec2& endPos)
	: IObject(IObject::EType::COIN)
	, moveStartPos_(startPos)
	, moveEndPos_(endPos)
{
	textureAtlas_ = GLManager::GetRef().GetByName<TextureAtlas2D>("TextureAtlas");
	coinCollector_ = EntityManager::GetRef().GetByName<CoinCollector>("CoinCollector");
	getCoinSound_ = AudioManager::GetRef().GetByName<Sound>("Coin");

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
	maxMoveTime_ = GameManager::GetRef().GetConfigValue<float>("Coin.maxMoveTime");
	bIsGain_ = false;
	moveGainSpeed_ = GameManager::GetRef().GetConfigValue<float>("Coin.moveGainSpeed");

	GamePlayRecorder* gamePlayRecorder = EntityManager::GetRef().GetByName<GamePlayRecorder>("GamePlayRecorder");
	gamePlayRecorder->AddRecord(GamePlayRecorder::ERecordType::GEN_COIN, 1);

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
		if (!bIsGain_) // 플레이어가 코인을 획득하지 않았을 때.
		{
			Move(deltaSeconds);
			if (moveTime_ >= maxMoveTime_)
			{
				state_ = EState::WAIT;
			}
		}
		else // 플레이어가 코인을 획득했을 때.
		{
			glm::vec2 currentPosition = renderBound_.center;
			glm::vec2 targetPosition = coinCollector_->GetCollider()->center;
			glm::vec2 direction = glm::normalize(targetPosition - currentPosition);

			currentPosition += direction * deltaSeconds * moveGainSpeed_;
			AdjustPosition(currentPosition);

			if (collisionBound_.Intersect(coinCollector_->GetCollider()))
			{
				player_->AddCoin();
				state_ = IObject::EState::DONE;
			}
		}
	}
	break;

	case EState::WAIT:
	{
		if (collisionBound_.Intersect(player_->GetCollider()))
		{
			getCoinSound_->Start();
			state_ = EState::MOVE;
			bIsGain_ = true;
		}
	}
	break;
	}
	
	animator_->Update(deltaSeconds);
}

void Coin::Render()
{
	if (state_ == EState::DONE || state_ == EState::NONE)
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
	if (animator_)
	{
		GLManager::GetRef().Destroy(animator_);
		animator_ = nullptr;
	}

	getCoinSound_ = nullptr;
	coinCollector_ = nullptr;
	textureAtlas_ = nullptr;

	IObject::Release();
}

void Coin::Move(float deltaSeconds)
{
	moveTime_ += deltaSeconds;
	float timeScale = glm::clamp<float>(moveTime_ / maxMoveTime_, 0.0f, 1.0f);
	glm::vec2 movePos = glm::lerp(moveStartPos_, moveEndPos_, timeScale);

	AdjustPosition(movePos);
}

void Coin::AdjustPosition(const glm::vec2& position)
{
	renderBound_.center = position;

	collisionBound_.center = renderBound_.center;
	collisionBound_.center.y += -renderBound_.size.y * 0.5f + collisionBound_.radius;

	shadow_.bound.center = renderBound_.center;
	shadow_.bound.center.y += (-renderBound_.size.y * 0.5f) + (-shadow_.bound.size.y * 0.5f);
}
