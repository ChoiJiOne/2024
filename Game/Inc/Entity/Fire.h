#pragma once

#include <map>

#include "Entity/IObject.h"
#include "GL/RenderManager2D.h"
#include "Physic/Circle2D.h"
#include "Physic/OrientedRect2D.h"

/** 클래스 전방 선언입니다. */
class SpriteAnimator2D;
class Sound;
class TextureAtlas2D;

/** 플레이어가 피해야 할 불입니다. */
class Fire : public IObject
{
public:
	/** 애니메이션 상태입니다. */
	enum EAnimationState
	{
		BURN = 0x00,      // 불타는 상태.
		EXPLOSION = 0x01, // 폴발 상태.
	};

public:
	Fire(const glm::vec2& position, const glm::vec2& direction, float speed, float lifeTime);
	virtual ~Fire();

	DISALLOW_COPY_AND_ASSIGN(Fire);

	virtual void Tick(float deltaSeconds) override;
	virtual void Render() override;
	virtual void Release() override;

	/** 불의 충돌 영역을 얻습니다. */
	const Circle2D* GetCollisionBound() const { return &collisionBound_; }

private:
	/** 불을 움직입니다. */
	void Move(float deltaSeconds);

	/** 불의 애니메이션 상태를 초기화합니다. */
	void LoadAnimations();

	/** 불의 애니메이션 상태 초기화를 해제합니다. */
	void UnloadAnimation();

private:
	/** 불 렌더링 시 참조할 텍스처 아틀라스입니다. */
	TextureAtlas2D* textureAtlas_ = nullptr;
	
	/** 렌더링 영역입니다. */
	OrientedRect2D renderBound_;

	/** 충돌 영역입니다. */
	Circle2D collisionBound_;

	/** 불의 이동 방향입니다. */
	glm::vec2 direction_ = glm::vec2(0.0f, 0.0f);

	/** 불의 이동 속도입니다. */
	float speed_ = 0.0f;

	/** 불의 라이프 타입입니다. */
	float lifeTime_ = 0.0f;

	/** 불의 데미지 값입니다. */
	float damage_ = 0.0f;

	/** 애니메이션 상태입니다. */
	EAnimationState animationState_ = EAnimationState::BURN;

	/** 불의 상태 별 애니메이션입니다. */
	std::map<EAnimationState, SpriteAnimator2D*> animations_;

	/** 불 폭발 시 출력할 사운드입니다. */
	Sound* explosionSound_ = nullptr;
};