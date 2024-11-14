#pragma once

#include <map>

#include "Entity/IEntity2D.h"
#include "Physic/Circle2D.h"
#include "Physic/Rect2D.h"

/** 클래스 전방 선언입니다. */
class SpriteAnimator2D;
class TextureAtlas2D;

/** 플레이어가 조종할 엔티티입니다. */
class Player : public IEntity2D
{
public:
	Player();
	virtual ~Player();

	DISALLOW_COPY_AND_ASSIGN(Player);

	virtual void Tick(float deltaSeconds) override;
	virtual void Render() override;
	virtual void Release() override;

private:
	/** 플레이어의 애니메이션 상태입니다. */
	enum class EAnimationState
	{
		IDLE = 0x00,
		RUN  = 0x01,
		HURT = 0x02,
	};

	/** 플레이어의 애니메이션 상태를 초기화합니다. */
	void LoadAnimations();

	/** 플레이어의 애니메이션 상태 초기화를 해제합니다. */
	void UnloadAnimation();

private:
	/** 플레이어 렌더링 시 참조할 텍스처 아틀라스입니다. */
	TextureAtlas2D* textureAtlas_ = nullptr;

	/** 렌더링 영역입니다 */
	Rect2D renderBound_;

	/** 충돌 영역입니다. */
	Circle2D collisionBound_;

	/** 현재 애니메이션의 상태입니다. */
	EAnimationState animationState_ = EAnimationState::IDLE;

	/** 플레이어의 애니메이션 상태 별 애니메이션 리소스입니다. */
	std::map<EAnimationState, SpriteAnimator2D*> animations_;
};
