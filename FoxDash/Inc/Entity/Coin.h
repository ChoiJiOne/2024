#pragma once

#include "Entity/IObject.h"
#include "GL/RenderManager2D.h"
#include "Physic/Circle2D.h"
#include "Physic/Rect2D.h"

/** 클래스 전방 선언입니다. */
class CoinCollector;
class SpriteAnimator2D;
class Sound;
class TextureAtlas2D;

/** 플레이어가 획득할 코인입니다. */
class Coin : public IObject
{
public:
	Coin(const glm::vec2& startPos, const glm::vec2& endPos);
	virtual ~Coin();

	DISALLOW_COPY_AND_ASSIGN(Coin);

	virtual void Tick(float deltaSeconds) override;
	virtual void Render() override;
	virtual void Release() override;

	/** 코인의 충돌 영역을 얻습니다. */
	const Circle2D* GetCollisionBound() const { return &collisionBound_; }

private:
	/** 코인의 그림자입니다. */
	struct Shadow
	{
		Rect2D bound; /** 그림자 영역입니다. */
		TextureDrawOption option; /** 그림자 렌더링 시 설정할 옵션입니다. */
		float scale = 0.0f; /** 그림자의 스케일 값입니다. */
	};

	/** 코인을 움직입니다. */
	void Move(float deltaSeconds);

	/** 코인의 렌더링/충돌/그림자 위치를 조정합니다. */
	void AdjustPosition(const glm::vec2& position);

private:
	/** 코인 렌더링 시 참조할 텍스처 아틀라스입니다. */
	TextureAtlas2D* textureAtlas_ = nullptr;

	/** 코인의 애니메이션을 수행하는 스프라이트 애니메이터입니다. */
	SpriteAnimator2D* animator_ = nullptr;

	/** 코인 콜렉터입니다. */
	CoinCollector* coinCollector_ = nullptr;

	/** 코인의 이동 시작 위치입니다. */
	glm::vec2 moveStartPos_ = glm::vec2(0.0f, 0.0f);
	
	/** 코인의 이동 끝 위치입니다. */
	glm::vec2 moveEndPos_ = glm::vec2(0.0f, 0.0f);
	
	/** 렌더링 영역입니다. */
	Rect2D renderBound_;

	/** 충돌 영역입니다. */
	Circle2D collisionBound_;

	/** 코인의 그림자입니다. */
	Shadow shadow_;

	/** 코인의 이동 시간입니다. */
	float moveTime_ = 0.0f;

	/** 코인의 최대 이동 시간입니다. */
	float maxMoveTime_ = 0.0f;

	/** 플레이어가 코인을 획득했는지 확인합니다. */
	bool bIsGain_ = false;

	/** 플레이어가 코인을 획득했을 때 움직이는 속도입니다. */
	float moveGainSpeed_ = 0.0f;

	/** 플레이어가 코인을 획득했을 때 출력할 사운드입니다. */
	Sound* getCoinSound_ = nullptr;
};